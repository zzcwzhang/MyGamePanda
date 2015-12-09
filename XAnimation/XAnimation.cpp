#include "XAnimation.h"
#include "XFrame.h"
#include "XSkin.h"
#include "GameState.h"
CCDictionary* XAnimation::testure_animation;
XAnimation::XAnimation(void)
{
	roleNode = NULL;
	delayTime = 0;
	recycleStop = false;
	recycleCount = -1;
	recycleFP2FP = false;
	canPointOthers = true;
	fillAlpha = false;
	runOver = false;
	removedAtOver = false;
	showBone = true;
	touchPressed = false;
	infoIsChanging = false;
	asc.resize(ASC_LEN);
	//memset(asc,0,ASC_LEN);
	for(cbyte i=0;i<ASC_LEN;i++)
	{
		asc[i] = 0;
	}
	isRecyle = 0;
	this->retain();
	//setContentSize(CCSizeMake(m_aniInterface->SCREEN_WIDTH,m_aniInterface->SCREEN_HEIGHT));
}


XAnimation::~XAnimation(void)
{
	for(int i=frames.size()-1;i>=0;i--)
	{
		CC_SAFE_DELETE(frames[i]);
	}
	if(roleNode)
	{
		roleNode->removeFromParent();
		CC_SAFE_DELETE(roleNode);
		roleNode = NULL;
	}
}
void XAnimation::setBatchNode(char* pngFile)
{
	roleNode = CCSpriteBatchNode::create(pngFile);
	roleNode->retain();
	this->addChild(roleNode);
}
XAnimation* XAnimation::create(XAnimation* ani)
{
	XAnimation* ani_res = new XAnimation();
	ani_res->setFrameCount(ani->frames.size());
	ani_res->recycleFP2FP = ani->recycleFP2FP;

	ani_res->Recycle_end = ani->Recycle_end;
	ani_res->recycle_end_startFP = ani->recycle_end_startFP;
	ani_res->recycle_end_endFP = ani->recycle_end_endFP;
	ani_res->recycle_end_count = ani->recycle_end_count;
	ani_res->polygonShapes.resize(ani->polygonShapes.size());
	ani_res->shapeType.resize(ani->shapeType.size());
	ani_res->shapeRadius.resize(ani->shapeRadius.size());
	ani_res->shapeSize.resize(ani->shapeSize.size());
	ani_res->shapeType.assign(ani->shapeType.begin(),ani->shapeType.end());
	ani_res->shapeRadius.assign(ani->shapeRadius.begin(),ani->shapeRadius.end());
	for(int i=0;i<ani_res->shapeSize.size();i++)
	{
		ani_res->shapeSize[i].assign(ani->shapeSize[i].begin(),ani->shapeSize[i].end());
	}
	for(int i=0;i<ani_res->polygonShapes.size();i++)
	{
		ani_res->polygonShapes[i].resize(ani->polygonShapes[i].size());
		for(int j=0;j<ani_res->polygonShapes[i].size();j++)
		{
			ani_res->polygonShapes[i][j].assign(ani->polygonShapes[i][j].begin(),ani->polygonShapes[i][j].end());
		}
	}
	for(int i=0;i<ani->frames.size();i++)
	{
		ani_res->frames[i]->setPlayCount(ani->frames[i]->playCount);
		ani_res->frames[i]->skinsorder.resize(ani->frames[i]->skinsorder.size());
		for(int j=0;j<ani->frames[i]->skinsorder.size();j++)
		{
			ani_res->frames[i]->skinsorder[j] = ani->frames[i]->skinsorder[j];
		}
		//
		for(int j=0;j<ani->frames[i]->skins.size();j++)
		{
			XSkin* skin =XSkin::create(ani->frames[i]->skins[j]);
			ani_res->frames[i]->skins.push_back(skin);
			if(skin->timenodes.size()>1)
			{
				ani_res->frames[i]->hasTween = true;
			}
			if(ani->frames[i]->skins[j]->m_particle)
			{
				skin->m_particle = new XParticle();
				skin->m_particle->init(); 
				skin->m_particle->plisCount = ani->frames[i]->skins[j]->m_particle->plisCount;
				skin->m_particle->plsitPath = ani->frames[i]->skins[j]->m_particle->plsitPath;
				skin->m_particle->inteverX = ani->frames[i]->skins[j]->m_particle->inteverX;
				skin->m_particle->inteverY = ani->frames[i]->skins[j]->m_particle->inteverY;
				skin->m_particle->isRecycle = ani->frames[i]->skins[j]->m_particle->isRecycle;
			}
			int fpr = skin->timenodes[skin->timenodes.size()-1]->info[INFO_STARTFP];
			if(fpr>ani->frames[i]->maxRunTime)
			{
				ani_res->frames[i]->maxRunTime = fpr;
			}
		}
	}
	return ani_res;
}
void XAnimation::reset()
{
	runOver = false;
	for(int i=0;i<asc.size();i++)
	{
		asc[i] = 0;
	}
	if(frames.size()>asc[ACS_FRAME_INDEX])
	{
		frames[asc[ACS_FRAME_INDEX]]->updateFrame(this,asc[ACS_RUNTIME],false);
	}

	
}
CCSpriteFrame* XAnimation::getASpriteFrame(int imgid,int spriteid)
{
	char image[64];
	memset(image,0,sizeof(image));
	sprintf(image,"p_%d_%d.png",imgid,spriteid);
	CCSpriteFrameCache *frame = CCSpriteFrameCache::sharedSpriteFrameCache();
	return frame->spriteFrameByName(image);
}
void XAnimation::initBaseBySprite()
{
	CCSpriteFrame* tFrame = NULL;
	for(int i=0;i<frames.size();i++)
	{

		for(int j=0;j<frames[i]->skins.size();j++)
		{
			int imgid = (int)frames[i]->skins[j]->baseInfo[SKIN_INFO_TEXTUREID];
			int spriteid = (int)frames[i]->skins[j]->baseInfo[SKIN_INFO_SPRITEID];
			if(frames[i]->skins[j]->m_numbar)
			{
				char buf[64];
				memset(buf,0,sizeof(buf));
				sprintf(buf,"p_%d_%d.png",imgid,spriteid);
				CCSpriteFrameCache *framecache = CCSpriteFrameCache::sharedSpriteFrameCache();
				CCSpriteFrame*frame = framecache->spriteFrameByName(buf);
				CCSprite* tmp = new CCSprite();
				tmp->initWithSpriteFrame(frame);
				CCImage* img = Tools::getImgFromSprite(tmp,tmp->getContentSize().width,tmp->getContentSize().height);
				CCTexture2D * tex = new CCTexture2D();
				tex->autorelease();
				tex->initWithImage(img);
				frames[i]->skins[j]->initWithTexture(tex);
				CC_SAFE_DELETE(tmp);
				CC_SAFE_DELETE(img);
				
				//frames[i]->skins[j]->initWithFile(buf);
			}else
			{
				CCSpriteFrame* tFrame2 = getASpriteFrame(imgid,spriteid);
				if(tFrame2 && tFrame == NULL)
				{
					tFrame = tFrame2;
				}
				if(frames[i]->skins[j]->baseInfo[SKIN_INFO_ISBONE]>0)
				{
					frames[i]->skins[j]->initWithSpriteFrame(tFrame);
					frames[i]->skins[j]->setAnchorPoint(ccp(0,0.5f));
					frames[i]->skins[j]->setContentSize(CCSizeMake(0,0));

				}else
				{
					frames[i]->skins[j]->initWithSpriteFrame(tFrame2);
				}
			}
			
			
			if(frames[i]->skins[j]->m_button)
			{
				frames[i]->skins[j]->m_button->initRes();
			}
			if(frames[i]->skins[j]->m_scrollbar)
			{
				frames[i]->skins[j]->m_scrollbar->initRes(0,frames[i]->skins[j]->baseInfo[SKIN_INFO_RECT_H]/2,frames[i]->skins[j]->baseInfo[SKIN_INFO_RECT_W]);

			}
			int fpr = frames[i]->skins[j]->timenodes[frames[i]->skins[j]->timenodes.size()-1]->info[INFO_STARTFP];
			if(fpr>frames[i]->maxRunTime)
			{
				frames[i]->maxRunTime = fpr;
			}

		}
	}
	start();
}
void XAnimation::setRemoveAtOver()
{
	removedAtOver = true;
}
void XAnimation::start()
{
	recycleStop = false;
	recycleFP2FP = false;
	if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
	{
		childOrder = 0;
		XFrame* frame = frames[asc[ACS_FRAME_INDEX]];
		for(int k=0;k<frame->skinsorder.size();k++)
		{

			int i = frame->skinsorder[k];
			XSkin* skin = frame->skins[i];

			if(skin->baseInfo[SKIN_INFO_PARENTID]>=0 && skin->baseInfo[SKIN_INFO_PARENTID]<frame->skins.size())
			{
				skin->curColor[INFO_COLOR_R] = frame->skins[skin->baseInfo[SKIN_INFO_PARENTID]]->curColor[INFO_COLOR_R] ;
				skin->curColor[INFO_COLOR_G] = frame->skins[skin->baseInfo[SKIN_INFO_PARENTID]]->curColor[INFO_COLOR_G] ;
				skin->curColor[INFO_COLOR_B] = frame->skins[skin->baseInfo[SKIN_INFO_PARENTID]]->curColor[INFO_COLOR_B] ;
				skin->setAdditionalTransform(frame->skins[skin->baseInfo[SKIN_INFO_PARENTID]]->nodeToParentTransform());
			}
			skin->updateTimeNodeData(0);
		
		}
		for(int i=0;i<frame->skins.size();i++)
		{
			XSkin* skin = frame->skins[i];
			if(roleNode)
			{
				roleNode->addChild(skin,childOrder);
			}else
			{
				this->addChild(skin,childOrder);
			}	
			//CCLOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>R4");
			childOrder++;
			if(skin->m_button)
			{
				skin->m_button->added(skin,skin->baseInfo[SKIN_INFO_RECT_W]/2,skin->baseInfo[SKIN_INFO_RECT_H]/2);
				skin->m_button->initBGImg(skin,skin->baseInfo[SKIN_INFO_RECT_W],skin->baseInfo[SKIN_INFO_RECT_H]);
				childOrder+=5;
			}
			if(skin->m_scrollbar)
			{
				skin->m_scrollbar->added(skin,0,skin->baseInfo[SKIN_INFO_RECT_H]/2,skin->baseInfo[SKIN_INFO_RECT_W]);
				childOrder+=3;
			}
			if(skin->m_numbar)
			{
				skin->m_numbar->added(skin);
				childOrder+=1;
			}
			if(skin->m_textbox)
			{
				skin->baseInfo[SKIN_INFO_RECT_W] =skin-> m_textbox->w;
				skin->baseInfo[SKIN_INFO_RECT_H] = skin->m_textbox->h;
				skin->setContentSize(CCSizeMake(skin->baseInfo[SKIN_INFO_RECT_W],skin->baseInfo[SKIN_INFO_RECT_H]));

				skin->m_textbox->reset();
				skin->addChild(skin->m_textbox);
				skin->m_textbox->px = skin->baseInfo[SKIN_INFO_RECT_W]/2+skin->m_textbox->fontOffsetX;
				skin->m_textbox->py =skin->baseInfo[SKIN_INFO_RECT_H]+skin->m_textbox->fontOffsetY;
				float h = skin->m_textbox->getTextHeight();
				skin->m_textbox->setPosition(ccp(skin->m_textbox->px,skin->m_textbox->py-h/2));
				childOrder+=1;

			}
			if(skin->m_particle)
			{
				skin->m_particle->added(skin,0.5f,0.5f);//sprite 1*1
			}
		}
	}
}
void XAnimation::removeMySelf()
{
	for(int j=frames.size()-1;j>=0;j--)
	{
		for(int i=0;i<frames[j]->skins.size();i++)
		{
			frames[j]->skins[i]->removeAllRes();
		}
	}
	//removeFromParent();
	runOver = true;
	//CC_SAFE_DELETE(this);
}
void XAnimation::play()
{
	if(delayTime>0)
	{
		delayTime --;
		return;
	}
	if(recycleFP2FP)
	{
		if(recycleStop)
		{
			if(removedAtOver)
			{
				removeMySelf();
				return;
			}
			return;
		}
		bool isOver = false;
		if (recycle_end_startFP < recycle_end_endFP)
		{
			asc[ACS_RUNTIME] ++;
			if ( asc[ACS_RUNTIME]  > recycle_end_endFP)
			{
				isOver = true;
				asc[ACS_RUNTIME]  = recycle_end_startFP;
			}
		}
		else if (recycle_end_startFP > recycle_end_endFP)
		{
			asc[ACS_RUNTIME] --;
			if ( asc[ACS_RUNTIME]  < recycle_end_endFP)
			{
				isOver = true;
				asc[ACS_RUNTIME]  = recycle_end_startFP;
			}
		}
		 frames[asc[ACS_FRAME_INDEX]]->updateFrame(this,asc[ACS_RUNTIME],false);
		if (isOver && recycleCount != -1)
		{
			recycleCount--;
			if (recycleCount <= 0)
			{
				recycleStop = true;
			}
		}
	}else if(!recycleFP2FP)
	{
		if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
		{

			bool res = frames[asc[ACS_FRAME_INDEX]]->updateFrame(this,asc[ACS_RUNTIME],false);
			if(res)
			{

				if(frames.size()>1)
				{
					for(int i=0;i<frames[asc[ACS_FRAME_INDEX]]->skins.size();i++)
					{
						frames[asc[ACS_FRAME_INDEX]]->skins[i]->removeAllChildren();
					}

					this->removeAllChildren();
					frames[asc[ACS_FRAME_INDEX]]->reset();
					asc[ACS_RUNTIME] = 0;
					asc[ACS_FRAME_INDEX]++;
					if(asc[ACS_FRAME_INDEX]>= frames.size())
					{
						asc[ACS_FRAME_INDEX] = 0;
						if(removedAtOver)
						{
							removeMySelf();
							return;
						}
					}
					start();
				}else
				{
					if(frames.size()==1 && Recycle_end==1 && !recycleFP2FP)
					{
						recycleFP2FP = true;
					}else
					{
						if(removedAtOver)
						{
							removeMySelf();
							return;
						}
						if(isRecyle ==0)
						{
							asc[ACS_RUNTIME] = 0;
						}
					}


				}

			}else
			{
				asc[ACS_RUNTIME]++;
			}

		}
	}
	
	//if(asc[ACS_RUNTIME] == frames[asc[ACS_FRAME_INDEX]]->)
}
void XAnimation::setFrameCount(int count)
{
	infoIsChanging = true;
	for(int i=frames.size()-1;i>=0;i--)
	{
		CC_SAFE_DELETE(frames[i]);
	}
	frames.resize(count);
	for(int i=0;i<count;i++)
	{
		frames[i] = new XFrame();
	}
	infoIsChanging = false;
}
void XAnimation::addSkinToFrame(int frameIndex,float skinInfo[])
{
	XFrame* frame = frames[frameIndex];
	XSkin* skin = new XSkin();
	CCTexture2D* tex = m_gamestate->getATexture((int)skinInfo[SKIN_INFO_TEXTUREID]);
	if(tex)
	{
		skin->initWithTexture(tex,CCRect(skinInfo[SKIN_INFO_RECT_X],skinInfo[SKIN_INFO_RECT_Y],skinInfo[SKIN_INFO_RECT_W],skinInfo[SKIN_INFO_RECT_H]));
	}
	skin->retain();
	frame->skins.push_back(skin);
}
/************************************************************************/
/* 为某帧设置皮肤数量                                                                     */
/************************************************************************/
void XAnimation::setSkinCountForFrame(int frameIndex,int skinCount)
{
	XFrame* frame = frames[frameIndex];
	frame->setSkinCount(skinCount);
}
void XAnimation::setTimeNodes(int frameIndex,int skinIndex,int count,float data[],int colordata[])
{
	XFrame* frame = frames[frameIndex];
	frame->setTimeNodes(skinIndex,count,data,colordata);
}
void XAnimation::setFrameInfo(int data[],int len)
{
	infoIsChanging = true;
	if(frames.size() != len)
	{
		return;
	}
	for(int i=0;i<len;i++)
	{
		frames[i]->playCount = data[i];
	}
	infoIsChanging = false;
}

