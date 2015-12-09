#include "GameState.h"
#include "InfoToJava.h"
#include "SMainMenu.h"
#include "XFrameID.h"
#include "XAnimationID.h"
#include "XAnimation/XSkin.h"
#include "SimpleAudioEngine.h"  
#include "MRecord.h"
#include "Tools.h"
#include "ZGame.h"
#include "TeachManager.h"
#include "GameInfo/ReadInfo.h"
#include "Map/Cell.h"
//#include "../Game_Analytics_SDK_Cocos_3/include/TalkingData.h"
USING_NS_CC;
GameState* GameState::gmstate;
SResManager* GameState::m_resManager;
ZGame* GameState::m_gameLayer;
using namespace CocosDenshion;  
void GameState::pureGS()
{
	gmstate->removeFromParent();
}
GameState::~GameState()
{

	if(gmstate->taskstrings)
	{
		CC_SAFE_DELETE(gmstate->taskstrings);
	}

	CC_SAFE_DELETE(InfoToJava::sender);
	if(SMainMenu::game_mainmenu)
	{
		SMainMenu::game_mainmenu->removeFromParent();
		SMainMenu::game_mainmenu->removeAllChildren();
		CC_SAFE_DELETE(SMainMenu::game_mainmenu);
		SMainMenu::game_mainmenu = NULL;
	}
	if(m_gameLayer)
	{
		m_gameLayer->removeFromParent();
		m_gameLayer->removeAllChildren();
		CC_SAFE_DELETE(m_gameLayer);
	}
	if(m_resManager)
	{
		CC_SAFE_DELETE(m_resManager);
		m_resManager = NULL;
	}

	do 
	{
		Atkable::AtkableArray->removeAllObjects();
		Atkable::AtkableArray->release();
		Shooter::shooterArray->removeAllObjects();
		Shooter::shooterArray->release();

	} while (0);

	if (cells.size()>0)
	{
		Cell::deleteCells();
	}
	delete ReadInfo::getInstance();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	//	CCLOG(CCTextureCache::sharedTextureCache()->description());//监测当前有多少纹理未被释放
	//CC_SAFE_DELETE(gmstate);
}
GameState* GameState::sharedGS()
{
	if(gmstate == NULL)
	{
		m_gameRes->loadResConfig();
		gmstate = GameState::create();
		gmstate->loginReward.resize(7);
		for(int i=0;i<7;i++)
		{
			gmstate->loginReward[i] = 0;
		}
		gmstate->setTouchEnabled(true);
		gmstate->loadMusic = true;
		gmstate->initLevelInfo();
		gmstate->initLevelStar();
		gmstate->initLevelTotal();
		gmstate->initTeaching();
		gmstate->initstaticArray();
		gmstate->loadHeroInfo();
		gmstate->loadTeachInfo();
		gmstate->taskstrings = NULL;
		gmstate->taskstrings = CCDictionary::createWithContentsOfFile("task.xml");
		gmstate->taskstrings->retain();
		gmstate->screenPIXW = SCREEN_W_HALF*2;
		gmstate->screenPIXH = SCREEN_H_HALF*2;

		gmstate->setState(GST_SSTARTPAGE,-1);
		gmstate->curScreenW = S_WIDTH;
		gmstate->curScreenH = S_HEIGHT;
		gmstate->showShop = false;
		gmstate->shopIndex = -1;
		gmstate->firstInMainMenu = true;
		if(!m_sendor->musicOn)
		{
			gmstate->effVolume = 0;
			gmstate->bgmVolume = 0;
		}else
		{
			gmstate->effVolume = 0.5f;
			gmstate->bgmVolume = 0.5f;
		}
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(gmstate->effVolume);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(gmstate->bgmVolume);
//		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BGM_START, true);
	}
	return gmstate;
}
SResManager* GameState::sharedRes()
{
	if(m_resManager == NULL)
	{
		m_resManager = new SResManager();
	}
	return m_resManager;
}
ZGame* GameState::sharedGame()
{
	if(m_gameLayer == NULL)
	{
		m_gameLayer = new ZGame();
		m_gameLayer->retain();
	}
	return m_gameLayer;
}
CCScene* GameState::scene()
{
	gmstate = NULL;
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	// 'layer' is an autorelease object
	//GameState *layer = GameState::create();

	// add layer as a child to scene
	scene->addChild(m_gamestate);

	//m_gamestate->setTouchEnabled(true);

	return scene;
}

