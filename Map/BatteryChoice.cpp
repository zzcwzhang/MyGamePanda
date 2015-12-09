#include "BatteryChoice.h"
#include "GameState.h"
#include "ZGame.h"

#define SPRITESIZE 80
#define SPRITESCALE_1 0.75f
#define SPRITESCALE_1_1 1.0f
#define SPRITESCALE_1_2 1.3f
#define SPRITESCALE_2 0.85f


#define kTagBC_LCSP (5)

BatteryChoice::BatteryChoice()
{
	spriteArray = CCArray::create();
	spriteArray->retain();
}

BatteryChoice* BatteryChoice::create(CCNode* node,CCPoint axie )
{
	BatteryChoice * bc = new BatteryChoice;

	if (bc && bc->init(1))
	{
		bc->autorelease();
		
		return bc;
	}
	CC_SAFE_DELETE(bc);
	return NULL;
}

bool BatteryChoice::init(int c_level)
{
	kindList.clear();

	int g_cmap = c_level;

	std::vector<int> vec(ReadInfo::getInstance()->towerSortForMap[g_cmap]);
	for (int i = 0;i<vec.size()-1;i++)
	{
		int Tsort = vec[i];
		if (Tsort > 0)
		{
			kindList.push_back(Tsort-1);
		}
	}

	char str[20];
	memset(str,0,sizeof(str));

	/*
	* 建立图标并最小化;
	*/

	CCSprite* locationSP = CCSprite::createWithSpriteFrameName("addtower1.png");
	locationSP->setPosition(CCPointZero);
	locationSP->setScale(0.0001f);
	locationSP->setTag(kTagBC_LCSP);
	addChild(locationSP);

	for (int i=0;i<kindList.size();i++)
	{
		
		Kind = kindList[i];
		CCSprite* sp;
		
		unsigned int NewTowerGD = 1111;  //方便查找的标记，并无实际作用;
		
		if (Kind>9)//新塔10-13号没有资源，先用旧资源改变颜色代替;
		{
			sprintf(str,"t_%d0.png",Kind-9);
			sp = CCSprite::createWithSpriteFrameName(str);
			sp->setColor(ccc3(255,255,0));
		}
		else
		{
			sprintf(str,"t_%d0.png",Kind);
			sp = CCSprite::createWithSpriteFrameName(str);
		}
		sp->setScale(0.0001f);

		sp->setTag(Kind);//***标记，用于检测图片的序号;

		this->addChild(sp);


		spriteArray->addObject(sp);

		/*
		* 得到金钱并添加标签;
		*/
		CCString* font = CCString::createWithFormat("%d",ReadInfo::getInstance()->footmanarray[Kind][5]);
		bPrice = CCLabelTTF::create(font->getCString(),"fonts/Marker Felt.ttf",17);
		bPrice->setAnchorPoint(CCPointZero);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)|| (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#else
		bPrice->setPosition(ccp(22,5));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		bPrice->setPosition(ccp(28,2));
#endif
#endif
		sp->addChild(bPrice);
	}

	this->setVisible(false);
	m_game->addChild(this,VIEW_HEIGHT);

	return true;
	
}


void BatteryChoice::Appearance()
{
	float actime = 0.2f;

	if (spriteArray->count()>0)
	{
		CCSprite*sprite;
		//防御塔菜单出现动画;
		for (int i =0;i<spriteArray->count();i++)
		{
			sprite = static_cast<CCSprite*>(spriteArray->objectAtIndex(i));
			//计算横排;
			int spRowCount = i%4;

			if (fX>COLUMN_MAX/2)
			{
				spRowCount = -spRowCount;
			}
			//计算纵排;
			int spColCount =  i/4+1;
			if (fY>ROW_MAX/2)
			{
				spColCount = -spColCount;
			}

			CCPoint axie = ccp(spRowCount*ZC_RECTSIZE,spColCount*ZC_RECTSIZE);
			sprite->setPosition(CCPointZero);

			CCScaleTo* st1 = CCScaleTo::create(actime,1.5f);
			CCMoveTo* mt = CCMoveTo::create(actime,axie);
			CCSpawn* spac = CCSpawn::createWithTwoActions(st1,mt);

			sprite->runAction(spac);
		}

		//提示框;
		do 
		{
			CCSprite* sp = (CCSprite*)this->getChildByTag(kTagBC_LCSP);
			CCFadeIn* action = CCFadeIn::create(actime);
			sp->setScale(1.34f);
			sp->runAction(action);
		} while (0);
	}
}