void XAnimation::resetShowCurFrame()
{
	playFrame(asc[ACS_FRAME_INDEX]);
}
void XAnimation::playFrame(int frameIndex)
{
	if(frameIndex<0 || frameIndex>=frames.size())return;
	asc[ACS_FRAME_INDEX] = frameIndex;
	asc[ACS_RUNTIME] = 0;
	this->removeAllChildren();
	XFrame* frame = frames[frameIndex];
	frame->runnedCount = 0;
	for(int i=0;i<frame->skins.size();i++)
	{
		if(!frame->skins[i]->isTextBox)
		{
			if(roleNode)
			{
				roleNode->addChild(frame->skins[i]);
			}else
			{
				this->addChild(frame->skins[i]);
			}
			
		}
	}
}
/************************************************************************/
/*                  获得当前选中皮肤的索引                                                    */
/************************************************************************/
int XAnimation::getCurSelSkinIndex()
{
	if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
	{
		return frames[asc[ACS_FRAME_INDEX]]->getCurSelSkinIndex();
	}
	
	return 0;
}
bool XAnimation::isActionOver()
{
	if(asc[ACS_FRAME_INDEX]== frames.size()-1)
	{
		XFrame* frame = frames[asc[ACS_FRAME_INDEX]];
		return asc[ACS_RUNTIME]  == frame->maxRunTime;
	}
	return  false;
}
bool XAnimation::updateAnimation(int timeIndex)
{
	  if(infoIsChanging)return false;
	   //循环帧到帧
	  if(recycleFP2FP)
	  {
		  if(recycleStop)
		  {
			  return true;
		  }
		  bool isOver = false;
		  if (recycle_end_startFP < recycle_end_endFP)
		  {
			   asc[ACS_RUNTIME] ++;
			  if ( asc[ACS_RUNTIME]  > recycle_end_endFP)
			  {
				  isOver = true;
				   asc[ACS_RUNTIME]  = recycle_end_startFP;
			  }
		  }
		  else if (recycle_end_startFP > recycle_end_endFP)
		  {
			   asc[ACS_RUNTIME] --;
			  if ( asc[ACS_RUNTIME]  < recycle_end_endFP)
			  {
				  isOver = true;
				   asc[ACS_RUNTIME]  = recycle_end_startFP;
			  }
		  }
		  if (isOver && recycleCount != -1)
		  {
			  recycleCount--;
			  if (recycleCount <= 0)
			  {
				  recycleStop = true;
			  }
		  }
		   return false;
	  }else if(!recycleFP2FP)
	  {
		  asc[ACS_RUNTIME] = timeIndex;
		  bool res = false;
		  if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
		  {
			  res = frames[asc[ACS_FRAME_INDEX]]->updateFrame(this,asc[ACS_RUNTIME],showBone);
		  }
		  if(res && frames.size() ==1 && Recycle_end==1 && !recycleFP2FP)
		  {
			  recycleFP2FP = true;
		  }
		    return res;
	  }

	  return false;
	
}
void XAnimation::updateTimeNodeInfo(int fpIndex, int skinIndex,int timeNodeIndex,float data[],int colordata[])
{
	 if(infoIsChanging)return;
	if(fpIndex>=0 && fpIndex<frames.size())
	{
		frames[fpIndex]->updateTimeNodeInfo(skinIndex,timeNodeIndex,data,colordata);
	}
}
/*void XAnimation::draw(void)
{
	CCNodeRGBA::draw();
	int ii =0;
}*/
void XAnimation::updateFrame(int frameIndex,int skinIndex,float skinInfo[])
{

}
/************************************************************************/
/* 绑定父节点                                                                     */
/************************************************************************/
void XAnimation::setParentId(int childSkinIndex,int parentSkinIndex)
{
	if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
	{
		frames[asc[ACS_FRAME_INDEX]]->setParentId(childSkinIndex,parentSkinIndex);
	}
}
void XAnimation::msetSkinRotation(int frameID,int skinID,float rvalue)
{
	if(frameID>=0 && frameID<frames.size())
	{
		XFrame* frame = frames[frameID];
		if(skinID>=0 && skinID<frame->skins.size())
		{
			frame->skins[skinID]->msetRotation(rvalue);
		}
	}
}
void XAnimation::mouseMove(float x,float y)
{
	if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
	{
		frames[asc[ACS_FRAME_INDEX]]->mouseMove(x,y);
	}
}
CCRect XAnimation::rect()
{
	return CCRectMake(-200,-200,400,400);
}
bool XAnimation::containTouchPoint(CCTouch* touch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}
bool XAnimation::ccTouchBegan(CCTouch *touch ,CCEvent *event)
{
	//bool res = frames[asc[ACS_FRAME_INDEX]]->ccTouchBegan(touch,event);
	return false;
}