void GameState::playBGM(const char* path)
{
	CCAssert( path != NULL || strcmp(path, "") != 0, "The BGM is invial");
	// 停止当前的BGM
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}

	// 播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(path, true);
}

void GameState::stopBGM()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void GameState::playEffMusic(const char* path)
{
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(path);
}
void GameState::playButtonMusic(int type)
{
	string path= "";
	switch(type)
	{
	case BTN_MUSIC_OK:
		path = "music/OK.ogg";
		break;
	case BTN_MUSIC_CANCEL:
		path = "music/CANCEL.ogg";
		break;
	case MUSIC_GMONEY:
		path = "music/getMoney.ogg";
		break;
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(path.c_str());
}
// on "init" you need to initialize your instance
bool GameState::init()
{

	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	srand((unsigned)time(NULL));
	this->schedule(schedule_selector(GameState::update),1.0f/FPS_RATE);
	return true;
}
void GameState::initTasks()
{
}

void GameState::loginReward_show()
{
}
void GameState::loginReward_get_click(CCObject*sender)
{
}
/************************************************************************/
/* 道具不足                                                                     */
/************************************************************************/
void GameState::goodsNotEnough(int type)//道具不足
{

}
void GameState::tip_buyGoods_OK_click(CCObject*sender)
{
}
void GameState::tip_buyGoods_CANCEL_click(CCObject*sender)
{
}

void GameState::initLevelInfo()
{
	levelInfo.resize(LEVELINFO_LEN);
	levelInfo[LEVEL_PROCESS]	= 10; // 关卡进度
	levelInfo[LEVEL_BULLETCOUNT]= 12; // 当前关卡子弹数
	levelInfo[LEVEL_COINCOUNT]	= 10000; // 金钱数
	levelInfo[LEVEL_STAR]		= 1; // 关卡星级
	curLevel = 0;					 // 当前关卡
}

void GameState::initLevelStar()
{
	levelStars.resize(LEVEL_COUNT);
	for (int i = 0; i < LEVEL_COUNT; ++i)
	{
		levelStars[i] = 0;
	}

}
void GameState::initLevelTotal()
{
	levelTotalInfo.resize(LEVELTOTAL_LEN);
	levelTotalInfo[LEVELTOTAL_USEBUTTLECOUNT]	= 0;
	levelTotalInfo[LEVELTOTAL_ARMORTOTAL]		= 0;
	levelTotalInfo[LEVELTOTAL_THROUGHTOTAL]		= 0;
	levelTotalInfo[LEVELTOTAL_SHOTTOTAL]		= 0;
}

void GameState::initTeaching()
{
	teachProcess = 0;
	inTeachSteate = 1;	// 第一次进入游戏存档 
	curTeachStep = 0; // 当前教学进度
	preTeachStep = 0; // 前一个教学进度
	curTeachFream = 0; // 当前教学界面
	preTeachFream = 0; // 前一个教学界面
	curBlockCount = 0; // 当前教学的红框数目
	curTouchType = 0; // 教学过程中的屏幕锁定类型
	teachDis = NULL; // 教学信息
}

void GameState::loadTeachInfo()
{
	// 如果是教学状态，则加载教学信息
	if (inTeachSteate == 1)
	{
		std::string fillPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("teach.plist");
		teachDis = CCDictionary::createWithContentsOfFile("teach.plist");
		teachDis->retain();
		CCAssert(teachDis, "create the teaching info failed!");
	}
}

void GameState::intoCurTeachStep()
{
	setTeachStep(curTeachStep);
}

void GameState::intoNextTeachStep(float dt)
{
	curTeachStep++;
	m_gamestate->setDelayForAction(dt, CCCallFunc::create(this,callfunc_selector(GameState::intoCurTeachStep)));
}

void GameState::setTeachStep(int step)
{
	if (step > 7 || step < 0 || curLevel > 2)
	{
		return;
	}
	curTeachStep = step;

	char pszLevel[10] = {0};
	char pszStep[10] = {0};
	
	sprintf(pszLevel, "level%d", curLevel + 1);
	sprintf(pszStep, "step%d", step);

	CCDictionary* levelDis = dynamic_cast<CCDictionary*>(teachDis->objectForKey(pszLevel)) ;
	CCDictionary* stepDis = dynamic_cast<CCDictionary*>(levelDis->objectForKey(pszStep));

	int freamId = atoi(stepDis->valueForKey("fream_id")->getCString());	// 得到fream的编号
	std::string teachText = stepDis->valueForKey("text")->getCString(); // 得到对话框文字
	curTeachFream = freamId;
	int count = atoi(stepDis->valueForKey("rect_count")->getCString()); // 当前教学矩形的数目
	curBlockCount = count;
	int type = atoi(stepDis->valueForKey("touch_type")->getCString()); // 锁定屏幕的方式
	curTouchType = type;

	int toNexType = atoi(stepDis->valueForKey("into_next_type")->getCString()); // 切换教学步骤的方式
	int hand = atoi(stepDis->valueForKey("hand")->getCString()); // 是否有手形提示

	// 删除上一步的教学
	removePreTeachFream();

	// 如果当前有矩形界面，则显示出来
	if (freamId != -1)
	{
		m_gameRes->ZUI_show(m_game, freamId, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, true, 10101);
	}

	// 设置矩形框的信息
	ClipRectInfo clipInfo;
	clipInfo.clipPoint = ccp(0, 0);
	clipInfo.clipSize = ccp(0, 0);
	if (count == 1)
	{
		CCPoint pt = m_gameRes->getPosition(freamId, 0);
		CCPoint clipPos(pt.x + curScreenW/2, pt.y + curScreenH/2);		
		clipInfo.clipPoint = clipPos;
		clipInfo.clipSize = m_gameRes->ZUI_getSize(freamId, 0);
	}
	if (hand == 1)
	{
		float x = 0, y = 0;
		if (count == 1)
		{
			
			x = clipInfo.clipPoint.x;
			y = clipInfo.clipPoint.y - clipInfo.clipSize.height/2 - 10;
		}
		else
		{
			x = curScreenW*2/3;
			y = curScreenH/4;
		}

		// 暂时特殊处理
		if (curLevel == 0 && step == 4)
		{
			x = curScreenW*2/3;
			y = curScreenH/4;
		}
	}

	
	
	
	if (freamId != -1)
	{
		TeachingFream* teachFream = TeachingFream::create(clipInfo);
		teachFream->setTag(10000);
		m_game->addChild(teachFream, 10100);
	}
	
	if (toNexType == TEACH_STEPTYPE_OTHER)
	{
		removeCurTeachFream(2.0f);
	}
	else if (toNexType == TEACH_STEPTYPE_END)
	{
	//	removeCurTeachFream(2.0f);
		teachProcess++;
	//	saveHeroInfo();
	}
	else if (toNexType == TEACH_STEPTYPE_ALLEND)
	{
		removeCurTeachFream(2.0f);
		teachProcess++;
	//	saveHeroInfo();
	}

	preTeachFream = freamId;
	preTeachStep = step;

	// 教学结束
	if (curTeachStep >= 7 && curLevel >= 2)
	{
		inTeachSteate = 0;
		// 保存数据
		saveHeroInfo();
	}
}

bool GameState::canTouchdPos(int x, int y)
{
	if (curTeachStep <= 0)
	{
		return true;
	}

	bool bRet = true;
	if (curBlockCount == 1)
	{
		bRet = m_gameRes->touchInBlock(curTeachFream, 0, x, y);
	}
	if (curTouchType == 1)
	{
		  bRet = false;
	}

	return bRet;
}

// 延迟一段时间后删除教学界面
void GameState::removeCurTeachFream(float dt)
{
	m_gamestate->setDelayForAction(dt, CCCallFunc::create(this,callfunc_selector(GameState::removeCurTeachFream)));
}
void GameState::removeCurTeachFream()
{
	m_gameRes->ZUI_removeAFrame(curTeachFream);
	if (m_game->getChildByTag(10000))
	{
		TeachingFream* fream = dynamic_cast<TeachingFream*>(m_game->getChildByTag(10000));
		fream->removeAllChildren();
		fream->removeFromParent();
	}
}
void GameState::removePreTeachFream(float dt)
{
	m_gamestate->setDelayForAction(dt, CCCallFunc::create(this,callfunc_selector(GameState::removeCurTeachFream)));
}
void GameState::removePreTeachFream()
{
	m_gameRes->ZUI_removeAFrame(preTeachFream);
	if (m_game->getChildByTag(10000))
	{
		TeachingFream* fream = dynamic_cast<TeachingFream*>(m_game->getChildByTag(10000));
		fream->removeAllChildren();
		fream->removeFromParent();
	}
}

/**
*	添加Talking监测事件
*	@param id: 监测事件的id
*/
void GameState::addTalkingEvent(int id)
{
/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string eventId("");
	EventParamMap paramMap;
	switch (id)
	{
	case event_toLevel:
		{
			char level[32] = { 0 };
			sprintf(level, "%d", curLevel + 1);
			paramMap.insert(EventParamPair("toLevel", level));
			eventId = EVENT_TO_LEVEL;
		}
		break;
	case event_restartFromGaming:
		{
			char level[32] = { 0 };
			sprintf(level, "%d", curLevel + 1);
			paramMap.insert(EventParamPair("currentLevel", level));
			eventId = EVENT_RESTART_GAMING;
		}
		break;
	case event_restartFromSuccess:
		{
			char level[32] = { 0 };
			sprintf(level, "%d", curLevel + 1);
			paramMap.insert(EventParamPair("currentLevel", level));
			eventId = EVENT_RESTART_SUCCESS;
		}
		break;
	case event_restartFromFailed:
		{
			char level[32] = { 0 };
			sprintf(level, "%d", curLevel + 1);
			paramMap.insert(EventParamPair("currentLevel", level));
			eventId = EVENT_RESTART_FAILED;
		}
		break;
	case event_toNextFromSuccess:
		{
			char level[32] = { 0 };
			sprintf(level, "%d", curLevel + 1);
			paramMap.insert(EventParamPair("currentLevel", level));
			eventId = EVENT_NEXT_SUCCESS;
		}
		break;
	case event_useArmor:
		{
			char level[32] = { 0 };
			sprintf(level, "%d", curLevel + 1);
			paramMap.insert(EventParamPair("currentLevel", level));
			eventId = EVENT_ARMOR;
		}
		break;
	case event_useThrough:
		{
			char level[32] = { 0 };
			sprintf(level, "%d", curLevel + 1);
			paramMap.insert(EventParamPair("currentLevel", level));
			eventId = EVENT_THROUGH;
		}
		break;
	case event_useShot:
		{
			char level[32] = { 0 };
			sprintf(level, "%d", curLevel + 1);
			paramMap.insert(EventParamPair("currentLevel", level));
			eventId = EVENT_SHOT;
		}
		break;
	case event_levelSuccessed:
		{
			char info[64] = { 0 };
			sprintf(info, "%d", curLevel + 1);
			paramMap.insert(EventParamPair("currentLevel", info));
			memset(info, 0, sizeof(info));
			sprintf(info, "%d_%d", curLevel + 1, levelTotalInfo[LEVELTOTAL_USEBUTTLECOUNT]);
			paramMap.insert(EventParamPair("usedBulletTotal", info));
			memset(info, 0, sizeof(info));
			sprintf(info, "%d", levelTotalInfo[LEVELTOTAL_ARMORTOTAL]);
			paramMap.insert(EventParamPair("usedArmorTotal", info));
			memset(info, 0, sizeof(info));
			sprintf(info, "%d", levelTotalInfo[LEVELTOTAL_THROUGHTOTAL]);
			paramMap.insert(EventParamPair("usedThoughTotal", info));
			memset(info, 0, sizeof(info));
			sprintf(info, "%d", levelTotalInfo[LEVELTOTAL_SHOTTOTAL]);
			paramMap.insert(EventParamPair("usedShotTotal", info));

			eventId = EVENT_LEVEL_SUCCESSED;
		}
		break;
	default:
		break;
	}
	TDCCTalkingDataGA::onEvent(eventId.c_str(), &paramMap);

	#endif*/
}

/**
*	延时一段时间后调用callfunc函数
*	@param dt: 延时时间
*	@param callfunc：无参回调函数
*/
void GameState::setDelayForAction(float dt, CCCallFunc* callfunc)
{
	// 创建延时
	CCDelayTime *delay = CCDelayTime::create(dt);
	CCFiniteTimeAction* seq = CCSequence::create(delay, callfunc, NULL);
	this->runAction(seq);
}

/************************************************************************/
/* 设置游戏状态   
newState新状态              
nextState下一个状态及   newState执行完后的状态
/************************************************************************/
void GameState::setState(int newState,int nextState)
{
	array1(int)curFrames = m_gameRes->getCurFrames();
	int preSeat = curState;

	switch(newState)
	{
	case GST_SSTARTPAGE:
		startPage = new SStartPage();
		startPage->retain();
		addChild(startPage);
		// 加载音乐
		initMusic();
		break;
	case GST_MAINMENU:
//		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BGM_START, true);
		initTasks();
		m_mainmenu->removeFromParent();
		m_mainmenu->initRes();
		addChild(m_mainmenu);
		if(m_gamestate->firstInMainMenu)m_gamestate->firstInMainMenu = false;
		break;
	case GST_GAMEING:
		//curTeachStep = 0; // 教学设置到第一步
		//if (curLevel > levelInfo[LEVEL_PROCESS] && curLevel <= MAX_LEVEL)
		//{
		//	levelInfo[LEVEL_PROCESS] = curLevel;
		//}
		//m_game->setState(G_ST_LOADING);
		m_game->intoNextState(G_ST_LOADING,1);
		m_game->destory();
		m_game->removeFromParent();
		addChild(m_game);
		break;
	}
	curState = newState;
	this->nextState = nextState;
	//switch(preSeat)
	//{
	//case GST_MAINMENU:
	//	removeChild(m_mainmenu);
	//	break;
	//case GST_GAMEING:
	//	removeChild(m_game);
	//	break;
	//}
	if(preSeat == GST_SSTARTPAGE)
	{
		startPage->removeFromParent();
		CC_SAFE_DELETE(startPage);
	}
	for(int i=0;i<curFrames.size();i++)
	{
		m_gameRes->ZUI_removeAFrame(curFrames[i]);
	}
	curFrames.clear();

	CCLog("Frame Clean");
}
void GameState::intoNextState(int nextState,int delayt)
{
	this->delayt = delayt;
	this->nextState = nextState;
/*	if(nextState>=0)
	{
		setState(nextState,-1);
	}*/
}
/************************************************************************/
/* 游戏主逻辑                                                                     */
/************************************************************************/
void GameState::update(float t)
{
	if(delayt>=0 && nextState>=0)
	{
		delayt--;
		if(delayt<=0)
		{
			setState(nextState,-1);

		}
	}
	switch(curState)
	{
	case GST_MAINMENU:
		m_mainmenu->update();
		break;
	case GST_GAMEING:
		m_game->update(t);
		break;
	case GST_SSTARTPAGE:
		startPage->update();
		break;
	}
}
CCTexture2D* GameState::getATexture(float tid)
{
	return NULL;
}
/*void GameState::registerWithTouchDispatcher()  
{  
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
} */
void GameState::ccTouchesBegan(CCSet *pTouch, CCEvent *pEvent)
{  
	CCSetIterator iter = pTouch->begin();
	for(;iter!=pTouch->end();iter++)
	{
		CCTouch * mytouch=(CCTouch *)(* iter);
		CCPoint cp=mytouch->getLocation();
		//修正坐标
		float px = cp.x;  
		float py = cp.y;
		px =px* S_WIDTH / m_gamestate->curScreenW;
		py =py* S_HEIGHT / m_gamestate->curScreenH;
		m_gameRes->ccTouchesBegan(px,py);
		switch(curState)
		{
		case GST_MAINMENU:
			m_mainmenu->touchBegin(px,py);
				break;
		case GST_GAMEING:
			m_game->touchBegan(px,py);
			break;
		}
	}
} 

void GameState::ccTouchesMoved(CCSet *pTouch, CCEvent *pEvent)
{
	CCSetIterator iter = pTouch->begin();
	for(;iter!=pTouch->end();iter++)
	{
		CCTouch * mytouch=(CCTouch *)(* iter);
		CCPoint cp=mytouch->getLocation();
		//修正坐标
		float px = cp.x;  
		float py = cp.y;
		px =px* S_WIDTH / m_gamestate->curScreenW;
		py =py* S_HEIGHT / m_gamestate->curScreenH;
		m_gameRes->ccTouchesMoved(px,py);
		switch(curState)
		{
		case GST_MAINMENU:
			m_mainmenu->touchMoved(px,py);
			break;
		case GST_GAMEING:
			m_game->touchMoved(px,py);
			break;
		}
	}
} 

void GameState::ccTouchesEnded(CCSet *pTouch, CCEvent *pEvent)
{  
	CCSetIterator iter = pTouch->begin();
	for(;iter!=pTouch->end();iter++)
	{
		CCTouch * mytouch=(CCTouch *)(* iter);
		CCPoint cp=mytouch->getLocation();
		//修正坐标
		float px = cp.x;  
		float py = cp.y;
		px =px* S_WIDTH / m_gamestate->curScreenW;
		py =py* S_HEIGHT / m_gamestate->curScreenH;
		m_gameRes->ccTouchesEnded(px,py);
		switch(curState)
		{
		case GST_MAINMENU:
			m_mainmenu->touchEnded(px,py);
				break;
		case GST_GAMEING:
			m_game->touchEnded(px,py);
			break;
		}
	}
} 
/************************************************************************/
/* 设置音乐                                                                     */
/************************************************************************/
void GameState::setMusic_click(CCObject*sender)
{
	switch(m_gamestate->curState)
	{
	case GST_MAINMENU:
		break;
	case GST_GAMEING:
		break;
	}
}

void GameState::cb_shackChacked(CCObject*sender,bool checked)
{
	m_gamestate->shacked = checked;
}
void GameState::cb_sortChecked(CCObject*sender,bool checked)
{
	m_gamestate->sortByLeft = checked;
}
void GameState::setMusic_back_click(CCObject*sender)
{
	switch(m_gamestate->curState)
	{
	case GST_MAINMENU:
		break;
	case GST_GAMEING:
		break;
	}
	m_gamestate->saveHeroInfo();
}
//音乐值改变
void GameState::music_ValueChanged(CCObject*sender,float svalue)
{
	m_gamestate->bgmVolume = svalue/100;
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m_gamestate->bgmVolume);
	if(svalue <= 0.01f)
	{
		m_gameRes->ZUI_setCheckBoxState(Frame_shezhi, Frame_shezhi_or_22, false);
	}
	else
	{
		m_gameRes->ZUI_setCheckBoxState(Frame_shezhi, Frame_shezhi_or_22, true);
	}
}
//音效值改变
void GameState::music_effect_ValueChanged(CCObject*sender,float svalue)
{
	m_gamestate->effVolume = svalue/100;
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_gamestate->effVolume);
	if(svalue <= 0.01f)
	{
		m_gameRes->ZUI_setCheckBoxState(Frame_shezhi, Frame_shezhi_or_24, false);
	}
	else
	{
		m_gameRes->ZUI_setCheckBoxState(Frame_shezhi, Frame_shezhi_or_24, true);
	}
}
/************************************************************************/
/* 商店                                                                     */
/************************************************************************/
void GameState::setGoodsCount()
{
}
void GameState::shop_show()
{
	shopIndex = -1;
	showShop = true;
	setGoodsCount();
}
void GameState::shop__back_click(CCObject*sender)
{
	switch(m_gamestate->curState)
	{
	case GST_MAINMENU:
		break;
	case GST_GAMEING:
		break;
	}
}
void GameState::sendMessageResult(int type,int code)
{
	if(code == RCODE_OK)
	{
	}
}
void GameState::shop__goods1_click(CCObject*sender)
{
	m_sendor->sendInfo(SMS_KEY_GOLD_1);
	sendMessageResult(SMS_KEY_GOLD_1,RCODE_OK);
}
void GameState::shop__goods2_click(CCObject*sender)
{
	//sendMessageResult(SMS_KEY_GOLD_2,RCODE_OK);//xs_test
	m_sendor->sendInfo(SMS_KEY_GOLD_2);
}
void GameState::shop__goods3_click(CCObject*sender)
{
	m_sendor->sendInfo(SMS_KEY_GOLD_3);
}
void GameState::shop__goods4_click(CCObject*sender)
{
}
void GameState::shop__goods5_click(CCObject*sender)
{
}
void GameState::shop__goods6_click(CCObject*sender)
{
}
/************************************************************************/
/* 任务界面                                                                     */
/************************************************************************/