void BatteryChoice::Exeunt()
{

	float acTime = 0.2f;
	if (spriteArray->count()>0)
	{
		CCSprite*sprite;
		for (int i =0;i<spriteArray->count();i++)
		{
			sprite = static_cast<CCSprite*>(spriteArray->objectAtIndex(i));
			CCScaleTo* st2 = CCScaleTo::create(acTime,0.0001f);
			sprite->runAction(st2);
		}
	}

	CCSprite* sp = (CCSprite*)this->getChildByTag(kTagBC_LCSP);
	sp->setScale(0.1f);

	this->runAction(CCFadeOut::create(acTime));
}

void BatteryChoice::touchBegan(int Kind)
{
	//Turret* tower = Turret::createFootMan(node,land,Kind,0);
	//Footman::create(node,land+ccp(ZC_RECTSIZE/2,ZC_RECTSIZE/2),Kind);
}

void BatteryChoice::onEnter()
{
	CCLayer::onEnter();
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(BatteryChoice::checkCoinEnough),"CurrectCoin",NULL);
}

void BatteryChoice::checkCoinEnough(CCObject* obj )
{
	CCInteger* ccoin = (CCInteger*)obj;
	int coin = ccoin->getValue();

	char temp[30];

	unsigned int NewTowerGD = 1111;  //方便查找的标记，并无实际作用;

	if (spriteArray)
	{
		for (int i=0;i<spriteArray->count();i++)
		{
			CCSprite* sp = static_cast<CCSprite*>(spriteArray->objectAtIndex(i));
			ReadInfo* inf = ReadInfo::getInstance();
			int cKind = sp->getTag();
			if (cKind>9)
			{
				cKind -=9;
				
				if (coin<inf->footmanarray[cKind][Footman::bugprice])
				{
					sprintf(temp,"t_%d1.png",cKind);
					sp->initWithSpriteFrameName(temp);
				}
				else
				{
					sprintf(temp,"t_%d0.png",cKind);
					sp->initWithSpriteFrameName(temp);
				}
				sp->setColor(ccc3(255,255,0));
			}
			else
			{
				if (coin<inf->footmanarray[cKind][Footman::bugprice])
				{
					sprintf(temp,"t_%d1.png",cKind);
					sp->initWithSpriteFrameName(temp);
				}
				else
				{
					sprintf(temp,"t_%d0.png",cKind);
					sp->initWithSpriteFrameName(temp);
				}
			}
				
		}
	}
	
}

void BatteryChoice::onExit()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(
		this,
		"CurrectCoin");  // 消息名称;
	CCLayer::onExit();
}

int BatteryChoice::touchEnd( float x,float y )
{
	for (int i=0;i<spriteArray->count();i++)
	{
		CCSprite* sp = (CCSprite*)spriteArray->objectAtIndex(i);
		CCRect rect = sp->boundingBox();
		if (rect.containsPoint(ccp(x,y)-getPosition()))
		{
			return sp->getTag();
		}
	}

	return -1;
}

void BatteryChoice::ShowChoiceMenu( CCPoint mpoint )
{
	CCPoint myPoint = mpoint;
	fX = myPoint.x/SPRITESIZE+1;
	fY = myPoint.y/SPRITESIZE+1;
	this->setPosition(myPoint);
	this->setVisible(true);
	Appearance();
}

