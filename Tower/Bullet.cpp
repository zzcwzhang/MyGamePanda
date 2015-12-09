#include "Tower/Bullet.h"

Bullet* Bullet::create( CCNode* father,CCPoint origin)
{
	Bullet* pRet = new Bullet;
	if (pRet)
	{
		
		pRet->init(father,origin);
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Bullet::init( CCNode* father,CCPoint origin )
{
	mfather = father;

	m_ID = 0;//决定图片;
	m_hart = 0;//决定伤害值;
	m_hartStyle = 0;//攻击类型;
	u_level = 0;//决定压制指数;
	//无任何buff;
	callbackBuff = 0;
	callbackBuffTimes = 0;
	m_bufflevel = 0;
	//无任何持续伤害;
	callbackchID = 0;
	callbackpower = 0;
	callbacktimes = 0;
	//旋转属性;
	flyVec2 = ccp(0,0); 

	//是否攻击一次;
	attackOnce = true;

	//旋转速度;
	rotationSpeed = 0;

	//创建子弹精灵;
	bsp = CCSprite::create();


	
	this->setPosition(origin);
	this->setZOrder(S_HEIGHT);
	//father->addChild(this);

	return true;
}

Bullet::~Bullet()
{
	//CCLog("~Bullet()");
	//if (bsp)
	//{
	//	bsp->removeFromParentAndCleanup(true);
	//	bsp = NULL;
	//}
}

void Bullet::hitCallBack()
{
	Atkable* aim = (Atkable*)getParent();

	//aim	->getHart(m_hart,m_hartStyle,u_level);
	//aim->getBuff(callbackBuff,callbackBuffTimes,m_bufflevel);
	//aim->getContinueHart(callbackchID,callbackpower,callbacktimes);


	//溅射范围攻击;
	if (m_ID == 3||m_ID == 5||m_ID == 11)
	{

		aim	->getHart(m_hart*0.2,m_hartStyle,u_level);
		aim->getBuff(callbackBuff,callbackBuffTimes,m_bufflevel);
		aim->getContinueHart(callbackchID,callbackpower,callbacktimes);

		CCPoint ppot = aim->getMidPoint();

		Bullet* but = Bullet::create(mfather,ppot);
		
		if (m_ID == 11)
		{
			but->setAttackProperty(6,m_hart*0.8,0,u_level);
			but->setBulletBuff(AS_ICE,120,m_bufflevel);
			but->CircleAttack(120+(m_bufflevel-1)*80);
		}
		else
		{
			but->setAttackProperty(7,m_hart*0.8,0,u_level);
			but->CircleAttack(120+(m_bufflevel)*80);
		}

	}
	else
	{
		aim	->getHart(m_hart,m_hartStyle,u_level);
		aim->getBuff(callbackBuff,callbackBuffTimes,m_bufflevel);
		aim->getContinueHart(callbackchID,callbackpower,callbacktimes);
	}

	if(m_ID == 8)
	{

	}
}

void Bullet::setBulletBuff( AT_state buffID,int bufftimes,int bufflevel )
{
	callbackBuff = buffID;
	callbackBuffTimes = bufftimes;
	m_bufflevel = bufflevel;
}

void Bullet::setBulletContinueHart( int chID , int power,int times )
{
	callbackchID = chID;
	callbackpower = power;
	callbacktimes = times;
}

void Bullet::setAttackProperty( int id,int hart, int hartstyle, int level )
{
	m_ID = id;//决定图片;
	m_hart = hart;//决定伤害值;
	m_hartStyle = hartstyle;//攻击类型;
	u_level = level;//决定压制指数;

	switch (m_ID)
	{
	case -1:
		break;
	case 2:bsp->initWithSpriteFrameName(BULLET_2_2);
		rotationSpeed = 8;
		break;
	case 3:bsp->initWithSpriteFrameName(BULLET_3_1);
		break;
	case 4:bsp->initWithSpriteFrameName(BULLET_4);
		break;
	case 5:bsp->initWithSpriteFrameName(BULLET_3_2);
		break;
	case 6:bsp->initWithSpriteFrameName(BULLET_6_0);
		break;
	case 7:bsp->initWithSpriteFrameName(BULLET_6_0);
		bsp->setColor(ccc3(200,0,0));
		break;
	case 8:bsp->initWithSpriteFrameName(BULLET_1_0);
		break;
	case 9:bsp->initWithSpriteFrameName(BULLET_1_0);
		break;
	case 10:bsp->initWithSpriteFrameName(BULLET_1_0);
		break;
	case 11:bsp->initWithSpriteFrameName(BULLET_3_3);
		break;
	case 12:bsp->initWithSpriteFrameName(BULLET_2_2);
		break;
	case 13:bsp->initWithSpriteFrameName(BULLET_0);
		break;

	default:
		bsp->initWithSpriteFrameName(BULLET_0);
	}



}

void Bullet::LockAttack( Atkable* aim )
{
	const float flySpeed = S_HEIGHT;//像素;
	CCPoint aimPoint = aim->getMidPoint();
	float dis = ccpDistance(getPosition(),aimPoint);
	float lifeTime = dis/flySpeed;//计算飞行时间;
	

	bsp->setPosition(getPosition());
	bsp->setRotation(countAngle(aimPoint)*180/PI);

	mfather->addChild(bsp,12800);

	//子弹精灵：移动后自毁;
	CCMoveTo*moveto = CCMoveTo::create(lifeTime,aimPoint);

	bsp->runAction(CCSequence::create(moveto,CCRemoveSelf::create(),NULL));


	//伤害计时器;
	/************************************************************************/
	/* 把自己添加到目标上，延迟一段时间后使目标受到伤害;			        */
	/************************************************************************/
	CCCallFunc* hitOver = CCCallFunc::create(this,callfunc_selector(Bullet::hitCallBack));
	this->runAction(CCSequence::create(CCDelayTime::create(lifeTime),hitOver,CCRemoveSelf::create(),NULL));


	aim->addChild(this);

	if (m_ID == 3||m_ID == 5||m_ID == 11)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("bullet3_bomb");
		CCAnimate* animate = CCAnimate::create(animation);
		bsp->stopAllActions();
		bsp->runAction(CCSequence::create(moveto,animate,CCRemoveSelf::create(),NULL));
	}
	return;
}

float Bullet::CollimationAttack( Atkable* aim )
{
	float aimRot = 0.0;
	CCPoint aimPoint = aim->getMidPoint();

	bsp->setRotation(countAngle(aimPoint)*180/PI);

	this->addChild(bsp);
	mfather->addChild(this);

	float ra = countAngle(aimPoint);
	float flyspeed = 8;
	flyVec2 = ccp(sin(ra)*flyspeed,cos(ra)*flyspeed);


	steplife = 150;
	scheduleUpdate();

	return ra;
}

void Bullet::DirectionAttack( float roa )
{
	this->addChild(bsp);
	mfather->addChild(this);

	bsp->setRotation(roa*180/PI);

	float ra = roa;
	float flyspeed = 8;
	flyVec2 = ccp(sin(ra)*flyspeed,cos(ra)*flyspeed);
	steplife = 150;
	scheduleUpdate();
}

void Bullet::CircleAttack( float radius )
{
	circle_radius = radius;
	float scale = (radius)/100.0f;
	//FLog(scale);


	CCPoint origin = getPosition();
	bsp->setScale(scale/2);
	bsp->setPosition(origin);
	mfather->addChild(bsp,1280);

	CCScaleTo *sto = CCScaleTo::create(0.4f,scale);
	CCFadeOut* fot = CCFadeOut::create(0.4f);
	CCCallFunc* ccal = CCCallFunc::create(this,callfunc_selector(Bullet::circleCallback));

	bsp->runAction(CCSequence::create(sto,ccal,fot,CCRemoveSelf::create(),NULL));

	mfather->addChild(this);
}

void Bullet::circleCallback()
{

	CCObject* obj;
	CCARRAY_FOREACH_REVERSE(Atkable::AtkableArray,obj)
	{
		Atkable* atk = (Atkable*)obj;
		if (checkAimInRange(atk,circle_radius))
		{
			atk	->getHart(m_hart,m_hartStyle,u_level);
			atk->getBuff(callbackBuff,callbackBuffTimes,m_bufflevel);
			atk->getContinueHart(callbackchID,callbackpower,callbacktimes);
		}
		

	}


	//FOREACH_ATKOBJ
	//CCPoint mypot = getPosition();
	//if (checkAimInRange(obj,circle_radius))
	//{
	//	obj	->getHart(m_hart,m_hartStyle,u_level);
	//	obj->getBuff(callbackBuff,callbackBuffTimes,m_bufflevel);
	//	obj->getContinueHart(callbackchID,callbackpower,callbacktimes);
	//}
	//FOREACH_END
}

void Bullet::update( float )
{

	//位移;

	setPosition(getPosition()+flyVec2);
	//旋转;
	if (rotationSpeed>0)
	{
		setRotation(getRotation()+rotationSpeed);
	}
	
	if (--steplife<=0)
	{
		atkedarray.clear();
		this->runAction(CCRemoveSelf::create());
	}
	//攻击;
	CCPoint mypot = getPosition();
	FOREACH_ATKOBJ
		CCPoint objpot = obj->getMidPoint();
		float dis = ccpDistance(objpot,mypot);

		if (dis<60)
		{
			if (obj)
			{
				bool isAttacked = false;
				for (int i = 0;i<atkedarray.size();i++)
				{
					Atkable* atked = (Atkable*)atkedarray[i];
					if (obj == atked)
					{
						isAttacked = true;
					}
				}

				if (!isAttacked)
				{
					obj->getHart(m_hart,m_hartStyle,u_level);
					obj->getBuff(callbackBuff,callbackBuffTimes,m_bufflevel);
					obj->getContinueHart(callbackchID,callbackpower,callbacktimes);
					atkedarray.push_back(obj);


					if (m_ID == 10)
					{
						steplife = 0 ;
					}
				}


			}
		}
	FOREACH_END
	
}

float Bullet::countAngle( CCPoint aimPoint )
{
	CCPoint my_loction = getPosition();
	float x = my_loction.x;
	float y = my_loction.y;
	float x1 = aimPoint.x;
	float y1 = aimPoint.y;

	float ra = atan2(x1-x,y1-y);

	return ra;
}

bool Bullet::checkAimInRange( Atkable* obj ,float mshootRange)
{
	CCPoint m_location = getPosition();
	CCPoint objpoint = obj->getMidPoint();
	float disToAim = ccpDistance(m_location,objpoint);

	//遍历所有范围内的可选目标;
	if (disToAim<mshootRange)
	{
		return true;
	}
	else
	{
		//获得4个边
		CCRect rect = obj->getBox();

		float minx = rect.getMinX();
		float miny = rect.getMinY();
		float maxx = rect.getMaxX();
		float maxy = rect.getMaxY();

		CCPoint lines[4];

		lines[0] = ccp(minx,miny);
		lines[1] = ccp(minx,maxy);
		lines[2] = ccp(maxx,maxy);
		lines[3] = ccp(maxx,miny);

		for (int i = 0;i<4;i++)
		{
			int j = i+1;
			if (i == 3)
			{
				j = 0;
			}

			////方法二;
			if (ccpSegmentIntersect(lines[i], lines[j] ,m_location, objpoint))
			{
				//交点; 
				CCPoint nodical = ccpIntersectPoint(lines[i], lines[j] ,m_location, objpoint);
				float disToAim = ccpDistance(m_location,nodical);
				disToAim = ccpDistance(m_location,nodical);
				//遍历所有范围内的可选目标;
				if (disToAim<mshootRange)
				{
					return true;
				}
			}
		}//4条线遍历完成;
		return false;
	}
}
