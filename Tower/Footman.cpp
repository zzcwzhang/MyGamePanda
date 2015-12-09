#include "Tower/Footman.h"
#include "GameState.h"
#include "ZGame.h"

//Footman* Footman::create( CCNode* father,CCPoint point,int ID )
//{
//	Footman* pRet = new Footman;
//	if (pRet)
//	{
//		pRet->init(father,point,ID);
//		pRet->autorelease();
//		return pRet;
//	}
//	else
//	{
//		delete pRet;
//		pRet = NULL;
//		return NULL;
//	}
//}

Footman* Footman::create( CCNode* father,int cellid,int ID )
{
	
	cells[cellid]->curObject = eShooter;
	
	Footman* pRet = new Footman;
	if (pRet)
	{
		pRet->init(father,cells[cellid]->getMidPoint(),ID);
		pRet->setCellID(cellid);
		pRet->autorelease();
		cells[cellid]->m_object = pRet;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Footman::init( CCNode* father,CCPoint point,int ID )
{
	m_father = father;
	setID(ID);
	towerSp = CCSprite::create();
	towerSp->setPosition(CCPointZero);
	addChild(towerSp,-1);


	ReadInfo* inf = ReadInfo::getInstance();
	for (int i = 0;i<inf->footmanarray.size()-1;i++)
	{
		//寻找对应ID号;
		if (ID == INFO(0))
		{
			setATK(INFO(1));
			setHartStyle(INFO(2));	
			setShootSpeed(INFO(3));
			setShootRange(INFO(4));
			setBuyPrice(INFO(5));
			setUpLevelPrice(INFO(6));
			setFullLevelPrice(INFO(7));
		}
	}
	
	//攻击等级是玩家属性;
	setUserLevel(1);
	setAtkLevel(1);
	setBuildLevel(1);

	autoCheckUpLevel();

	//自动转向开启;
	//autoRotate();

	//schedule(schedule_selector(Shooter::Radar));

	this->setPosition(point);
	m_location = point;
	this->setZOrder(S_HEIGHT-this->getPositionY());
	
	if (father)
	{
		father->addChild(this);
	}
	else
	{
		return false;
	}

	return true;
}


Footman::Footman()
{
	setKind(kS_KIND_FOOTMAN);
	m_cellID = -1;
	//setATK(0);
	//setHartStyle(0);	
	//setShootSpeed(120);
	//setShootRange(100);
	//setBuyPrice(100);
	//setUpLevelPrice(100);
	//setFullLevelPrice(100);
}

Footman::~Footman()
{
	cells[getCellID()]->curObject = eSpace;
}

void Footman::Fire( Atkable* aim )
{
	Bullet* but = Bullet::create(m_father,m_location);
	but->setAttackProperty(mID,mATK,mhartStyle,mBuildLevel);
	if (aim)
	{
		switch (mID)
		{
		case 0:		
			but->LockAttack(aim);
			break;
		case 1:
			but->setBulletBuff(AS_SLOW,120,mBuildLevel);
			but->LockAttack(aim);
			break;
		case 2:
			but->CollimationAttack(aim);
			break;
		case 3:
			but->LockAttack(aim);
			but->setBulletBuff(0,0,mBuildLevel-1);
			break;
		case 4:
			but->LockAttack(aim);
			break;
		case 5:
			but->LockAttack(aim);
			break;
		case 6:
			but->CircleAttack(mshootRange);
			but->setBulletBuff(AS_ICE,120,mBuildLevel);
			break;
		case 7:
			but->CircleAttack(mshootRange);
			break;
		case 8:
			if ((rand()%100)<(10+mBuildLevel*10))
			{
				but->setBulletBuff(AS_DIZZINESS,120,mBuildLevel);
			}
			but->LockAttack(aim);
			break;
		case 9:
			but->LockAttack(aim);
			but->setBulletContinueHart(ACH_POISON,mATK*0.25,3);
			break;
		case 10:
			{
				float ra = but->CollimationAttack(aim);
				but->setBulletContinueHart(ACH_FIRE,mATK*0.45,3);
				do 
				{
					Bullet* nbut = Bullet::create(m_father,m_location);
					nbut->setAttackProperty(mID,mATK,mhartStyle,mBuildLevel);
					nbut->DirectionAttack(ra+0.3);
					nbut->setBulletContinueHart(ACH_FIRE,mATK*0.45,3);
				} while (0);

				do 
				{
					Bullet* nbut = Bullet::create(m_father,m_location);
					nbut->setAttackProperty(mID,mATK,mhartStyle,mBuildLevel);
					nbut->DirectionAttack(ra-0.3);
					nbut->setBulletContinueHart(ACH_FIRE,mATK*0.45,3);
				} while (0);
			}
			break;
		case 11:
			but->LockAttack(aim);
			but->setBulletBuff(AS_ICE,120,mBuildLevel);
			break;
		case 12:
			but->CollimationAttack(aim);
			break;
		case 13:
			{	
				float apd = aim->getAPDEF();
				float fh = mATK/(1+((apd*0.35f)/(getUserLevel()*30.0)));
				but->setAttackProperty(mID,fh,3,mBuildLevel);
				but->LockAttack(aim);
			}

			break;
		default:
			but->LockAttack(aim);
			;
		}
		return;
	}



}

void Footman::setBuildLevel( int level )
{

	//mBuildLevel=level;
	char str[256];


	if (mID>9)
	{
		switch (level)
		{
		case 1:sprintf(str,"tower%d_a.png",mID-9);
			break;
		case 2:sprintf(str,"tower%d_b.png",mID-9);
			break;
		case 3:sprintf(str,"tower%d_c.png",mID-9);
			break;
		default:
			CCLog("the tower's level is > 3");
			return ;
		}
		towerSp->initWithSpriteFrameName(str);
		towerSp->setColor(ccc3(255,255,0));

	}
	else
	{
		switch (level)
		{
		case 1:sprintf(str,"tower%d_a.png",mID);
			break;
		case 2:sprintf(str,"tower%d_b.png",mID);
			break;
		case 3:sprintf(str,"tower%d_c.png",mID);
			break;
		default:
			CCLog("the tower's level is > 3");
			return ;
		}
		towerSp->initWithSpriteFrameName(str);
	}

	//重置属性;
	float rangeScale = 1.0f;
	float atkScale = 1.0f;
	float shootspeedScale = 1.0f;

	mBuildLevel;
	for (int i = level;i>mBuildLevel;i--)
	{
		rangeScale *=1.2f;
		atkScale *=1.2f;
		shootspeedScale *=0.6f;
	}
	setShootRange(getShootRange()*rangeScale);
	setATK(getATK()*atkScale);
	setShootSpeed(getShootSpeed()*shootspeedScale);


	mBuildLevel=level;


	//消除升级图标;
	if (atsp)
	{
		atsp->setVisible(false);
	}

	
}

int Footman::sellSelf()
{
	/*CCNotificationCenter::sharedNotificationCenter()->removeObserver(
		this,
		"CurrectCoin"); */
	cells[m_cellID]->m_object = NULL;
	cells[m_cellID]->curObject = eSpace;
	Shooter::shooterArray->removeObject(this);
	runAction(CCRemoveSelf::create());
	return getSellPrice();
}

int Footman::getNextLevelPrice()
{
	switch (mBuildLevel)
	{
	case 1:
		return mUpLevelPrice;
		break;
	case 2:
		return mFullLevelPrice;
		break;
	default:
		FUNELog;
		//ILog(mBuildLevel);
		return 0;
	}
}