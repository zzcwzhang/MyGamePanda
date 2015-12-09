#include "ZGame.h"
#include "GameState.h"
#include "ZHero.h"
#include "XFrameID.h"
#include "SMainMenu.h"

NAMESPACE_ZJG_BEGIN

#define CONFIGFILE		("config.bin")
#define GAMEDATA		("gameData.bin")

BatteryChoice* ZGame::m_towerChoose;
BatteryUpgrade* ZGame::m_towerUpgrade;

ZGame::ZGame(void)
{
	m_towerChoose = NULL;
	m_towerUpgrade = NULL;
	preGameState = G_ST_NULL;
	coin = 0;
	curLv = -1;
	curWave = 0;
	isDoubleSpeed = false;
	isPause = false;
	m_map = NULL;
	haveUI = false;
}
ZGame::~ZGame(void)
{
	
	//destory();
	CC_SAFE_DELETE(m_towerChoose);
	CC_SAFE_DELETE(m_towerUpgrade);

}

void ZGame::destory()
{
	//removeCurFrames();
	if (m_map)
	{
		m_map->removeFromParentAndCleanup(true);
		m_map = NULL;
	}
}

void ZGame::touchBegan(float x,float y)
{
}

void ZGame::touchMoved(float x,float y)
{


}

void ZGame::touchEnded(float x,float y)
{
	switch(preGameState)
	{
	case G_ST_LOADING:
		break;
	case G_ST_GAMEING:
		{
			if (!touchAtkable(x,y)&&m_map) //先检测是否点击到怪物;
			{
				Cell* cell= m_map->getTouch(x,y);
				cellNum = cell->getID();

				if (cell->curObject == eSpace)
				{
					//Footman::create(m_map,cellNum,1);
					m_choose->ShowChoiceMenu(cell->getMidPoint());
					setState(G_ST_CHOOSETOWER);
				}
				if (cell->curObject == eShooter)
				{
					m_upgrade->ShowUpgradeMenu(cellNum);
					setState(G_ST_UPGRADE);
				}
			}	
		}
		break;
	case G_ST_CHOOSETOWER:
		do 
		{
			int order = m_choose->touchEnd(x,y);
			if (order!=-1)
			{
				ReadInfo* inf = ReadInfo::getInstance();
				if (pay(inf->footmanarray[order][Footman::bugprice]))
				{	
					Footman::create(m_map,cellNum,order)->setATK(towerAttackPower[order]);
				}
			}	
			ZGame::m_towerChoose->Exeunt();
			setState(G_ST_GAMEING);
		} while (0);
		break;

	case G_ST_UPGRADE:
		do 
		{
			int order = m_upgrade->touchEnd(x,y);
			if (order == 1)
			{
				//addCoin(-m_upgrade->tower->getNextLevelPrice());
				Shooter* t = m_upgrade->tower;
				if (pay(t->getNextLevelPrice()))
				{
					t->setBuildLevel(t->getBuildLevel()+1);
				}
			}
			if (order == 0)
			{

			}
			m_upgrade->buExeunt();
			setState(G_ST_GAMEING);
		} while (0);
		break;
	case G_ST_MENU:
		break;
	}
}

void ZGame::playBGM()
{
	m_gamestate->playBGM(BGM_GRAVEYARD);
}

void ZGame::intoNextState(int state, int dt)
{
	nextState = state;
	delayTime = dt;
}