void GameState::taskpage_show()
{
}
void GameState::task__back_click(CCObject*sender)
{
	if(curState == GST_GAMEING)
	{
	}

}
/************************************************************************/
/* 金币不足                                                                     */
/************************************************************************/
void GameState::noMoney_show()
{
}
void GameState::noMoney_back_click(CCObject*sender)
{
}
void GameState::loadHeroInfo()
{
	if(MRecord::openRecord_reader())
	{
		inTeachSteate = MRecord::readInt();
		teachProcess = MRecord::readInt();
		levelInfo[LEVEL_PROCESS] = MRecord::readInt(); // 关卡进度
		levelInfo[LEVEL_COINCOUNT] = MRecord::readInt(); // 金币数

		// 关卡星级
		for (int i = 0; i < levelInfo[LEVEL_PROCESS]; i++)
		{
			levelStars[i] = MRecord::readInt();
		}

		MRecord::closeRecord_reader();
	}else//没有存档
	{

	}
}
void GameState::saveHeroInfo()
{
	MRecord::openRecord_saver();
	
	MRecord::writeInt(inTeachSteate); // 是否第一次进入游戏
	MRecord::writeInt(teachProcess); // 教学进度
	MRecord::writeInt(levelInfo[LEVEL_PROCESS]);// 关卡进度
	MRecord::writeInt(levelInfo[LEVEL_COINCOUNT]);// 金币数

	// 关卡星级
	for (int i = 0; i < levelInfo[LEVEL_PROCESS]; i++)
	{
		MRecord::writeInt(levelStars[i]);
	}

	MRecord::closeRecord_saver();
}
bool GameState::chackTask()
{
	return false;
}


void GameState::loadGameingInfo()
{
	seveGameIngInfo(0,0,false);
}
void GameState::seveGameIngInfo(int beishu,unsigned long long dizhu,bool isLandor)
{
}
void GameState::initMusic()
{
	//预加载音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(EFF_BUTTONCLICK);// 点击按钮
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(EFF_HERODEAD);// 主角死亡
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(EFF_ENEMYDEAD);// 怪物死亡
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(EFF_BOXBREAK);// 木箱粉碎
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(EFF_BOMBEXPLORE);// 炸弹爆炸
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(EFF_BUTTLESHOOT);// 子弹发射
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(EFF_BUTTLEREBOUND);// 子弹反弹	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(EFF_ARMOR);		// 英雄召唤护盾

	// 预加载BGM
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BGM_ICE);// 冰场景
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BGM_MAINMENU);// 封面
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BGM_GRAVEYARD);// 墓地紫色场景
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BGM_FOREST);// 森林沙漠场景
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BGM_SELECTION);// 选关界面
}

void GameState::initstaticArray()
{
	Atkable::AtkableArray->retain();
	Shooter::shooterArray->retain();
}

