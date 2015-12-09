#include "Atkable.h"
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define ATKABLE_BOOLDBAR 100
#define ATKABLE_BOOLDBAR_PER 101

float iceBuff[4] = {0,0.3,0.4,0.5};
float slowBuff[4] = {0,0.4,0.5,0.65};

CCArray *Atkable::AtkableArray = CCArray::create();

bool Atkable::init()
{

	//设置一个基础的标志方便测试;
	msp = CCSprite::create("FreezingBreath.jpg");
	msp->setAnchorPoint(ZC_ATKABLE_ANCHOR);
	msp->setPosition(ccp(0,0));
	addChild(msp,-1);

	 mMaxHP = 1000;
	 mCurHP = 1000;

	 setDEF(10);
	 setAPDEF(10);

	 mRewardMoney = 300;


	return true;
}

void Atkable::autoZorder( float )
{
	this->setZOrder(S_HEIGHT-this->getPositionY());
}

void Atkable::setAutoZoder( bool isForever )
{
	if (isForever)
	{
		schedule(schedule_selector(Atkable::autoZorder));
	}
	else
	{
		autoZorder(0);
	}
}

cocos2d::CCPoint Atkable::getMidPoint()
{
	//return getPosition()+msp->getPosition();
	CCSize tSize= msp->getContentSize();
	float conX = tSize.width;
	float conY = tSize.height;
	CCPoint apoint = ZC_ATKABLE_ANCHOR;
	return getPosition()+ccp(conX*(0.5-apoint.x),conY*(0.5-apoint.y));
}

cocos2d::CCRect Atkable::getBox()
{
	float spheight = msp->getContentSize().height*msp->getScaleY();
	float spWidth = msp->getContentSize().width*msp->getScaleX();
	return CCRectMake(getPositionX()-spWidth*ZC_ATKABLE_ANCHOR.x,getPositionY()-spheight*ZC_ATKABLE_ANCHOR.y,spWidth,spheight);
}


Atkable::Atkable(){

	//添加到队列;
	Atkable::AtkableArray->addObject(this);

	////////输出当前数组成员数量;
	//int arrycount = Atkable::AtkableArray->count();
	//ILog(arrycount);

	//设置初始状态;
	mState = AS_NORMAL;


	//速度控制;
	scheduler = new CCScheduler();  
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(scheduler, 0, false);  
	actionManager = new CCActionManager();  
	actionManager->autorelease();

	scheduler->scheduleUpdateForTarget(actionManager, 0, false);  
	setActionManager(actionManager);
}

Atkable::~Atkable()
{
	//CCLog("~Atkable");

	scheduler->unscheduleUpdateForTarget(actionManager);
	scheduler->release();
	//CC_SAFE_DELETE(scheduler);

	actionManager = NULL;
	scheduler  = NULL;

	if (buffArray.size()>0)
	{
		std::list<Buff*>::iterator rd;
		for (rd = buffArray.begin();rd!=buffArray.end();)
		{
			delete (*rd);
			buffArray.erase(rd++);
		}
	}
}

void Atkable::getHart( int power,int hartStyle,int hlevel )
{
	if (mState & AS_GOD)
	{
		return;
	}

	//得到本对象的防御属性;
	int mAPdef = getAPDEF();
	int mADdef = getDEF();
	
	CCAssert(hlevel!=0,"getHart hlevel == 0");


	//计算伤害;
	int fh = 0;
	 switch (hartStyle)
	 {
	 case KHARTSTYLE_AD:
		 fh = (int)(power/(1+(mADdef/(hlevel*30.0))));
		 break;
	 case KHARTSTYLE_AP:
		 fh = power/(1+(mAPdef/(hlevel*30.0)));
		 break;
	 case KHARTSTYLE_CHAOS:
		 {
			 int objMinDef = MIN(mAPdef,mADdef);//选择最低的护甲;
			  fh = power/(1+(objMinDef/(hlevel*30.0)));
		 }
		 break;
	 case KHARTSTYLE_SACRED:fh = power;		//神圣伤害,无视护甲;
		 break;
	 default:
		 FUNELog
		//默认为物理攻击;
		 fh = power/(1+(getDEF()/(hlevel*30.0)));
	 }



	 //扣除血量;
	 mCurHP -= fh;



	 //目前血条百分比;
	 float per = 100-(float)mCurHP/(float)mMaxHP*100.0f;

	 if (mCurHP<=0)
	 {
		 if (msp&&msp->getChildByTag(ATKABLE_BOOLDBAR))
		 {
			 msp->getChildByTag(ATKABLE_BOOLDBAR)->setVisible(false);
		 }
	 }

	 //加载血条;
	 if (!getChildByTag(ATKABLE_BOOLDBAR))
	 {
		 //加载底框;
		 CCSprite* bgp = CCSprite::createWithSpriteFrameName("lifeframe.png");//"lifeframe.png"	
		 bgp->setPosition(ccp(0,getSPContentSize().height+5));
		 bgp->setTag(ATKABLE_BOOLDBAR);
		 addChild(bgp,10);


		 //加载进度条;
		 CCSprite *progressSprite=CCSprite::createWithSpriteFrameName("lifevalues.png");  
		 progress1=CCProgressTimer::create(progressSprite);  
		 //设置样式;
		 progress1->setType(kCCProgressTimerTypeBar);  
		 progress1->setAnchorPoint(ccp(0,0));

		 //设置方向;
		 progress1->setMidpoint(ccp(1, 0));  
		 progress1->setBarChangeRate(ccp(1, 0));  

		 //设置开始进度;
		 progress1->setPercentage(per);
		 progress1->setTag(ATKABLE_BOOLDBAR_PER);

		 bgp->addChild(progress1, 1,100);  

	 }
	 else
	 {		
		progress1->setPercentage(per);
	 }	


	 //if (mCurHP<=0)
	 //{
		// Destroyed();
	 //}
}