void ZGame::dataRead()
{
	ReadInfo* inf = ReadInfo::getInstance();
	//初始化菜单;
	ShareBC();
	ShareUG();
	
	for (int i = 0;i<inf->footmanarray.size();i++)
	{
		int curAtk = inf->footmanarray[i][1];

		do //加载符文攻击力;
		{
			float pSum = 100.0f;
			array2(int) rune(inf->Runearray);
			for (int i = 0;i<rune.size();i++)
			{
				pSum += (float)rune[i][1];
			}

			curAtk =(int)(curAtk*pSum/100);
		} while (0);

		do //装备攻击（未完成）;
		{
			int equipAttack = 0;
			do //读取装备加成;
			{
				equipAttack = 20;
			} while (0);

			do //装备加成系数;
			{
				float atkCoefficien = 1;
				switch (i)
				{
				case 0:
					break;
				case 1: atkCoefficien = 0.7f;
					break;
				case 2: atkCoefficien = 0.5f;
					break;
				case 3: atkCoefficien = 0.4f;
					break;
				case 4:
					break;
				case 5:atkCoefficien = 0.4f;
					break;
				case 6:atkCoefficien = 0.25f;
					break;
				case 7:atkCoefficien = 0.35f;
					break;
				case 8:atkCoefficien = 0.7f;
					break;
				case 9:atkCoefficien = 0.7f;
					break;
				case 10:atkCoefficien = 0.5f;
					break;
				case 11:atkCoefficien = 0.25f;
					break;
				case 12:atkCoefficien = 0.6f;
					break;
				case 13:
					break;
				case 14:
					break;
				}
				equipAttack *= atkCoefficien;

			} while (0); //装备攻击读取完成;

			curAtk+=equipAttack;

		} while (0);



		towerAttackPower.push_back(curAtk);
	}


	////打印;
	//for (int i = 0;i<inf->footmanarray.size();i++)
	//{
	//	CCLOG("tower[%d] atk = %d",i,towerAttackPower[i]);
	//}
}

void ZGame::setState(int state)
{

	switch(preGameState)
	{
	case G_ST_NULL:
		CCLog("preGameState NULL show Frame_loading ");
		m_gameRes->ZUI_show(this,Frame_loading,false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2,true,10024);
		break;
	}
	preGameState = state;
	
	switch(state)
	{
	case G_ST_LOADING:
		//CCLog("Into Loading ather 0.5 second into Gameing");
		initUI();
		GameInit();
		dataRead();
		intoNextState(G_ST_GAMEING,30);
		break;
	case G_ST_GAMEING:
		//CCLog("Now Into Gameing And remove Frame_loading");
		m_gameRes->ZUI_removeAFrame(Frame_loading);
		break;
	}
	gameState = state;
}

void ZGame::update(float t)
{
	m_gameRes->ZUI_update();
	if (isPause)
	{
		return;
	}

	if (delayTime > 0)
	{
		delayTime--;
		if (delayTime <= 0)
		{
			setState(nextState);
		}
	}
	
	switch(gameState)
	{
	case G_ST_LOADING:
		return;
		break;
	case G_ST_GAMEING:
		break;
	case G_ST_MENU:
		return;
		break;
	}
	
	if (isDoubleSpeed)
	{	
		GameStep();
	}
	GameStep();
	

	
}

