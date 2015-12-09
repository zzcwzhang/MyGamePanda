#include "GameState.h"
#include "XSkin.h"
#include "XRect.h"

XSkin::XSkin(void)
{
	rotation = 0;
	offsetX = 0;
	offsetY = 0;
	m_opcitiy = 0;
	m_isVisiable = true;
	doprogress = false;
	progressTimer = NULL;
	m_numbar = NULL;
	m_scrollbar = NULL;
	m_button = NULL;
	m_textbox = NULL;
	m_particle = NULL;
	m_checkbox = NULL;
	spriteForBone = NULL;

	focused = false;
	issetted = false;
	lvse = false;
	m_parentNode = -1;
	childRect = NULL;
	valueChanging = false;
	curTimeNode = 0;
	isTextBox = false;
	aniNodeForLink = NULL;
	baseInfo.resize(SKIN_INFO_LEN);
	for(int i=0;i<INFO_LEN;i++)
	{
		info_tween[i] = 0;
	}
	this->retain();
}


XSkin::~XSkin(void)
{
	if(progressTimer)
	{
		progressTimer->removeFromParent();
		progressTimer = NULL;
	}
	if(m_button)
	{
		m_button->destory();
		CC_SAFE_DELETE(m_button);
	}
	if(m_scrollbar)
	{
		m_scrollbar->destory();
		CC_SAFE_DELETE(m_scrollbar);
	}
	if(m_numbar)
	{
		m_numbar->destory();
		CC_SAFE_DELETE(m_numbar);
	}
	if(m_textbox)
	{
		m_textbox->destory();
		CC_SAFE_DELETE(m_textbox);
	}
	if(aniNodeForLink)
	{
		aniNodeForLink->removeFromParent();
		CC_SAFE_DELETE(aniNodeForLink);
	}
	if(m_particle)
	{
		m_particle->destory();
		CC_SAFE_DELETE(m_particle);
	}
	if(childRect)
	{
		childRect->removeFromParent();
		CC_SAFE_DELETE(childRect);
	}
	if(spriteForBone)
	{
		spriteForBone->removeFromParent();
	}
	if(m_checkbox)
	{
		CC_SAFE_DELETE(m_checkbox);
	}
	m_textbox = NULL;
	childRect = NULL;
	spriteForBone = NULL;
	aniNodeForLink = NULL;
	for(int i=timenodes.size()-1;i>=0;i--)
	{
		CC_SAFE_DELETE(timenodes[i]);
	}
	timenodes.resize(0);
}
XSkin* XSkin::create(XSkin* skin)
{
	XSkin* skin_res = new XSkin();
	skin_res->timenodes.resize(skin->timenodes.size());
	for(int i=0;i<skin->timenodes.size();i++)
	{
		skin_res->timenodes[i] = new XTimeNodeData();
		for(int j=0;j<INFO_LEN;j++)
		{
			skin_res->timenodes[i]->info[j] = skin->timenodes[i]->info[j];
		}
		for(int j=0;j<INFO_COLOR_LEN;j++)
		{
			skin_res->timenodes[i]->color[j] = skin->timenodes[i]->color[j];
		}
	}
	skin_res->baseInfo.resize(skin->baseInfo.size());
	for(int i=0;i<skin->baseInfo.size();i++)
	{
		skin_res->baseInfo[i] =  skin->baseInfo[i];
	}


	if(skin_res->baseInfo[SKIN_INFO_ISBONE]>0)
	{
		skin_res->baseInfo[SKIN_INFO_RECT_W] = 0;
		skin_res->baseInfo[SKIN_INFO_RECT_H] = 0;
		skin_res->setAnchorPoint(ccp(0,0.5f));
		skin_res->setContentSize(CCSizeMake(0,0));
	}else
	{
		/*CCTexture2D* tex = m_gamestate->getATexture(skin_res->baseInfo[SKIN_INFO_TEXTUREID]);
		if(tex)
		{
			skin_res->initWithTexture(tex,CCRect(skin_res->baseInfo[SKIN_INFO_RECT_X],skin_res->baseInfo[SKIN_INFO_RECT_Y],
				skin_res->baseInfo[SKIN_INFO_RECT_W],skin_res->baseInfo[SKIN_INFO_RECT_H]));
		}else
		{
			skin_res->isTextBox = true;
		}*/
	}
	return skin_res;
}
void XSkin::removeAllRes()
{
	if(m_button)
	{
		m_button->destory();
	}
	if(m_scrollbar)
	{
		m_scrollbar->destory();
	}
	if(m_numbar)
	{
		m_numbar->destory();
	}
	if(m_textbox)
	{
		m_textbox->destory();
	}
	if(m_particle)
	{
		m_particle->destory();
	}
}
/************************************************************************/
/* 设置父节点                                                                     */
/************************************************************************/
void XSkin::setParentNode(int nodeIndex)
{
	m_parentNode = nodeIndex;
}
/************************************************************************/
/* 设置所在动画节点                                                                   */
/************************************************************************/
void XSkin::setAniNode(CCNode* node)
{
	aniNodeForLink = node;
}
/************************************************************************/
/* 设置所有节点信息                                                                     */
/************************************************************************/
void XSkin::setTimeNodes(int count,float data[],int colordata[])
{
	valueChanging = true;
	if(timenodes.size()>0)
	{
		for(int i=timenodes.size()-1;i>=0;i--)
		{
			CC_SAFE_DELETE(timenodes[i]);
		}
	}
	timenodes.resize(count);
	for(int i=0;i<count;i++)
	{
		timenodes[i] = new XTimeNodeData();
		for(int j=0;j<INFO_LEN;j++)
		{
			timenodes[i]->info[j] = data[i*INFO_LEN+j];
		}
		for(int j=0;j<INFO_COLOR_LEN;j++)
		{
			timenodes[i]->color[j] = colordata[i*INFO_COLOR_LEN+j];
		}
	}
	valueChanging = false;
}
void XSkin::setBaseInfo()
{
	m_imgId = baseInfo[SKIN_INFO_TEXTUREID];
	m_spriteId = baseInfo[SKIN_INFO_SPRITEID];
}
/************************************************************************/
/* 更新关键帧信息                                                                     */
/************************************************************************/
void XSkin::updateTimeNodeInfo(int timeNodeIndex,float data[],int colordata[])
{
	if(timeNodeIndex>=0 && timeNodeIndex<timenodes.size())
	{
		for(int i=0;i<INFO_LEN;i++)
		{
			timenodes[timeNodeIndex]->info[i] =data[i];
		}
		for(int j=0;j<INFO_COLOR_LEN;j++)
		{
			timenodes[timeNodeIndex]->color[j] = colordata[j];
		}
	}
}
int XSkin::getTimeNode(int time)
{
	//有父节点默认修改第一个关键帧
	/*if(baseInfo[SKIN_INFO_PARENTID]>=0)
	{
		return 0;
	}*/
	int res = -1;
	for(int i=timenodes.size()-1;i>=0;i--)
	{
		if(time==timenodes[i]->info[INFO_STARTFP])
		{
			res = i;
			break;
		}
	}
	return res;

}
void XSkin::start()
{
}
void XSkin::m_setPosition(float x,float y)
{
	timenodes[0]->info[INFO_X] = x;
	timenodes[0]->info[INFO_X] = y;
}
void XSkin::s_setScale(float scalex,float scaley)
{
	for(int i=timenodes.size()-1;i>=0;i--)
	{
		timenodes[i]->info[INFO_SCALEX] = scalex;
		timenodes[i]->info[INFO_SCALEY] = scaley;
	}
}
/************************************************************************/
/* 改变皮肤纹理                                                              */
/************************************************************************/
void XSkin::changeTexture(char*path)
{
	initWithFile(path);
}
/************************************************************************/
/* 换装                                                                     */
/************************************************************************/
void XSkin::changeEquip(int equipIndex)
{
	if(equipIndex ==0)
	{
		baseInfo[SKIN_INFO_TEXTUREID] = m_imgId;
		baseInfo[SKIN_INFO_SPRITEID] = m_spriteId;
	}
	else
	{
		int cindex = equipIndex-1;
		if(cindex>=0 && cindex<equipinfo.size())
		{
			baseInfo[SKIN_INFO_TEXTUREID] = equipinfo[cindex][0];
			baseInfo[SKIN_INFO_SPRITEID] = equipinfo[cindex][1];
		}
	}
	if(baseInfo[SKIN_INFO_TEXTUREID] >=0 && baseInfo[SKIN_INFO_SPRITEID] >=0)
	{
		char image[64];
		memset(image,0,sizeof(image));
		sprintf(image,"p_%d_%d.png",(int)baseInfo[SKIN_INFO_TEXTUREID],(int)baseInfo[SKIN_INFO_SPRITEID]);
		initWithSpriteFrameName(image);
	}
}
/************************************************************************/
/* 移动                                                                     */
/************************************************************************/
void XSkin::doMove(float offx,float offy)
{
	offsetX += offx;
}
/************************************************************************/
/* 更新复选框信息                                                                     */
/************************************************************************/
void XSkin::updateCheckBox()
{
	if(m_checkbox == NULL)return;
	int preBGtexID = baseInfo[SKIN_INFO_TEXTUREID];
	int preSPtexID = baseInfo[SKIN_INFO_SPRITEID];
	if(!m_checkbox->bePressed && m_checkbox->isChecked && m_checkbox->btn_info[CHECKBOX_TYPE_CHECKED][COR_IMG_TEXID]>=0&&
		m_checkbox->btn_info[CHECKBOX_TYPE_CHECKED][COR_IMG_SPRITEID]>=0)
	{
		//选中
		baseInfo[SKIN_INFO_TEXTUREID] = m_checkbox->btn_info[CHECKBOX_TYPE_CHECKED][COR_IMG_TEXID];
		baseInfo[SKIN_INFO_SPRITEID] = m_checkbox->btn_info[CHECKBOX_TYPE_CHECKED][COR_IMG_SPRITEID];
		//颜色
		for(int i=0;i<INFO_COLOR_LEN;i++)
		{
			timenodes[0]->color[i] = m_checkbox->btn_info[CHECKBOX_TYPE_CHECKED][COR_IMG_COLOR_R+i];
		}
		//透明度
		timenodes[0]->info[INFO_ALPHA] = m_checkbox->btn_info[CHECKBOX_TYPE_CHECKED][COR_IMG_ALPHA];
		offsetX = m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_OFFSETX];
		offsetY = m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_OFFSETY];
	}
	else	if(!m_checkbox->bePressed && !m_checkbox->isChecked && m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_TEXID]>=0&&
		m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_SPRITEID]>=0)
	{
		//取消
		baseInfo[SKIN_INFO_TEXTUREID] = m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_TEXID];
		baseInfo[SKIN_INFO_SPRITEID] = m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_SPRITEID];
		//颜色
		for(int i=0;i<INFO_COLOR_LEN;i++)
		{
			timenodes[0]->color[i] = m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_COLOR_R+i];
		}
		//透明度
		timenodes[0]->info[INFO_ALPHA] = m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_ALPHA];
		offsetX = m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_OFFSETX];
		offsetY = m_checkbox->btn_info[CHECKBOX_TYPE_NOTCHECKED][COR_IMG_OFFSETY];
	}
	else if(m_checkbox->bePressed && m_checkbox->btn_info[CHECKBOX_TYPE_PRESSED][COR_IMG_TEXID]>=0&&
		m_checkbox->btn_info[CHECKBOX_TYPE_PRESSED][COR_IMG_SPRITEID]>=0)
	{
		//取消
		baseInfo[SKIN_INFO_TEXTUREID] = m_checkbox->btn_info[CHECKBOX_TYPE_PRESSED][COR_IMG_TEXID];
		baseInfo[SKIN_INFO_SPRITEID] = m_checkbox->btn_info[CHECKBOX_TYPE_PRESSED][COR_IMG_SPRITEID];
		//颜色
		for(int i=0;i<INFO_COLOR_LEN;i++)
		{
			timenodes[0]->color[i] = m_checkbox->btn_info[CHECKBOX_TYPE_PRESSED][COR_IMG_COLOR_R+i];
		}
		//透明度
		timenodes[0]->info[INFO_ALPHA] = m_checkbox->btn_info[CHECKBOX_TYPE_PRESSED][COR_IMG_ALPHA];
		offsetX = m_checkbox->btn_info[CHECKBOX_TYPE_PRESSED][COR_IMG_OFFSETX];
		offsetY = m_checkbox->btn_info[CHECKBOX_TYPE_PRESSED][COR_IMG_OFFSETY];
	}
	if(!this->getTexture() || preBGtexID!= baseInfo[SKIN_INFO_TEXTUREID] ||  preSPtexID!= baseInfo[SKIN_INFO_SPRITEID])
	{
		char image[64];
		memset(image,0,sizeof(image));
		sprintf(image,"p_%d_%d.png",(int)baseInfo[SKIN_INFO_TEXTUREID],(int)baseInfo[SKIN_INFO_SPRITEID]);
		initWithSpriteFrameName(image);
	}
}
void XSkin::bePressedForCheckBox(bool pressed)
{
	if(m_checkbox)
	{
		if(m_checkbox->bePressed  != pressed)
		{
			updateCheckBox();
		}
		m_checkbox->bePressed = pressed;
	}
}
void XSkin::changeCheckBoxState()
{

	if(m_checkbox)
	{
		m_checkbox->bePressed = false;
		m_checkbox->stateChaged();
		updateCheckBox();
	}
}
void XSkin::setCheckBoxState(bool state)
{
	if(m_checkbox)
	{
		m_checkbox->setState(state);
		updateCheckBox();
	}
}
/************************************************************************/
/* 更新补间（骨骼）信息                                                                     */
/************************************************************************/
bool XSkin::updateTimeNodeData(int time)
{
	/************************************************************************/
	/* ccBlendFunc c = {GL_ONE ,GL_SRC_COLOR |GL_ONE_MINUS_SRC_COLOR};
	batch->setBlendFunc(c);                                                                     */
	/************************************************************************/
	bool isOver = false;//本帧跑完
	if(valueChanging)return true;
	//CCPoint PA = getAnchorPoint();

	if(isTextBox)
	{

	}else
	{
			isOver = (timenodes.size()-1 == curTimeNode);
			for(int i=timenodes.size()-1;i>=0;i--)
			{
				if(time>=timenodes[i]->info[INFO_STARTFP])
				{
					curTimeNode = i;
					bool visiable =timenodes[curTimeNode]->info[INFO_VISIBLE] == 0;
					bool partic_visiable = timenodes[curTimeNode]->info[INFO_HASTHING] == 0;
					this->setVisible(visiable);
					if(m_particle)
					{
						if(!partic_visiable && !m_particle->hided)
						{
							//m_particle->destory();
							m_particle->stop();
							m_particle->hided = true;
						}else if(partic_visiable && m_particle->hided)
						{
							m_particle->added(this,baseInfo[SKIN_INFO_RECT_W]/2,baseInfo[SKIN_INFO_RECT_H]/2);
							m_particle->hided = false;
						}
					}
					break;
				}
			}
			if(timenodes.size()>curTimeNode+1)
			{
				float interval = time-timenodes[curTimeNode]->info[INFO_STARTFP];//帧距离
				float totalFPFor2Node = timenodes[curTimeNode+1]->info[INFO_STARTFP]- timenodes[curTimeNode]->info[INFO_STARTFP];//两个关键帧之间的帧数
				for(int i=0;i<INFO_LEN;i++)
				{
					info_tween[i] =  
						timenodes[curTimeNode]->info[i]+
						interval/totalFPFor2Node*(timenodes[curTimeNode+1]->info[i]-timenodes[curTimeNode]->info[i]);
				}
				if(timenodes[curTimeNode]->info[INFO_ACC]>0)
				{
					float accx = 0;//加速度
					float accy = 0;
					float interval = time-timenodes[curTimeNode]->info[INFO_STARTFP];//帧距离
					float t = timenodes[curTimeNode+1]->info[INFO_STARTFP]-timenodes[curTimeNode]->info[INFO_STARTFP];
					float sx = timenodes[curTimeNode+1]->info[INFO_X]-timenodes[curTimeNode]->info[INFO_X];
					float sy = timenodes[curTimeNode+1]->info[INFO_Y]-timenodes[curTimeNode]->info[INFO_Y];
					if(timenodes[curTimeNode]->info[INFO_ACC] ==1)
					{
						accx = sx*2/(t*t);//匀加速
						accy = sy*2/(t*t);//匀加速
						info_tween[INFO_X] = timenodes[curTimeNode]->info[INFO_X]+accx*(interval*interval)/2;
						info_tween[INFO_Y] = timenodes[curTimeNode]->info[INFO_Y]+accy*(interval*interval)/2;
					}
					else if(timenodes[curTimeNode]->info[INFO_ACC] ==2)
					{
						accx = -sx*2/(t*t);//匀减速
						accy = -sy*2/(t*t);//匀减速
						float vx0 = -accx*t;
						float vy0 = -accy*t;
						info_tween[INFO_X] = timenodes[curTimeNode]->info[INFO_X]+vx0*interval+accx*(interval*interval)/2;
						info_tween[INFO_Y] = timenodes[curTimeNode]->info[INFO_Y]+vy0*interval+accy*(interval*interval)/2;
					}
					//accx = sx*2/(t*t);//匀加速
					//accy = sy*2/(t*t);//匀加速
					//info_tween[INFO_X] = timenodes[curTimeNode]->info[INFO_X]+accx*(interval*interval)/2;
					//info_tween[INFO_Y] = timenodes[curTimeNode]->info[INFO_Y]+accy*(interval*interval)/2;
				}
				//颜色
				for(int i=0;i<INFO_COLOR_LEN;i++)
				{
					color_tween[i] = timenodes[curTimeNode]->color[i]+
						interval/totalFPFor2Node*(timenodes[curTimeNode+1]->color[i]-timenodes[curTimeNode]->color[i]);
				}
			}else
			{
				for(int i=0;i<INFO_LEN;i++)
				{
					info_tween[i] =timenodes[curTimeNode]->info[i];
				}
				//颜色
				for(int i=0;i<INFO_COLOR_LEN;i++)
				{
					color_tween[i] = timenodes[curTimeNode]->color[i];
				}
			}
		
		setScaleX( info_tween[INFO_SCALEX]);
		setScaleY( info_tween[INFO_SCALEY]);
		
		setPositionX(info_tween[INFO_X]+offsetX);
		setPositionY(info_tween[INFO_Y]);

		if(rotation != 0)
		{
			setRotation(rotation);
		}
		else
		{
			setRotationX(info_tween[INFO_ROTATION]+info_tween[INFO_ROTX]);
			setRotationY(info_tween[INFO_ROTATION]-info_tween[INFO_ROTY]);
		}
		setSkewX(info_tween[INFO_SKEWX]);
		setSkewY(info_tween[INFO_SKEWY]);
		//透明度
		float opacity = 255-info_tween[INFO_ALPHA]-m_opcitiy;
		if(opacity<0)opacity =0;
		if(opacity>255)opacity = 255;
		setOpacity(opacity);
		//颜色
		curColor[INFO_COLOR_R] = color_tween[INFO_COLOR_R];
		curColor[INFO_COLOR_G] = color_tween[INFO_COLOR_G];
		curColor[INFO_COLOR_B] = color_tween[INFO_COLOR_B];

		//滤色
		if(lvse)
		{
			ccBlendFunc c = {GL_ONE ,GL_SRC_COLOR |GL_ONE_MINUS_SRC_COLOR};
			setBlendFunc(c);
		}
		if(baseInfo[SKIN_INFO_ISBONE]==0)
		{
			if(baseInfo[SKIN_INFO_PARENTID]>=0)
			{
				setColor(ccc3(curColor[INFO_COLOR_R],curColor[INFO_COLOR_G],curColor[INFO_COLOR_B]));
			}else
			{
				setColor(ccc3(color_tween[INFO_COLOR_R],color_tween[INFO_COLOR_G],color_tween[INFO_COLOR_B]));
			}
			
		}else
		{
		   setOpacity(0);
		}
		if(!m_isVisiable)
		{
			setOpacity(0);
			return true;
		}
		if(m_button)
		{
			m_button->update(opacity);
			if(!m_button->showNorBg())
			{
				setOpacity(0);
			}
		}
		if(m_scrollbar)
		{
			m_scrollbar->update(opacity);
			if(!m_scrollbar->showNorBg())
			{
				setOpacity(0);
			}
		}
		if(m_numbar)
		{
			m_numbar->update(opacity);
			setOpacity(0);
		}
		if(doprogress)
		{
			
			if(progressTimer)
			{
				progressTimer->setColor(ccc3(color_tween[INFO_COLOR_R],color_tween[INFO_COLOR_G],color_tween[INFO_COLOR_B]));
				progressTimer->setOpacity(opacity);
				progressTimer->setAdditionalTransform(nodeToParentTransform());
			}
			setOpacity(0);
		}
		if(m_textbox)
		{
			m_textbox->setTextOpcity(opacity);
			setOpacity(0);
		}
	}

	//node->addChild(this);
	return isOver;
}
/************************************************************************/
/* 失去焦点                                                                     */
/************************************************************************/
void XSkin::loseFocus()
{
	if(childRect)
	{
		childRect->removeFromParent();
		CC_SAFE_DELETE(childRect);
	}
	focused = false;
}
/************************************************************************/
/* 获得锚点                                                                     */
/************************************************************************/
void XSkin::focus()
{
	focused = true;
	if(baseInfo[SKIN_INFO_ISBONE]==0 && !isTextBox)
	{
		if(childRect)
		{
			childRect->removeFromParent();
			CC_SAFE_DELETE(childRect);
		}
		XRect* rect = new XRect();
		rect->setSize(baseInfo[SKIN_INFO_RECT_W],baseInfo[SKIN_INFO_RECT_H]);
		addChild(rect);
		childRect = rect;
	}

}
void XSkin::onScorll(float x,float y)
{
	if(m_scrollbar && containTouchPoint(x,y))
	{
		CCPoint p = convertToNodeSpaceAR(ccp(x,y));
		float cx = p.x+m_scrollbar->processW/2;
		int sv = cx/m_scrollbar->processW*(m_scrollbar->maxValue-m_scrollbar->minValue);
		if(sv<m_scrollbar->minValue)sv = m_scrollbar->minValue;
		if(sv>m_scrollbar->maxValue)sv = m_scrollbar->maxValue;
		m_scrollbar->setValue(sv);
		m_scrollbar->updateBtnLocation(cx,baseInfo[SKIN_INFO_RECT_H]/2);
	}
}
void XSkin::setValue(int num)
{
	if(m_scrollbar)
	{
		if(num>m_scrollbar->maxValue)
		{
			num = m_scrollbar->maxValue;
		}
		float sv = baseInfo[SKIN_INFO_RECT_W]*num/(m_scrollbar->maxValue-m_scrollbar->minValue);
		m_scrollbar->setValue(num,sv,baseInfo[SKIN_INFO_RECT_H]/2);
	}
}
bool XSkin::containTouchPointOnScrollBtn( float x,float y)
{
	if(m_scrollbar)
	{
		CCPoint p = m_scrollbar->getLocation();
		CCPoint size =  m_scrollbar->getSize();
		CCRect rect;
		rect = CCRectMake(-baseInfo[SKIN_INFO_RECT_W]/2+p.x-size.x/2,-baseInfo[SKIN_INFO_RECT_H]/2+p.y-size.y/2,size.x,size.y);
		return rect.containsPoint(convertToNodeSpaceAR(ccp(x,y)));
	}
	return false;
	
}
bool XSkin::containTouchPoint(float x,float y)
{
	if(m_button != NULL && m_button->bgImg != NULL )
	{
		CCRect rect = CCRectMake(-baseInfo[SKIN_INFO_RECT_W]/2,-baseInfo[SKIN_INFO_RECT_H]/2,baseInfo[SKIN_INFO_RECT_W],baseInfo[SKIN_INFO_RECT_H]);
		CCPoint glPoint = CCDirector::sharedDirector()->convertToGL(ccp(x,y));  
		CCPoint pTouch = ccp(x,y);

		if ( rect.containsPoint(convertToNodeSpaceAR(ccp(x,y)))) {
			//return true;
			ccColor4B color4B = {0, 0, 0, 0};  
			CCPoint nodePos = convertToNodeSpaceAR(pTouch);  
			int imgW =  (int)m_button->bgImg->getWidth();
			int imgH =  (int)m_button->bgImg->getHeight();
			int x = (int)nodePos.x+imgW/2;  
			unsigned int y = getContentSize().height - (nodePos.y+imgH/2);  
			unsigned char* data_ = m_button->bgImg->getData();  
			unsigned int *pixel = (unsigned int *)data_;  
			int ccount =  (y * (int)m_button->bgImg->getWidth()) * 1 + x * 1;
			if(ccount<0 || ccount>=m_button->bgImg->getWidth()*m_button->bgImg->getHeight())return false;
			pixel = pixel +ccount;  
			if(!pixel)return false;
			//R通道  
			color4B.r = *pixel & 0xff;  
			//G通道  
			color4B.g = (*pixel >> 8) & 0xff;  
			//B通过  
			color4B.b = (*pixel >> 16) & 0xff;  
			//Alpha通道，我们有用的就是Alpha  
			color4B.a = (*pixel >> 24) & 0xff;  
			//CCLOG("当前点击的点的: alpha = %d", color4B.a);  
			bool isTouched = false;
			if (color4B.a > 0) {  
				isTouched = true;  
			} else {  
				isTouched = false;  
			}  
		return isTouched;
		/*CCRect rect = CCRectMake(-baseInfo[SKIN_INFO_RECT_W]/2,-baseInfo[SKIN_INFO_RECT_H]/2,baseInfo[SKIN_INFO_RECT_W],baseInfo[SKIN_INFO_RECT_H]);
		CCPoint glPoint = CCDirector::sharedDirector()->convertToGL(ccp(x,y));  
		CCPoint pTouch = ccp(x,y);

		if ( rect.containsPoint(convertToNodeSpaceAR(ccp(x,y)))) {  

			ccColor4B color4B = {0, 0, 0, 0};  

			CCPoint nodePos = convertToNodeSpaceAR(pTouch);  
			unsigned int x = nodePos.x;  
			unsigned int y = getContentSize().height - nodePos.y;  

			CCPoint point = getPosition();  
			开始准备绘制  
			CCRenderTexture* m_pRenderTexture = CCRenderTexture::create(getContentSize().width,getContentSize().height, kCCTexture2DPixelFormat_RGBA8888);  
			m_pRenderTexture->ignoreAnchorPointForPosition(true);  
			m_pRenderTexture->setPosition(ccp(400, 200));  
			m_pRenderTexture->setAnchorPoint(CCPointZero); 

			m_pRenderTexture->begin();  
			绘制使用的临时精灵，与原图是同一图片  
			CCSprite* pTempSpr = CCSprite::createWithSpriteFrame(displayFrame());  
			pTempSpr->setPosition(ccp(pTempSpr->getContentSize().width / 2, pTempSpr->getContentSize().height / 2));  
			绘制  
			pTempSpr->visit();  
			结束绘制  
			m_pRenderTexture->end();  
			通过画布拿到这张画布上每个像素点的信息，封装到CCImage中  
			CCImage* pImage =m_pRenderTexture->newCCImage();  
			获取像素数据  
			unsigned char* data_ = pImage->getData();  
			unsigned int *pixel = (unsigned int *)data_;  
			pixel = pixel + (y * (int)pTempSpr->getContentSize().width) * 1 + x * 1;  
			if(!pixel)return false;
			R通道  
			color4B.r = *pixel & 0xff;  
			G通道  
			color4B.g = (*pixel >> 8) & 0xff;  
			B通过  
			color4B.b = (*pixel >> 16) & 0xff;  
			Alpha通道，我们有用的就是Alpha  
			color4B.a = (*pixel >> 24) & 0xff;  
			CCLOG("当前点击的点的: alpha = %d", color4B.a);  
			bool isTouched = false;
			if (color4B.a > 0) {  
				isTouched = true;  
			} else {  
				isTouched = false;  
			}  

			绘制完成后清理画布的内容  
			m_pRenderTexture->clear(0, 0, 0, 0);  
			return isTouched;*/
		}  
	}else
	{
		CCRect rect;
		//是滚动条
		if(m_scrollbar != NULL)
		{
			rect = CCRectMake(-baseInfo[SKIN_INFO_RECT_W]/2,-baseInfo[SKIN_INFO_RECT_H]/2-m_scrollbar->point_Height/2,baseInfo[SKIN_INFO_RECT_W],baseInfo[SKIN_INFO_RECT_H]+m_scrollbar->point_Height);
		}else
		{
			rect = CCRectMake(-baseInfo[SKIN_INFO_RECT_W]/2,-baseInfo[SKIN_INFO_RECT_H]/2,baseInfo[SKIN_INFO_RECT_W],baseInfo[SKIN_INFO_RECT_H]);
		}
		//int8_t data[4];  
		//glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

		return rect.containsPoint(convertToNodeSpaceAR(ccp(x,y)));
	}

	return NULL;
}
CCPoint XSkin::s_getLocation()
{
	//CCPoint p = getPosition();
	//return getParent()->convertToNodeSpaceAR(ccp(p.x,p.y));
	//return convertToNodeSpaceAR(p);
	return ccp(info_tween[INFO_X]+offsetX,info_tween[INFO_Y]+offsetY);
}
bool XSkin::intersectsRect(float x,float y,float w,float h)
{
	CCRect rect;
rect = CCRectMake(-baseInfo[SKIN_INFO_RECT_W]/2,-baseInfo[SKIN_INFO_RECT_H]/2,baseInfo[SKIN_INFO_RECT_W],baseInfo[SKIN_INFO_RECT_H]);
		CCPoint p_me = convertToNodeSpaceAR(ccp(x,y));
		CCPoint p_size = convertToNodeSpaceAR(ccp(w,h));
		return rect.intersectsRect(CCRect(p_me.x,p_me.y,w,h));
}
void XSkin::m_setVisiable(bool visiable)
{
	m_isVisiable = visiable;
	if(m_numbar)
	{
		m_numbar->m_setVisiable(visiable);
	}
}
/************************************************************************/
/* 开始进度条
 type kCCProgressTimerTypeRadial 中心点旋转  kCCProgressTimerTypeBar进度条
 duration 时间
 fFromPercentage 开始值%
 fToPercentage 结束值
 ReverseProgress 方向 true 反向
 selector 回调函数
/************************************************************************/
void XSkin::stopProgress()
{
	doprogress = false;
	if(progressTimer)
	{
		progressTimer->stopAllActions();
		progressTimer->removeFromParent();
		progressTimer = NULL;
	}
}
void XSkin::startProgressTimer(CCProgressTimerType type,float duration, float fFromPercentage, float fToPercentage,bool ReverseProgress,SEL_CallFuncN selector)
{
	if(progressTimer)
	{
		progressTimer->removeFromParent();
		progressTimer= NULL;
	}
	int imgid = (int)baseInfo[SKIN_INFO_TEXTUREID];
	int spriteid = (int)baseInfo[SKIN_INFO_SPRITEID];
	char image[64];
	memset(image,0,sizeof(image));
	sprintf(image,"p_%d_%d.png",imgid,spriteid);
	doprogress = true;
	CCSprite* sp = CCSprite::createWithSpriteFrameName(image);
	progressTimer = CCProgressTimer::create(sp);
	CCActionInterval*action_progress_from_to = CCProgressFromTo::create(duration, fFromPercentage, fToPercentage); 
	CCCallFunc* action_callback = CCCallFuncN::create(this, selector);
	progressTimer->setType( type );
	progressTimer->setReverseProgress(ReverseProgress);
	progressTimer->runAction(CCSequence::create(action_progress_from_to, action_callback, NULL));
	progressTimer->setPosition(ccp(baseInfo[SKIN_INFO_RECT_W]/2,baseInfo[SKIN_INFO_RECT_H]/2));
	this->getParent()->addChild(progressTimer,getZOrder());
}
void XSkin::visit()
{
	CCNode::visit();
	/*if(m_textbox && m_textbox->autoClip)
	{
		glEnable(GL_SCISSOR_TEST);
		CCPoint p= getPosition();
		CCNode *parent = getParent();
		while(parent)
		{
			p = parent->convertToWorldSpaceAR(p);
			parent = parent->getParent();
		}
		glScissor(p.x-baseInfo[SKIN_INFO_RECT_W]/2-3,p.y-baseInfo[SKIN_INFO_RECT_H]/2-3,baseInfo[SKIN_INFO_RECT_W]+6,baseInfo[SKIN_INFO_RECT_H]+6);//x, y, w, h   
		//glScissor(0,0,500,2000);
		CCNode::visit();//调用自己的类方法
		glDisable(GL_SCISSOR_TEST);
	}else
	{
		CCNode::visit();
	}*/
}