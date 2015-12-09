#include "Marker.h"


Marker* Marker::curMark = NULL;

Marker* Marker::create( Atkable* father )
{
	Marker* pRet = new Marker;
	if (pRet)
	{
		pRet->autorelease();
		pRet->init(father);

		//ɾ���ɵı��;
		if (curMark!=NULL)
		{
			curMark->removeFromParentAndCleanup(true);
			curMark = NULL;
		}
		//�����ǰ;
		curMark =pRet;

		return pRet;
	}
	delete pRet;
	pRet = NULL;
	return NULL;
}

bool Marker::init( Atkable* father )
{
	if (!CCNode::init())
	{
		return false;
	}
	
	//����;
	m_mark = CCSprite::createWithSpriteFrameName("at1.png");
	m_mark->setPosition(ccp(0,father->getSPContentSize().height+25));
	addChild(m_mark);

	//����;
	CCAnimation* moveAction = CCAnimationCache::sharedAnimationCache()->animationByName("addTarget");
	CCAnimate* move = CCAnimate::create(moveAction);
	m_mark->runAction(move);

	father->addChild(this,9999);
	
	return true;

}

Marker::~Marker()
{
	curMark = NULL;
}

Marker* Marker::getCurMark()
{
	return curMark;
}


