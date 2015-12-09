#include "XFrame.h"
#include "XRect.h"
#include "XAnimation.h"
#include "GameState.h"
XFrame::XFrame(void)
{
	maxRunTime = 0;
	runnedCount = 0;
	playCount = 0;
	skinsorder.resize(0);
	opState = OP_STATE_NONE;
	hasTween = false;
}


XFrame::~XFrame(void)
{
	skinsorder.resize(0);
	for(int i=skins.size()-1;i>=0;i--)
	{
		skins[i]->removeAllChildren();
		skins[i]->removeFromParent();
		CC_SAFE_DELETE(skins[i]);
	}
	skins.resize(0);
}
void XFrame::setSkinCount(int count)
{
	for(int i=skins.size()-1;i>=0;i--)
	{
		if(skins[i])
		{
			skins[i]->removeFromParent();
			CC_SAFE_DELETE(skins[i]);
		}
	}
	skins.resize(count);
	for(int i=0;i<count;i++)
	{
		skins[i] = new XSkin();
		//skins[i]->retain();
	}
}

void XFrame::setTimeNodes(int skinIndex,int count,float data[],int colordata[])
{
	skins[skinIndex]->setTimeNodes(count,data,colordata);
	if(skins[skinIndex]->timenodes.size()>1)
	{
		hasTween = true;
	}
}
void XFrame::setParentId(int childSkinIndex,int parentSkinIndex)
{
	if(childSkinIndex>=0 && childSkinIndex<skins.size())
	{
		skins[childSkinIndex]->baseInfo[SKIN_INFO_PARENTID] = parentSkinIndex;
	}
}
void XFrame::reset()
{
	for(int i=0;i<skins.size();i++)
	{
		skins[i]->reset();
	}
}
void XFrame::resetOrder(int order[],int len)
{
	skinsorder.resize(0);
	skinsorder.resize(len);
	for(int i=0;i<len;i++)
	{
		skinsorder[i] = order[i];
	}
}
CCPoint XFrame::s_getLocation(int skinIndex)
{

	CCPoint p = ccp(-1,-1);
	if(skinIndex>=0 &&skinIndex<skins.size() )
	{
		p = skins[skinIndex]->s_getLocation();
		if(skins[skinIndex]->baseInfo[SKIN_INFO_PARENTID]>=0 && skins[skinIndex]->baseInfo[SKIN_INFO_PARENTID]<skins.size())
		{
			XSkin* skin = skins[skins[skinIndex]->baseInfo[SKIN_INFO_PARENTID]];
			CCPoint ps = skin->convertToWorldSpace(skin->s_getLocation());
			p.x += ps.x;
			p.y += ps.y;
		}
	}
	return p;
}
bool XFrame::updateFrame(CCNode*node,int time,bool showBone)
{
    int overSkinCount =0;//已经结束的皮肤
	bool hasTween = false;
	bool isOver = false;
	for(int k=0;k<skinsorder.size();k++)
	{
		int i = skinsorder[k];
		if(skins[i]->baseInfo[SKIN_INFO_PARENTID]>=0 && skins[i]->baseInfo[SKIN_INFO_PARENTID]<skins.size())
		{
			skins[i]->curColor[INFO_COLOR_R] = skins[skins[i]->baseInfo[SKIN_INFO_PARENTID]]->curColor[INFO_COLOR_R] ;
			skins[i]->curColor[INFO_COLOR_G] = skins[skins[i]->baseInfo[SKIN_INFO_PARENTID]]->curColor[INFO_COLOR_G] ;
			skins[i]->curColor[INFO_COLOR_B] = skins[skins[i]->baseInfo[SKIN_INFO_PARENTID]]->curColor[INFO_COLOR_B] ;
			skins[i]->setAdditionalTransform(skins[skins[i]->baseInfo[SKIN_INFO_PARENTID]]->nodeToParentTransform());
		}
		bool res = skins[i]->updateTimeNodeData(time);
		if(skins[i]->timenodes.size()>1)
		{
			hasTween = true;
		}
		if(res)
		{
			overSkinCount ++;
		}
	}
	isOver = overSkinCount >= skins.size();
	if(!hasTween && isOver)
	{
		runnedCount++;
		if(runnedCount>= playCount)
		{
			runnedCount = 0;
			isOver = true;
		}else
		{
			isOver= false;
		}
	}
	return isOver;
}
void XFrame::updateTimeNodeInfo( int skinIndex,int timeNodeIndex,float data[],int colordata[])
{
	if(skinIndex>=0 && skinIndex<skins.size())
	{
		skins[skinIndex]->updateTimeNodeInfo(timeNodeIndex,data,colordata);
	}
}
/************************************************************************/
/* 检测某个点是否在              aLocation 2*2区域内                                                       */
/************************************************************************/
bool XFrame::mouseInPoint(float px,float aLocation)
{
	return px>= aLocation-2 && px<= aLocation+2;
}
void XFrame::setTouchFlag(XSkin* skin)
{
}
/************************************************************************/
/* 鼠标没有按下移动      主要是设置鼠标形状                                                               */
/************************************************************************/
void XFrame::mouseMove(float x,float y)
{
	
}
/************************************************************************/
/* //鼠标点击              
    ctraPressed 是否按下ctrl键
/************************************************************************/
void XFrame::touchClick(float x,float y,bool ctraPressed)
{
	
}
bool XFrame::touchBegan(float x,float y,bool ctraPressed)
{
	
	return false;
}
/************************************************************************/
/* 触摸弹起                                                                     */
/************************************************************************/
void XFrame::touchEnded(float x,float y)
{
	
}

void XFrame::touchMoved(float x,float y)
{
	
}
float XFrame::getDegreeForTwoPoint(float px1, float py1, float px2, float py2)
{
	float x = px2-px1;
	float y = py2-py1;
	
	float hypotenuse = sqrt(x*x+y*y);
	if(hypotenuse ==0)return 0;
	//斜边长度
	float cos = x/hypotenuse;
	float radian =acos(cos);
	if(radian ==0)return 0;
	//求出弧度
	float angle = 180/(3.14/radian);
	//用弧度算出角度        
	if (y<0) {
		angle = -angle;
	} else if ((y == 0) && (x<0)) {
		angle = 180;
	}
	return angle;
}


void  XFrame::selSkinByRect(float x,float y,float w,float h)
{
	for(int i=skins.size()-1;i>=0;i--)
	{
		if(skins[i]->intersectsRect(x,y,w,h))
		{
			skins[i]->focus();
			selectedSkins.push_back(i);
		}
	}
}
void XFrame::setState(int state)
{
	opState = state;
}
/************************************************************************/
/*                  获得当前选中皮肤的索引                                                    */
/************************************************************************/
int XFrame::getCurSelSkinIndex()
{
	if(selectedSkins.size()==1)
	{
		return selectedSkins[0];
	}
	return -1;
}

void XFrame::setLocation_beforeBoned(int skindex,float x,float y)
{
}