BatteryChoice::~BatteryChoice()
{
	
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define CESHI true	


#define kTag_LB 1
#define kTag_SP_Circle 2
#define kTag_LB_Circle 3
#define kTag_SP_UP 4
#define kTag_LB_UP 5
#define kTag_SP_CELL 6
#define kTag_LB_CELL 7
#define kTag_LB_ATK 8
#define kTag_LB_DPS 9 

#define kColorLB ccc3(220,35,220)

BatteryUpgrade::BatteryUpgrade()
{

	tower = NULL;
	uPrice = NULL;
	sPrice = NULL;
	spriteArray = CCArray::create();
	spriteArray->retain();

}

BatteryUpgrade* BatteryUpgrade::create( CCNode* node,Shooter*tower,CCPoint axie )
{
	BatteryUpgrade * Bau = new BatteryUpgrade;

	if (Bau && Bau->init())
	{
		Bau->autorelease();
		return Bau;
	}

	CC_SAFE_DELETE(Bau);
	return NULL;
}

bool BatteryUpgrade::init()
{
	if(!CCLayer::init()) return false;
	
	
	//Levels = tower->getBuildLevel();

	
	//背景;
	CCSprite* bgsp = CCSprite::createWithSpriteFrameName("update_bg.png");
	//bgsp->setPosition(ccp(bgsp->getContentSize().width/2*SPRITESCALE_1,bgsp->getContentSize().height/2*SPRITESCALE_1));
	circleScale = 1.0f;
	bgsp->setScale(0.001f);
	bgsp->setTag(kTag_SP_Circle);
	spriteArray->addObject(bgsp);
	addChild(bgsp);
	
	//显示防御塔文字信息根节点;
	
	

	
	//测试显示;
	if (CESHI)
	{
		CCSprite* Lbsp = CCSprite::create();
		Lbsp->setPosition(CCPointZero);
		Lbsp->setTag(kTag_LB);
		Lbsp->setScale(0.001f);
		spriteArray->addObject(Lbsp);
		addChild(Lbsp);
			//显示防御塔范围信息;
		CCString* circleRange = CCString::createWithFormat("circle:%d",0);
		CCLabelTTF* lbcr= CCLabelTTF::create(circleRange->getCString(),"fonts/Marker Felt.ttf",30);
		lbcr->setPosition(ccp(100,-30));
		lbcr->setColor(kColorLB);
		lbcr->setTag(kTag_LB_Circle);
		Lbsp->addChild(lbcr,10);
		//显示防御塔攻击信息;
		CCString* atklb = CCString::createWithFormat("atk:%d",0);
		CCLabelTTF* lbrw = CCLabelTTF::create(atklb->getCString(),"fonts/Marker Felt.ttf",30);
		lbrw->setPosition(ccp(100,30));	
		lbrw->setColor(kColorLB);
		lbrw->setTag(kTag_LB_ATK);
		Lbsp->addChild(lbrw,10);

		//显示防御塔DPS信息;
		CCString* dpslb = CCString::createWithFormat("DPS:%d",0);
		CCLabelTTF* lbd = CCLabelTTF::create(dpslb->getCString(),"fonts/Marker Felt.ttf",30);
		lbd->setPosition(ccp(100,0));	
		lbd->setColor(kColorLB);
		lbd->setTag(kTag_LB_DPS);
		Lbsp->addChild(lbd,10);
	}


	

	//创建升级按钮;
	do
	{
		//获取升级所需金钱;
		CCSprite* sp2 = CCSprite::createWithSpriteFrameName("update.png");
		CCPoint uppoint = ccp(0,ZC_RECTSIZE);
		sp2->setPosition(uppoint);

		sp2->setScale(0.0001f);
		this->addChild(sp2,1,kTag_SP_UP);
		spriteArray->addObject(sp2);

		//升级标价;
		CCString* font1 = CCString::createWithFormat("%d",0);
		uPrice = CCLabelTTF::create(font1->getCString(),"fonts/Marker Felt.ttf",17);
		uPrice->setAnchorPoint(CCPointZero);
		uPrice->setPosition(ccp(28,7));
		sp2->addChild(uPrice,1,kTag_LB_UP);
	}while(0);
	
	//创建回收按钮;
	do 
	{
		CCSprite* sp3 = CCSprite::createWithSpriteFrameName("update_delete.png");
		CCPoint sellpoint = ccp(0,-ZC_RECTSIZE);
		sp3->setPosition(sellpoint);
// 		if (axie.y<=0.0)
// 		{
// 			sp3->setPosition(ccp(bgsp->getContentSize().width/2*SPRITESCALE_1-60,sp3->getContentSize().height/3+60));
// 		}
		sp3->setScale(0.0001f);
		this->addChild(sp3,1,kTag_SP_CELL);

		spriteArray->addObject(sp3);

		//this->setPosition(ccp(axie.x-bgsp->getContentSize().width/2*SPRITESCALE_1+SPRITESIZE/2,axie.y-bgsp->getContentSize().height/2*SPRITESCALE_1+SPRITESIZE/2));
		m_game->addChild(this,VIEW_HEIGHT);

		//回收标价;
		CCString* font2 = CCString::createWithFormat("%d",0);
		sPrice = CCLabelTTF::create(font2->getCString(),"fonts/Marker Felt.ttf",17);
		sPrice->setAnchorPoint(CCPointZero);
		sPrice->setTag(kTag_LB_CELL);
		sPrice->setPosition(ccp(28,7));
		sp3->addChild(sPrice);
	} while (0);

	this->setVisible(false);


	return true;
}

void BatteryUpgrade::buAppearance()
{
	if (!tower)
	{
		return;
	}

	if (CESHI)
	{
		do 
		{
			CCLabelTTF* lb = (CCLabelTTF*)this->getChildByTag(kTag_LB)->getChildByTag(kTag_LB_ATK);
			CCString* font = CCString::createWithFormat("ATK:%d",tower->getATK());
			lb->setString(font->getCString());
		} while (0);

		do 
		{
			CCLabelTTF* lb = (CCLabelTTF*)this->getChildByTag(kTag_LB)->getChildByTag(kTag_LB_Circle);
			CCString* font = CCString::createWithFormat("Range:%d",tower->getShootRange());
			lb->setString(font->getCString());
		} while (0);

		do 
		{
			int atk = tower->getATK();
			float sped = tower->getShootSpeed()/60.0;
			int dps = atk/sped;

			CCLabelTTF* lb = (CCLabelTTF*)this->getChildByTag(kTag_LB)->getChildByTag(kTag_LB_DPS);
			CCString* font = CCString::createWithFormat("DPS:%d",dps);
			lb->setString(font->getCString());
		} while (0);

	}

	Levels = tower->getBuildLevel();
	if (Levels == 3)
	{
		getChildByTag(kTag_SP_UP)->setVisible(false);
	}
	else
	{
		getChildByTag(kTag_SP_UP)->setVisible(true);
		int uplevelPrice = tower->getUpLevelPrice();
		CCString* font1 = CCString::createWithFormat("%d",tower->getNextLevelPrice());
		uPrice->setString(font1->getCString());
	}

	//回收价格调整;
	int sellprice = tower->getSellPrice();
	CCString* font = CCString::createWithFormat("%d",sellprice);
	sPrice->setString(font->getCString());
	//sPrice 

	//攻击范围;

	circleScale = tower->getShootRange()/100.0f;

	if (spriteArray->count()>0)
	{
		CCSprite*sprite;
		for (int i =0;i<spriteArray->count();i++)
		{
			sprite = static_cast<CCSprite*>(spriteArray->objectAtIndex(i));
			CCScaleTo* st1;
			CCScaleTo* st2;

			if (sprite->getTag()==kTag_SP_Circle)
			{
				st1 = CCScaleTo::create(0.1f,circleScale*1.1);
				st2 = CCScaleTo::create(0.1f,circleScale);
			}
			else
			{
				st1 = CCScaleTo::create(0.1f,1.1f);
				st2 = CCScaleTo::create(0.1f,1.0f);
			}

			CCSequence* sq = CCSequence::createWithTwoActions(st1,st2);

			sprite->runAction(sq);
		}
	}
}

void BatteryUpgrade::buExeunt()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(
		this,
		"CurrectCoin");  

	float actime = 0.2f;

	if (spriteArray->count()>0)
	{
		CCSprite*sprite;
		for (int i =0;i<spriteArray->count();i++)
		{
			sprite = static_cast<CCSprite*>(spriteArray->objectAtIndex(i));
			CCScaleTo* st2 = CCScaleTo::create(actime,0.0001f);
	

			sprite->runAction(st2);
		}
	}

	this->runAction(CCFadeOut::create(actime));
}

