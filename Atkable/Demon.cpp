#include "Demon.h"
#include "GameState.h"
#include "ZGame.h"

#define INFO(a) inf->demonarray[i][a]
#define INFOWAVE(a) inf->demonForMap[i][a]

Demon::Demon()
{
	g_flipX = false;
	setDelegate(NULL);
	being_attacked = NULL;
}

Demon* Demon::create( DEMON_PARA )
{
	Demon* pRet = new Demon;
	if (pRet)
	{
		pRet->init(DEMON_PARA_INIT);
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

bool Demon::init( DEMON_PARA )
{

	ID = sort;
	setKingdom(OBJ_MONSTER);

	char str[256];
	sprintf(str,"gw%02d_a.png",ID);
	msp = CCSprite::createWithSpriteFrameName(str);
	msp->setAnchorPoint(ZC_ATKABLE_ANCHOR);
	addChild(msp);


	char tempName[256];
	sprintf(tempName,"gw%02dAction",ID);
	CCAnimation* moveAction = CCAnimationCache::sharedAnimationCache()->animationByName(tempName);
	CCAnimate *animate = CCAnimate::create(moveAction); 
	msp->runAction(animate); 
	setAutoZoder(true);

	SetCESHIData();
	//SetWaveData();

	return true;
}

void Demon::moveDemon()
{
	/*---------------------------------
	递归调用创建动作;
	---------------------------------*/
	this->stopAllActions();

	CCPoint now_point = mpath[p_index]/*pointArray->getControlPointAtIndex(p_index)*/;

	this->setPosition(now_point);

	//移动到终点;
	if (p_index==mpath.size()-1)
	{
		CCCallFunc* nextAttack = CCCallFunc::create(this,callfunc_selector(Demon::moveDemon));
		CCSequence* seq = CCSequence::create(CCJumpBy::create(1.0f,ccp(0,0),40,1),nextAttack,NULL);
		this->runAction(seq);
		if (myDelegate)
		{
			myDelegate->lifereduce(m_attack);
		}

		being_attacked->hartBloodpoor(1);
		
		return;
	}

	p_index++;
	CCPoint next_point = mpath[p_index]/*pointArray->getControlPointAtIndex(p_index)*/;

	float X1 = now_point.x;
	float Y1 = now_point.y;
	float X2 = next_point.x;
	float Y2 = next_point.y;


		//判断方向;
	g_flipX = false;
	if (X2<X1)
	{
		g_flipX = true;
	}
	if (X2>X1)
	{
		g_flipX = false;
	}
	msp->setFlipX(g_flipX);
	

	//xy为负数，说明遇到跳跃点;
	if (X2 <-1 || Y2 < -1)
	{
		X2 = -X2;
		Y2 = -Y2;
		//判断方向;
		if (X2<X1)
		{
			g_flipX = true;
		}
		if (X2>X1)
		{
			g_flipX = false;
		}
		msp->setFlipX(g_flipX);

		float pointdistance = sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2));
		//计算时间=距离/速度;
		float timeto = pointdistance/m_moveSpeed;

		CCMoveTo* mt = CCMoveTo::create(timeto,ccp(X2,Y2));

		CCCallFunc* jaCallback	= CCCallFunc::create(this,callfunc_selector(Demon::spaceJumpArrive));
		CCCallFunc* nextmove	= CCCallFunc::create(this,callfunc_selector(Demon::jumpDemon));
		CCCallFunc* jumpSpace	= CCCallFunc::create(this,callfunc_selector(Demon::spaceJump));
		CCSequence* jump	    = CCSequence::createWithTwoActions(jumpSpace,CCDelayTime::create(1.0f));

		CCScaleTo* scaleTo = CCScaleTo::create(1.0f,0.1f);

		CCSequence* sq = CCSequence::create(mt,jump,nextmove,NULL);

		if (getScale()!=1)
		{
			BodySubstitute(g_flipX,false);
			this->runAction(CCSequence::create(CCDelayTime::create(1.0),jaCallback,mt,jump,nextmove,NULL));
			setScale(1);
		}
		else
		{
			this->runAction(sq);
		}
		return;
	}

	//计算移动时间;
	float pointdistance = sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2));

	float timeto = pointdistance/m_moveSpeed;

	CCMoveTo* mt = CCMoveTo::create(timeto,next_point);
	CCCallFunc* nextmove = CCCallFunc::create(this,callfunc_selector(Demon::moveDemon));
	CCCallFunc* jaCallback = CCCallFunc::create(this,callfunc_selector(Demon::spaceJumpArrive));

	CCSequence* sq = CCSequence::create(mt,nextmove,NULL);

	


	if (getScale()!=1)
	{
		BodySubstitute(g_flipX,false);
		this->runAction(CCSequence::create(CCDelayTime::create(1.0),jaCallback,mt,nextmove,NULL));
		setScale(1);
	}
	else
	{
		this->runAction(sq);
	}

}

