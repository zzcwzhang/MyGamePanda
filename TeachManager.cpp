#include "TeachManager.h"
#include "SResManager.h"
#include "XAnimationID.h"
#include "GameState.h"

TeachingFream::TeachingFream()
{

}

TeachingFream::~TeachingFream()
{
	m_rectInfos.clear();
}

void TeachingFream::initClipRectInfos(const ClipRectInfo& rectInfo)
{

	CCLayerColor* leftLayer = CCLayerColor::create();
	leftLayer->setOpacity(150);
	CCSize size(ccp(0,0));
	size.width = rectInfo.clipPoint.x - rectInfo.clipSize.width/2;
	size.height = rectInfo.clipSize.height;
	CCPoint pt;
	pt.x = 0;
	pt.y = rectInfo.clipPoint.y - rectInfo.clipSize.height/2;
	leftLayer->setPosition(pt);
	leftLayer->setContentSize(size);

	CCLayerColor* topLayer = CCLayerColor::create();
	topLayer->setOpacity(150);
	size.width = getContentSize().width;
	size.height = getContentSize().height - rectInfo.clipPoint.y - rectInfo.clipSize.height/2;
	pt.x = 0;
	pt.y = rectInfo.clipPoint.y + rectInfo.clipSize.height/2;
	topLayer->setPosition(pt);
	topLayer->setContentSize(size);

	CCLayerColor* rightLayer = CCLayerColor::create();
	rightLayer->setOpacity(150);
	size.width = getContentSize().width - rectInfo.clipPoint.x - rectInfo.clipSize.width/2;
	size.height = rectInfo.clipSize.height;
	pt.x = rectInfo.clipPoint.x + rectInfo.clipSize.width/2;
	pt.y = rectInfo.clipPoint.y - rectInfo.clipSize.height/2;
	rightLayer->setPosition(pt);
	rightLayer->setContentSize(size);

	CCLayerColor* bottomLayer = CCLayerColor::create();
	bottomLayer->setOpacity(150);
	size.width = getContentSize().width;
	size.height = rectInfo.clipPoint.y - rectInfo.clipSize.height/2;
	pt.x = 0;
	pt.y = 0;
	bottomLayer->setPosition(pt);
	bottomLayer->setContentSize(size);

	this->addChild(leftLayer);
	this->addChild(rightLayer);
	this->addChild(topLayer); 
	this->addChild(bottomLayer);
}

TeachingFream* TeachingFream::create(const ClipRectInfo& rectInfo)
{
	TeachingFream* pRet = new TeachingFream();
	if (pRet && pRet->initWithColor(ccc4(0, 0, 0, 0), 800, 480))
	{
		//pRet->setColor(ccc3(0, 0, 0));
		//pRet->setOpacity()
		pRet->initClipRectInfos(rectInfo);
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

TeachManager::TeachManager(void)
{

}
TeachManager::~TeachManager(void)
{
}