void ZGame::initUI()
{
	CCLOG("INIT UI");
	m_gameRes->ZUI_show(this, Frame_youxijiemain, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false, 10000);
	m_gameRes->ZUI_setClickListener(this, Frame_youxijiemain, Frame_youxijiemain_or_61, toucheventselector(ZGame::backtoXuanguan1));
	m_gameRes->ZUI_setClickListener(this, Frame_youxijiemain, Frame_youxijiemain_or_60, toucheventselector(ZGame::reGame));
	m_gameRes->ZUI_setClickListener(this, Frame_youxijiemain, Frame_youxijiemain_or_64, toucheventselector(ZGame::SpeedXX));
	m_gameRes->ZUI_setClickListener(this, Frame_youxijiemain, Frame_youxijiemain_or_65, toucheventselector(ZGame::PauseGame));
	m_gameRes->ZUI_setNumForNumbar(Frame_youxijiemain,Frame_youxijiemain_or_68,m_gamestate->curLevel+1); // 设置数字:关卡;

	//--加载plist;

	if (haveUI)
	{
		return;
	}

	CCSpriteFrameCache *frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("plists/build.plist");
	frameCache->addSpriteFramesWithFile("plists/tower.plist");
	frameCache->addSpriteFramesWithFile("plists/demon.plist");
	frameCache->addSpriteFramesWithFile("plists/game.plist");
	frameCache->addSpriteFramesWithFile("plists/grade.plist");

	//--加载游戏动画;
	//怪物动画80*80;
	for (int i = 0;i<30;i++)
	{
		char tempA[30];
		sprintf(tempA,"gw%02d",i);
		char tempB[30];
		sprintf(tempB,"gw%02d",i);
		strcat(tempA,"_a.png");
		strcat(tempB,"_b.png");
		CCArray *animations = CCArray::createWithCapacity(2); 
		CCSpriteFrame *frameA = frameCache->spriteFrameByName(tempA); 
		CCSpriteFrame *frameB = frameCache->spriteFrameByName(tempB); 
		animations->addObject(frameA);
		animations->addObject(frameB);
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animations,1.0f);
		animation->setDelayPerUnit(0.3f);
		animation->setLoops(-1);
		char tempName[30];
		sprintf(tempName,"gw%02dAction",i);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation,tempName); 
	}
	do //烟雾;
	{
		//怪物烟雾消失帧动画;
		CCArray* animations = CCArray::create();
		char temp[20];
		for (int i = 1;i<=6;i++)
		{
			sprintf(temp,"addEnemy%d.png",i);
			CCSpriteFrame* frame = frameCache->spriteFrameByName(temp);
			animations->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animations);
		animation->setDelayPerUnit(0.1f);
		animation->setLoops(1);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation,"addEnemy");
	} while (0);

	do //标记;
	{
		CCArray* animations2 = CCArray::create();
		CCSpriteFrame* frame1 = frameCache->spriteFrameByName("at1.png");
		CCSpriteFrame* frame2 = frameCache->spriteFrameByName("at2.png");
		animations2->addObject(frame1);
		animations2->addObject(frame2);
		CCAnimation* animation2 = CCAnimation::createWithSpriteFrames(animations2);
		animation2->setDelayPerUnit(0.3f);
		animation2->setLoops(-1);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2,"addTarget");
	} while (0);

	do //建造升级;
	{
		CCArray* animations34 = CCArray::create();
		CCSpriteFrame* frame3 = frameCache->spriteFrameByName("at3.png");
		CCSpriteFrame* frame4 = frameCache->spriteFrameByName("at4.png");
		animations34->addObject(frame3);
		animations34->addObject(frame4);
		CCAnimation* animation34 = CCAnimation::createWithSpriteFrames(animations34);
		animation34->setDelayPerUnit(0.3f);
		animation34->setLoops(-1);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation34,"addTarget2");
	} while (0);

	do //基地跳动;
	{
		int j = 0;
		for(int j = 0 ;j<10;j++)
		{
			CCArray *animations = CCArray::createWithCapacity(2); 

			char tempA[20] = {0};
			sprintf(tempA,"life%d",j);
			char tempB[20] = {0};
			sprintf(tempB,"life%d",j);
			strcat(tempA,"0.png");
			strcat(tempB,"1.png");

			CCSpriteFrame *frameA = frameCache->spriteFrameByName(tempA);
			CCSpriteFrame *frameB = frameCache->spriteFrameByName(tempB);
			animations->addObject(frameA); 
			animations->addObject(frameB); 

			CCAnimation* animation = CCAnimation::createWithSpriteFrames(animations,0.2f); 
			animation->setDelayPerUnit(0.3f);
			animation->setLoops(-1);
			char tempa[23];
			sprintf(tempa,"life%d",10-j);

			CCAnimationCache::sharedAnimationCache()->addAnimation(animation,tempa); 
		}
	} while (0);

	do 
	{
		CCArray* animations2 = CCArray::create();
		CCSpriteFrame* frame1 = frameCache->spriteFrameByName(BULLET_3_1);
		CCSpriteFrame* frame2 = frameCache->spriteFrameByName(BULLET_3_2);
		CCSpriteFrame* frame3 = frameCache->spriteFrameByName(BULLET_3_3);
		CCSpriteFrame* frame4 = frameCache->spriteFrameByName(BULLET_3_4);
		CCSpriteFrame* frame5 = frameCache->spriteFrameByName(BULLET_3_5);
		CCSpriteFrame* frame6 = frameCache->spriteFrameByName(BULLET_3_6);
		animations2->addObject(frame1);
		animations2->addObject(frame2);
		animations2->addObject(frame3);
		animations2->addObject(frame4);
		animations2->addObject(frame5);
		animations2->addObject(frame6);
		CCAnimation* animation2 = CCAnimation::createWithSpriteFrames(animations2);
		animation2->setDelayPerUnit(0.08f);
		animation2->setLoops(1);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2,"bullet3_bomb");
	} while (0);

	haveUI = true;

}