void XAnimation::ccTouchMoved(CCTouch *touch ,CCEvent *event)
{
	//frames[asc[ACS_FRAME_INDEX]]->ccTouchMoved(touch,event);
}

void XAnimation::ccTouchEnded(CCTouch *touch ,CCEvent *event)
{
	//frames[asc[ACS_FRAME_INDEX]]->ccTouchEnded(touch,event);
} 

bool XAnimation::touchBegan(float x,float y,bool ctraPressed)
{
	if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
	{
		return frames[asc[ACS_FRAME_INDEX]]->touchBegan(x,y,ctraPressed);
	}
	return false;
}
void XAnimation::touchMoved(float x,float y)
{
	if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
	{
		frames[asc[ACS_FRAME_INDEX]]->touchMoved(x,y);
	}
	
}
void XAnimation::touchClick(float x,float y,bool ctraPressed)//鼠标点击 ctrl键是否按下
{
	if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
	{
		frames[asc[ACS_FRAME_INDEX]]->touchClick(x,y,ctraPressed);
	}
	
}
void XAnimation::touchEnded(float x,float y)
{
	if(asc[ACS_FRAME_INDEX]>=0 && asc[ACS_FRAME_INDEX]<frames.size())
	{
		frames[asc[ACS_FRAME_INDEX]]->touchEnded(x,y);
	}
	
}
/************************************************************************/
/* 根据鼠标区域选择皮肤                                                                 */
/************************************************************************/
void XAnimation::selSkinByRect(float x,float y,float w,float h)
{
	frames[asc[ACS_FRAME_INDEX]]->selSkinByRect(x,y,w,h);
}
void XAnimation::draw(void)
{
	if(fillAlpha)
	{
		ccDrawSolidRect(ccp(-m_gamestate->curScreenW/2,-m_gamestate->curScreenH/2),ccp(m_gamestate->curScreenW,m_gamestate->curScreenH),ccc4f(0,0,0,0.5f));
	}
	CCNodeRGBA::draw();
}