#include "Shooter.h"
#include "Tower/Marker.h"

CCArray* Shooter::shooterArray = CCArray::create();

Shooter::Shooter()
{
	setCellID(-1);
	m_father = NULL;
	isAutoRotate = false;
	sCDtime = 1000;
	mBuildLevel = 1;
	Shooter::shooterArray->addObject(this);
	extraAttack = 0;
	atsp = NULL;
}

Shooter* Shooter::create( CCNode* father,CCPoint point,int ID )
{
	Shooter* pRet = new Shooter;
	if (pRet)
	{
		pRet->init(father,point,ID);
		
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

bool Shooter::init( CCNode* father,CCPoint point,int ID )
{
	towerSp = CCSprite::createWithSpriteFrameName("tower7_c2.png");
	addChild(towerSp,-1);

	//���ó�ʼ������;
	setID(1);
	setATK(18);
	setHartStyle(0);
	setShootRange(180);
	setShootSpeed(30);
	setAtkLevel(1);

	autoRotate();

	this->setPosition(point);
	m_location = point;
	this->setZOrder(S_HEIGHT-this->getPositionY());
	father->addChild(this);

	return true;
}

void Shooter::draw()
{


	//glLineWidth(2);  
	//ccDrawColor4B(255, 0, 0, 255);  

	//float radius = getShootRange();
	//if (radius>=0)
	//{
	//	ccDrawCircle( ccp(0,0), radius, 0, 30, false);  
	//	CHECK_GL_ERROR_DEBUG(); 
	//}


}

void Shooter::Radar()
{
	//������Χȷ�ϣ�Ӧ����init��InfoReader��;
	//�״�һֱѰ��Ŀ�꣬���ܹ���������;
	Atkable* aimAt = NULL;

	//�Զ�ѡ��Ŀ��------------------;

	for (int i = Atkable::AtkableArray->count()-1 ;i>=0;i--) 
	{ 

	Atkable* obj = (Atkable*)Atkable::AtkableArray->objectAtIndex(i); 
	CCSize size = obj->getSPContentSize();
	//�������з�Χ�ڵĿ�ѡĿ��;

	if (checkAimInRange(obj))
	{
		if (obj->getKingdom() == OBJ_MONSTER)
		{
			aimAt = obj;
		}
	}

	FOREACH_END

	//ǿ��ѡ��Ŀ��----------------------;

	Marker* curMark = Marker::getCurMark();
	if (curMark!=NULL)
	{
		Atkable* objMark = (Atkable*)curMark->getParent();
		if (objMark)
		{

			if (checkAimInRange(objMark))
			{
				aimAt = objMark;
			}
		}	
	}




	//�Զ���ת----------------------;
	if (isAutoRotate&&aimAt)
	{
		towerSp->setRotation(getMyRotation(aimAt));	
	}

	//���������������--------------------;
	if (sCDtime++>=mshootSpeed)
	{
		if (aimAt)
		{
			Fire(aimAt);
			sCDtime = 0;
		}
	}
	
}

float Shooter::getMyRotation( Atkable* node )
{
	if(!node) return 0;
	CCPoint mpt = node->getMidPoint();

	CCPoint vec2 = ccpSub(mpt,m_location);
	float r1 = atan2(vec2.x,vec2.y); //���� ;
	float r2 = r1*180/3.14 ;//�Ƕ�;
	//��ֹ�Ž���ת;
	float r_now = towerSp->getRotation();
	if (r2<-90.0&&r_now>90.0)
	{
		r2+=360.0f;
	}
	if (r_now<-90.0&&r2>90.0)
	{
		r_now+=360.0f;
	}
	float r_sub = r2-r_now;

	float timeToRo = r_sub/(/*Level**/20.0f);//�����ٶ�;

	float precision = 0.5f;;

	return r_now+timeToRo;
}

float Shooter::getMyRotation( float aimRotation )
{
	float r2 = aimRotation;//�Ƕ�;
	//��ֹ�Ž���ת;
	float r_now = towerSp->getRotation();
	if (r2<-90.0&&r_now>90.0)
	{
		r2+=360.0f;
	}
	if (r_now<-90.0&&r2>90.0)
	{
		r_now+=360.0f;
	}
	float r_sub = r2-r_now;

	if (r_sub>0)
	{
		return r_now+1;
	}
	if (r_sub<0)
	{
		return r_now-1;
	}

	return r_now;
}

void Shooter::autoRotate()
{
	isAutoRotate = true;
}

cocos2d::CCRect Shooter::getBox()
{
	CCPoint mypt = towerSp->getPosition()-ccp(30,30)+this->getPosition();
	CCRect rect = CCRectMake(mypt.x,mypt.y,80,80);
	return rect;
}

bool Shooter::checkAimInRange( Atkable* obj )
{
	CCPoint objpoint = obj->getMidPoint();
	float disToAim = ccpDistance(m_location,objpoint);

	//�������з�Χ�ڵĿ�ѡĿ��;
	if (disToAim<mshootRange)
	{
		return true;
	}
	else
	{
		//���4����
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

			////����һ;
			//float s;
			//float t;
			//if(ccpLineIntersect(lines[i], lines[j] ,m_location, objpoint, &s, &t))
			//{
			//	//��ý���;
			//	CCPoint nodical =  m_location + ccpMult((objpoint - m_location),t);

			//	disToAim = ccpDistance(m_location,nodical);
			//	//�������з�Χ�ڵĿ�ѡĿ��;
			//	if (disToAim<mshootRange)
			//	{
			//		return true;
			//	}
			//}

			////������;
			if (ccpSegmentIntersect(lines[i], lines[j] ,m_location, objpoint))
			{
				//����; 
				CCPoint nodical = ccpIntersectPoint(lines[i], lines[j] ,m_location, objpoint);
				float disToAim = ccpDistance(m_location,nodical);
				disToAim = ccpDistance(m_location,nodical);
			//	CCLog("line %d  = %f",i,disToAim);
				//�������з�Χ�ڵĿ�ѡĿ��;
				if (disToAim<mshootRange)
				{
					//CCLog("jjj");
					return true;
				}
			}

		}//4���߱������;

		
	}
	return false;
}

bool Shooter::checkRectangleAndCircleCollision( CCPoint rectMidpoint,float rectHeight,float rectWidth,CCPoint circleMidpoint,float radius )
{
	float rx = rectMidpoint.x;
	float ry = rectMidpoint.y;

	float cx = circleMidpoint.x;
	float cy = circleMidpoint.y;

	float xdis = abs(rx - cx);
	//FLog(xdis);
	float ydis = abs(ry - cy);
	//FLog(ydis);

	float rph = radius + rectHeight/2.0;
	//FLog(rph);
	float rpw = radius + rectWidth/2.0;
	//FLog(rpw);
	if (rpw>=xdis&&rph>=ydis)
	{
		return true;
	}

	return false;
	


}

void Shooter::Fire( Atkable* aim )
{
	//����ʹ��;
	aim->getHart(mATK,mhartStyle,matkLevel);

	int buffLevel = 2; 
	int buffTime = 180;
	//ILog(buffTime);
	aim->getBuff(AS_ICE,buffTime,buffLevel);
}

void Shooter::checkLevelUpEnough( CCObject *obj )
{

	CCInteger* ccoin = (CCInteger*)obj;
	int coin = ccoin->getValue();
	if (mBuildLevel<3)
	{
		if (coin>=getNextLevelPrice())
		{
			atsp->setVisible(true);
		}
		else
		{
			atsp->setVisible(false);

		}
	}
}

void Shooter::autoCheckUpLevel()
{
	//��Ǯ��ʱ��������־;
	atsp = CCSprite::createWithSpriteFrameName("at3.png");
	atsp->setPosition(m_location+ccp(0,80));
	atsp->setVisible(false);
	addChild(atsp,100,33);
	CCAnimation* addAT = CCAnimationCache::sharedAnimationCache()->animationByName("addTarget2");
	CCAnimate* anite = CCAnimate::create(addAT);
	atsp->runAction(anite);

	//������Ǯ��������Ǯ�ܹ�����ʱ��ʾ������ʾ;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(Shooter::checkLevelUpEnough),"CurrectCoin",NULL);
}


Shooter::~Shooter()
{
	CCLog("~Shooter");
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(
		this,
		"CurrectCoin");
	int cid = getCellID();
	if (cid!=-1)
	{
		cells[cid]->curObject = eSpace;
		cells[cid]->m_object = NULL;
	}

}

void Shooter::ReadEquipment()
{
	//��ȡװ����ȼ��� ��ȡ�û���Ϣ���Ƿ�װ����ǿ���ȼ����еĻ���ȡװ���� ���ӹ�����;
	ReadInfo* inf = ReadInfo::getInstance();
	for (int i = 0;i<inf->equiparray.size();i++)
	{
		//Ѱ�Ҷ�ӦID��;
		if (mUserLevel == inf->equiparray[i][0])
		{
			//��ȡ1-4��װ��;
			for (int j = 1;j <5;j++)
			{
				//�����ñ�õ�װ����;
				int eNum = inf->equiparray[i][j];

				//����û���Ϣ���Ƿ�ӵ�и�װ����ǿ���ȼ�;
				int intensifyLevel = inf->UserEquiparray[mID][j-1];
				//ILog(intensifyLevel);
				//����Ƿ����˸�װ��;
				if (intensifyLevel>0)
				{
					//����װ����;
					for (int m = 0;m<inf->equipmentarray.size();m++)
					{
						if (eNum == inf->equipmentarray[m][0])
						{
							int edps = inf->equipmentarray[m][1];
							float msep = 60.0/mshootSpeed;
							int eat = edps/msep;
							extraAttack +=eat;
							//ILog(extraAttack);
						}
					}
				}
			}
		}
	}
}

void Shooter::EquipmentHarmony()
{
	//ILog(mID);
	float atkCoefficien = 1.0f;
	switch (mID)
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
	extraAttack *= atkCoefficien;
	//ILog(extraAttack);
}

int Shooter::getSellPrice()
{
	int returnCoin = mBuyPrice;
	if (mBuildLevel >=2)
	{
		returnCoin += mUpLevelPrice;
		if (mBuildLevel == 3)
		{
			returnCoin += mFullLevelPrice;
		}
	}

	//return returnCoin-20;
	return returnCoin*0.8;
}

void Shooter::ReadRune()
{
	//���ԣ����ȫ����������;
	ReadInfo* inf = ReadInfo::getInstance();
	if (!inf)
	{
		return;
	}
	array2(int) rune(inf->Runearray);
	array1(int) atkSum;
	for (int i = 0;i<rune.size();i++)
	{
		atkSum.push_back(rune[i][1]);
	}

	float Sum = 100.0;
	for (int i = 0;i<atkSum.size();i++)
	{
		Sum += (float)atkSum[i];
	}
	//CCLOG("Sum %f",Sum);

	int curAtk = getATK();

	setATK(curAtk*(Sum/100.0));

}

int Shooter::sellSelf()
{
	Shooter::shooterArray->removeObject(this);
	runAction(CCRemoveSelf::create());
	return getSellPrice();
}