void Demon::BodySubstitute( bool filx,bool goback )
{
	char name[15];
	sprintf(name,"gw%02d_a.png",ID);
	CCSprite* roSp = CCSprite::createWithSpriteFrameName(name);
	roSp->setAnchorPoint(ZC_ATKABLE_ANCHOR);
	roSp->setFlipX(filx);
	roSp->setPosition(ccp(30,30));
	addChild(roSp);

	if (goback)
	{
		CCSequence* sq = CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(CCScaleTo::create(1.0f,0.01f),CCRotateBy::create(1.0f,480)),CCRemoveSelf::create());
		roSp->runAction(sq);
	}
	else
	{
		roSp->setScale(0.01f);
		CCSequence* sqro = CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(CCScaleTo::create(1.0f,1.0f),CCRotateBy::create(1.0f,-360)),CCRemoveSelf::create());
		roSp->runAction(sqro);
	}

}

void Demon::spaceJump()
{
	msp->setVisible(false);
	BodySubstitute(g_flipX,true);
}

void Demon::jumpDemon()
{
	setPosition(mpath[p_index]);
	setScale(0.9);
	moveDemon();
}

void Demon::spaceJumpArrive()
{
	msp->setVisible(true);
}


void Demon::setPath( array1(CCPoint) path )
{
	mpath = path;
	p_index = 0;
	moveDemon();
}

void Demon::InvadeMap( MapList* map )
{
	being_attacked = map;
	map->addChild(this);
	setPath(map->pvec);
}



void Demon::SetCESHIData()
{

	ReadInfo* inf = ReadInfo::getInstance();
	for (int i = 0;i<inf->demonarray.size();i++)
	{
		int readId = INFO(0);

		//寻找对应ID号;
		if (ID == readId)
		{
			setMaxHP(INFO(1));
			setCurHP(getMaxHP());
			setDEF(INFO(2));
			setAPDEF(INFO(3));	
			setMoveSpeed(INFO(4));
			setRewardMoney(14);
			int info_atk = INFO(5);

			//普通怪攻击默认为1;
			if (info_atk != 0)
			{
				setAttack(info_atk);
			}
			else
			{
				setAttack(1);
			}
		}
	}
}


void Demon::SetWaveData()
{
	ReadInfo* inf = ReadInfo::getInstance();

	int g_gamelevel = m_gamestate->curLevel;
	int g_wavelevel = m_game->curWave;

	for (int i = 0;i<inf->demonForMap.size();i++)
	{
		int readId = INFOWAVE(0);

		//寻找对应ID号;
		if (g_gamelevel == readId)
		{
			float protectWave = g_wavelevel;
			if (protectWave<=3)
			{
				protectWave = -(1-g_wavelevel*0.3);
			}
			else
			{
				protectWave = g_wavelevel-3;
			}

			int addhp = INFOWAVE(4);
			int adddep = INFOWAVE(5);
			int thp = INFOWAVE(1)+protectWave*addhp;
			int tdep = INFOWAVE(2)+protectWave*adddep;
			setMaxHP(thp);
			setCurHP(getMaxHP());
			setDEF(INFOWAVE(2)+protectWave*adddep);
			setAPDEF(tdep);	

			setMoveSpeed(120);
			setRewardMoney(14);
			int info_atk = 1;
			setAttack(1);
		}
	}
}