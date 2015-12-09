#include "Building.h"

#define BUILD_ICE 100
#define BUILD_FIRESTONE 101

USING_SG_GAME;

Building* Building::create(BUILDING_PARA)
{
	Building* pRet = new Building;
	if (pRet)
	{
		pRet->init(BUILDING_PARA_INIT);
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

bool Building::init(BUILDING_PARA)
{
	//static int buildcount = 0;
	//buildcount++;
	//ILog(buildcount);

	m_Cell =NULL;
	ID = sort;
	setKingdom(OBJ_OBSTACLE);
	////建筑没有防御力;
	setDEF(0);
	setAPDEF(0);


	if (ID == BUILD_ICE)
	{
		//sprintf(temp,"di%d.png",ID);
		msp = CCSprite::create();
		msp->setScale(1.25);
		msp->setAnchorPoint(ZC_ATKABLE_ANCHOR);
		//msp->setVisible(false);
		msp->setPosition(CCPointZero);
		addChild(msp);

		setDEF(20);
		setAPDEF(20);
	}
	else if (ID == BUILD_FIRESTONE)
	{
		//sprintf(temp,"di%d.png",ID);
		msp = CCSprite::create();
		msp->setScale(1.25);
		msp->setAnchorPoint(ZC_ATKABLE_ANCHOR);
		//msp->setVisible(false);
		msp->setPosition(CCPointZero);
		addChild(msp);

		setDEF(50);
		setAPDEF(50);
	}
	else
	{
		char temp[256];
		sprintf(temp,"build_%03d.png",ID);
		msp = CCSprite::createWithSpriteFrameName(temp);
		msp->setAnchorPoint(ZC_ATKABLE_ANCHOR);
		msp->setPosition(CCPointZero);
		addChild(msp);
	}
	
	setAutoZoder(true);

	ReadInfo* inf = ReadInfo::getInstance();
	for (int i = 0;i<inf->buildarray.size();i++)
	{
		//寻找对应ID号;
		if (ID == inf->buildarray[i][0])
		{
			////ILog(inf->buildarray[i][0]);
			int fullhp = inf->buildarray[i][1];
			setMaxHP(fullhp);
			setCurHP(getMaxHP());
			setRewardMoney(inf->buildarray[i][2]);
		}
	}


	
	//father->addChild(this);

	


	//CCSize tSize= msp->getContentSize();
	//float conX = tSize.width;
	//float conY = tSize.height;
	//CCPoint apoint = ZC_ATKABLE_ANCHOR;

	//CCSprite* sp = CCSprite::create("noadd.png");
	//sp->setPosition( ccp(conX*(0.5-apoint.x),conY*(0.5-apoint.y)));
	//addChild(sp);

	return true;
}

Building::~Building()
{
	//CCLog("~Building");
	if (m_Cell)
	{
		m_Cell->curObject = eSpace;
	}
}

void Building::sitDownCell()
{
	float x = getPositionX();
	float y = getPositionY();

	int cellNum =(int)(x/ZC_RECTSIZE+(y/ZC_RECTSIZE*9));
	cells[cellNum]->curObject = eBuild;
	m_Cell = cells[cellNum];
}

void Building::Destroyed()
{
	this->stopAllActions();
	this->runAction(CCRemoveSelf::create());
	////从队列删除;
	Atkable::AtkableArray->removeObject(this);

	
}