void BatteryUpgrade::onEnter()
{
	CCLayer::onEnter();
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(BatteryUpgrade::checkCoinEnough),"CurrectCoin",NULL);
}

void BatteryUpgrade::onExit()
{
	CCLayer::onExit();
}

void BatteryUpgrade::checkCoinEnough( CCObject* obj )
{
	CCInteger* ccoin = (CCInteger*)obj;
	int coin = ccoin->getValue();

	CCSprite* sp2 = (CCSprite*)getChildByTag(2);

	if (!sp2)
	{
		return;
	}
	if(!tower)
	{
		return;
	}
	if (coin>=tower->getNextLevelPrice())
	{

		sp2->initWithSpriteFrameName("update.png");
	}
	else
	{
		sp2->initWithSpriteFrameName("noupdate.png");
	}
}

int BatteryUpgrade::touchEnd( float x,float y )
{
	do 
	{
		CCSprite* sp = (CCSprite*)(getChildByTag(kTag_SP_UP));
		CCPoint touch = ccp(x,y)-getPosition();
		if (sp->boundingBox().containsPoint(touch))
		{
			return 1;
		}
	} while (0);

	do 
	{
		CCSprite* sp = (CCSprite*)(getChildByTag(kTag_SP_CELL));
		CCPoint touch = ccp(x,y)-getPosition();
		if (sp->boundingBox().containsPoint(touch))
		{

			m_game->pay(-tower->getSellPrice());
			tower->sellSelf();
			tower = NULL;
			return 0;
		}
	} while (0);
	return -1;
}

void BatteryUpgrade::ShowUpgradeMenu( int cellid )
{
	this->setVisible(true);
	CCPoint pot = cells[cellid]->getMidPoint();
	this->setPosition(pot);

	CCPoint axie = pot;
	CCSprite* upsp = (CCSprite*)this->getChildByTag(kTag_SP_UP);
	if (axie.y>=VIEW_HEIGHT-120)
	{
		upsp->setPosition(ccp(ZC_RECTSIZE,0));
		if (axie.x>=VIEW_WIDTH-120)
		{
			upsp->setPosition(ccp(-ZC_RECTSIZE,0));
		}
	}

	tower = (Shooter *)cells[cellid]->m_object;

	buAppearance();
}

BatteryUpgrade::~BatteryUpgrade()
{

}