void ZGame::backtoXuanguan1( CCObject* obj )
{
	destory();
	m_game->setState(G_ST_NULL);
	m_game->removeAllChildrenWithCleanup(true);
	removeCurFrames();
	m_mainmenu->setUIState(UISTATE_SELECTION);
	m_mainmenu->initMainMenu();
	m_gamestate->intoNextState(GST_MAINMENU,1);
	
}

void ZGame::removeCurFrames()
{
	array1(int) frames = m_gameRes->getCurFrames();
	for (std::vector<int>::iterator iter = frames.begin(); iter != frames.end(); ++iter)
	{
		m_gameRes->ZUI_removeAFrame(*iter);
	}
}

void ZGame::reGame( CCObject* obj )
{
	FOREACH_ATKOBJ
		obj->pauseSchedulerAndActions();
	FOREACH_END

	setState(G_ST_MENU);
	m_gameRes->ZUI_show(this, Frame_erciqueren1, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, true, 10010); // 设置数字:金钱;
	m_gameRes->ZUI_setClickListener(this, Frame_erciqueren1, Frame_erciqueren1_or_3, toucheventselector(ZGame::ReStart));
	m_gameRes->ZUI_setClickListener(this, Frame_erciqueren1, Frame_erciqueren1_or_4, toucheventselector(ZGame::Resume));
	isPause = true;
}

void ZGame::ReStart( CCObject* obj )
{
	//恢复游戏;
	FOREACH_ATKOBJ
		obj->resumeSchedulerAndActions();
	FOREACH_END
	setState(G_ST_GAMEING);
	isPause = false;

	/*
	销毁原地图;
	初始化金钱与波数;
	重置计时器;
	建立新地图;
	*/
	m_gameRes->ZUI_removeAFrame(Frame_erciqueren1);
	destory();
	int t_coin = ReadInfo::getInstance()->towerSortForMap[curLv][DCOUNT_TOWERFORMAP-1];
	coin = t_coin;
	m_gameRes->ZUI_setNumForNumbar(Frame_youxijiemain,Frame_youxijiemain_or_76,coin); // 设置数字:关卡;
	curWave = 0;
	t_DemonRushClock = second(-3);
	initMap();
}

void ZGame::Resume( CCObject* obj )
{
	//恢复游戏;
	FOREACH_ATKOBJ
		obj->resumeSchedulerAndActions();
	FOREACH_END
	setState(G_ST_GAMEING);
	isPause = false;

	m_gameRes->ZUI_removeAFrame(Frame_erciqueren1);
}

void ZGame::GameInit()
{
	/*
	销毁点击菜单;
	初始化金钱与波数;
	重置计时器;
	建立新地图;
	*/
	CC_SAFE_DELETE(m_towerChoose);
	CC_SAFE_DELETE(m_towerUpgrade);
	ReadInfo* inf = ReadInfo::getInstance();
	curLv = m_gamestate->curLevel;
	int t_coin = ReadInfo::getInstance()->towerSortForMap[curLv][DCOUNT_TOWERFORMAP-1];
	coin = t_coin/*+10000*/;
	m_gameRes->ZUI_setNumForNumbar(Frame_youxijiemain,Frame_youxijiemain_or_76,coin); // 设置数字:关卡;
	curWave = 0;
	t_DemonRushClock = second(-1);
	initMap();

}