void Atkable::Destroyed()
{
	this->stopAllActions();
	this->runAction(CCRemoveSelf::create());
	////从队列删除;
	Atkable::AtkableArray->removeObject(this);
}

cocos2d::CCSize Atkable::getSPContentSize()
{
	return msp->getContentSize();
}

void Atkable::SpeedControl()
{
	const float normalSpeed = 1.0f;
	float curSpeed = normalSpeed;

	float iceEffect=1.0f;
	float slowEffect = 1.0f;

	if (mState&AS_ICE)
	{
		std::list<Buff*>::iterator first = buffArray.begin(),last = buffArray.end();
		while(first!=last)
		{
			Buff* buf = (Buff*)(*first);		
			if (buf)
			{
				if (buf->buffID == AS_ICE)
				{
					iceEffect = 1.0-iceBuff[buf->b_level];
					break;
				}

			}

			first++;
		}
	}

	if (mState&AS_SLOW)
	{
		std::list<Buff*>::iterator first = buffArray.begin(),last = buffArray.end();
		while(first!=last)
		{
			Buff* buf = (Buff*)(*first);		
			if (buf)
			{
				if (buf->buffID == AS_SLOW)
				{
					slowEffect = 1.0-slowBuff[buf->b_level];
					break;
				}

			}

			first++;
		}
	}

	curSpeed = normalSpeed*min(slowEffect,iceEffect);

	if (mState&AS_DIZZINESS)
	{
		curSpeed = 0.0;
	}

	scheduler->setTimeScale(curSpeed);
}


void Atkable::getBuff( AT_state id,int times, int level )
{
	if (times>0)
	{

		if (mState&id )
		{
			Buff* checkBuf = new Buff(id,times,level);
			updateState(checkBuf);
			delete checkBuf;
		}
		else
		{
			mState |= id;
			Buff* buf = new Buff(id,times,level);
			buffArray.push_back(buf);
			SpeedControl();
		}
		
	}

}


void Atkable::updateState( Buff* tbuf )
{
	std::list<Buff*>::iterator first = buffArray.begin(),
		last = buffArray.end();

	while(first!=last)
	{
		Buff* buf = (Buff*)(*first);		
		if (buf)
		{
			if (buf->buffID == tbuf->buffID)
			{
				//找到同名buff;

				int curtimes = buf->times;
				int newtimes = tbuf->times;

				int curlevels = buf->b_level;
				int newlevels = tbuf->b_level;

				switch (buf->buffID)
				{
				case AS_ICE:

					//CCLog("ice again");
					buf->times= max(curlevels,newtimes);
					buf->b_level = max(curlevels,newlevels);

					break;
				case AS_SLOW:
					//CCLog("slow again");
					buf->times= max(curlevels,newtimes);
					buf->b_level = max(curlevels,newlevels);

					break;
				case AS_DIZZINESS:
					//CCLog("dizziness again");

					buf->times= max(curlevels,newtimes);
					buf->b_level = max(curlevels,newlevels);
					break;
				case AS_GOD:
					//CCLog("god again");

					buf->times= max(curlevels,newtimes);
					buf->b_level = max(curlevels,newlevels);
					break;
				default:
					FUNELog;
				}

				return;
			}
		}

		first++;
	}
	//delete tbuf;
}


void Atkable::getContinueHart( int chID , int power,int times )
{
	if (chID>0)
	{
		ContinueHart* chart = new ContinueHart(chID,power,times);
		cHartArray.push_back(chart);
	}	
}

void Atkable::draw()
{


	do  //处理buff状态;
	{
		std::list<Buff*>::iterator first = buffArray.begin(),
			last = buffArray.end();

		while(first!=last)
		{
			Buff* buf = (Buff*)(*first);		
			if (buf)
			{
				//ILog(buf->times);

				if (--buf->times <= 0)
				{		
					mState &=~buf->buffID;

					delete buf;
					buffArray.erase(first++);
					buf = NULL;

					SpeedControl();
				}
				else
				{
					first++;
				}

			}
		}
	} while (0);


	do //处理持续伤害;
	{
		std::list<ContinueHart*>::iterator first = cHartArray.begin(),
			last = cHartArray.end();
		while(first!=last)
		{
			ContinueHart* chart = (ContinueHart*)(*first);
			if (chart)
			{
				if (chart->mtimes>0)
				{
					if (chart->minterval--<=0)
					{
						chart->mtimes--;
						chart->minterval = 60;
						//伤害;
						getHart(chart->mpower,3,1);
					}
					first++;
				}
				else
				{
					//删除buff;
					delete chart;
					cHartArray.erase(first++);
					chart = NULL;
				}
			}
		}

	} while (0);

	//glLineWidth( 2.0f ); 
	//ccDrawColor4B(255,0,0,128);  
	//float spheight = msp->getContentSize().height*msp->getScaleY();
	//float spWidth = msp->getContentSize().width*msp->getScaleX();

	//float xin = -spWidth*ZC_ATKABLE_ANCHOR.x;
	//float yin = -spheight*ZC_ATKABLE_ANCHOR.y;


	//ccDrawRect(ccp(xin,yin),ccp(xin,yin)+ccp(spWidth,spWidth));

	//CHECK_GL_ERROR_DEBUG();  

}