void ZGame::initMap()
{
	destory();
	m_map = MapList::create(curLv+1);
	addChild(m_map,-1);	

	//Demon * de = Demon::create(curWave+1);
	//de->InvadeMap(m_map);
	//de->setMaxHP(10000);
	//de->setCurHP(10000);
	//de->setMoveSpeed(10);
	
}

void ZGame::clockStep()
{
	t_DemonRushClock++; //计时器;

	const int rushNextDemonInterval = 1*FPS_RATE; //每秒刷新一个怪;

	const int curWaveDemonCount = 10;     //每波刷新10个怪;

	for (int i =0;i<curWaveDemonCount;i++)
	{
		if (t_DemonRushClock == i*rushNextDemonInterval)
		{

			Demon::create(curWave+1)->InvadeMap(m_map);

			if (i == curWaveDemonCount-1)
			{
				t_DemonRushClock = second(-5);//间隔5秒刷新下一波怪;
				curWave++;
			}
		}
	}
}

void ZGame::AllTowerAutoShoot()
{
	CCObject* obj;
	CCARRAY_FOREACH_REVERSE(Shooter::shooterArray,obj)
	{
		Shooter* shoter = (Shooter*)obj;
		shoter->Radar();
	}
}

void ZGame::GameStep()
{
	AllTowerAutoShoot();
	if (m_map)
	{
		if (m_map->mapHP<=0)
		{
			m_map->removeFromParentAndCleanup(true);
			m_map = NULL;
		}
		else
		{
			clockStep();
			m_map->update();
		}
	}
}

void ZGame::SpeedXX( CCObject* obj )
{

	if (isDoubleSpeed)
	{
		isDoubleSpeed = false;
		if (!isPause)
		{
			CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0f);
			//m_gameRes->ZUI_setButtonState(Frame_youxijiemain,Frame_youxijiemain_or_64,BTN_ST_NOR);
		}
	}
	else
	{
		isDoubleSpeed = true;
		if (!isPause)
		{
			CCDirector::sharedDirector()->getScheduler()->setTimeScale(2.0f);
			m_gameRes->ZUI_setButtonState(Frame_youxijiemain,Frame_youxijiemain_or_64,BTN_ST_PRES);//BTN_ST_PRES
		}
	}
}

void ZGame::PauseGame( CCObject* obj )
{
	if (isPause)
	{
		isPause = false;
		if (isDoubleSpeed)
		{
			CCDirector::sharedDirector()->getScheduler()->setTimeScale(2.0f);
			
		}
		else
		{
			CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0f);
		}
	}
	else
	{
		isPause = true;
		CCDirector::sharedDirector()->getScheduler()->setTimeScale(0);
	}
}

BatteryChoice* ZGame::ShareBC()
{
	if(m_towerChoose == NULL)
	{
		m_towerChoose = new BatteryChoice();
		m_towerChoose->init(m_gamestate->curLevel);
	}
	return m_towerChoose;
}

BatteryUpgrade* ZGame::ShareUG()
{
	if (m_towerUpgrade == NULL)
	{
		m_towerUpgrade = new BatteryUpgrade();
		m_towerUpgrade->init();
	}
	return m_towerUpgrade;
}

bool ZGame::touchAtkable(float x,float y)
{
	CCPoint touchpoint = ccp(x,y);

	for (int i = 0 ;i<Atkable::AtkableArray->count();i++)
	{
		Atkable* obj = (Atkable*)Atkable::AtkableArray->objectAtIndex(i);
		CCRect rect = obj->getBox();

		if (rect.containsPoint(touchpoint))
		{
			Marker::create(obj);
			return true;
		}
	}

	return false;
}

bool ZGame::pay( int price )
{
	int need = price;
	if (coin>=price)
	{
		coin-=need;
		m_gameRes->ZUI_setNumForNumbar(Frame_youxijiemain,Frame_youxijiemain_or_76,coin); 
		return true;
	}
	return false;
}



NAMESPACE_ZJG_END