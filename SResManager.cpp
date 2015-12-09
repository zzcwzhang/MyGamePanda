#include "GameState.h"
#include "SimpleAudioEngine.h"  
#include "SResManager.h"
#include "XFrameID.h"

#define USEOPIMG false//是否使用处理过的图片
using namespace CocosDenshion;  

SResManager::SResManager(void)
{
	allowAcceptPoint = true;
}
SResManager::~SResManager(void)
{
	for(int i=ui_added.size()-1;i>=0;i--)
	{
		ui_added[i]->removeFromParent();
	}
	//
	for(int i=ui_animations.size()-1;i>=0;i--)
	{
		ui_animations[i]->removeFromParent();
		CC_SAFE_DELETE(ui_animations[i]);
	}
	for(int i=animations.size()-1;i>=0;i--)
	{
		if(animations[i])
		{
			animations[i]->removeFromParent();
			CC_SAFE_DELETE(animations[i]);
		}
	}
	animations.resize(0);
	for(int i=gameui.size()-1;i>=0;i--)
	{
		if(gameui[i])
		{
			gameui[i]->removeFromParent();
			CC_SAFE_DELETE(gameui[i]);
		}
	}
	gameui.resize(0);
	ui_added.resize(0);
	if(XAnimation::testure_animation)
	{
		XAnimation::testure_animation->removeAllObjects();
		CC_SAFE_DELETE(XAnimation::testure_animation);
		XAnimation::testure_animation = NULL;
	}
	if(uistrings)
	{
		CC_SAFE_DELETE(uistrings);
	}
}
void SResManager::loadResConfig()
{
	XAnimation::testure_animation = new CCDictionary();
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(CONFIGFILE);
	DataInputStream* dis = DataInputStream::openFile(fullPath.c_str(),"rb");
	aniCount = dis->readInt();
	uicouunt = dis->readInt();
	textureCount = dis->readInt();
	animations.resize(aniCount);	
	gameui.resize(uicouunt);
	DataInputStream::closeFile(dis);
	//加载string
	uistrings = CCDictionary::createWithContentsOfFile("uiStrings.xml");
	uistrings->retain();
}
/************************************************************************/
/* 替换字符串
str原字符串
needReplaceStr 需要替换的字符串
rtarget needReplaceStr替换成的字符串
/************************************************************************/
void SResManager::string_replace(string&str,const string&needReplaceStr,const string&rtarget)
{
	string::size_type pos=0;
	string::size_type a=needReplaceStr.size();
	string::size_type b=rtarget.size();
	while((pos=str.find(needReplaceStr,pos))!=string::npos)
	{
		str.erase(pos,a);
		str.insert(pos,rtarget);
		pos+=b;
	}
}

/************************************************************************/
/* 加载一个动画                                                                     */
/************************************************************************/
XAnimation* SResManager::loadAnimation(int aniID,bool isUIFrame)
{
	if(aniID<0)
	{
		return NULL;
	}
	if(!isUIFrame && animations[aniID] != NULL){
		//检测纹理
		//loadATexture(node,animations[aniID]->nodeID,isUIFrame);
		return animations[aniID];
	}
	if(isUIFrame && gameui[aniID] != NULL)gameui[aniID];
	char str[64];
	memset(str,0,sizeof(str));
	sprintf(str,"%s/%d.bin",isUIFrame?UI_FILE_DIR:ANI_FILE_DIR,aniID);
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(str);
	DataInputStream* dis = DataInputStream::openFile(fullPath.c_str(),"rb");
	XAnimation *curAni = new XAnimation();
	//curAni->aniID = aniID;
	//pgameInfo->animations[aniID] = new ZAnimation();
	curAni->isRecyle = dis->readByte();
	curAni->Recycle_end = dis->readByte();
	curAni->recycle_end_startFP = dis->readInt();
	curAni->recycle_end_endFP = dis->readInt();
	curAni->recycle_end_count = dis->readInt();
	//pgameInfo->animations[aniID]->descrption = dis->readString();
	//帧数量
	short fpCount = dis->readShort();
	curAni->frameCount = fpCount;
	curAni->frames.resize(fpCount);

	for (int k = 0; k < fpCount; k++)
	{
		loadAnimation(dis,curAni,k,isUIFrame);
	}
	//物理属性
	if(!isUIFrame){
		int phyLen = dis->readByte();
		curAni->physics.resize(phyLen);
		for (int i = 0; i < phyLen; i++)
		{
			curAni->physics[i] = dis->readShort();
		}
	}
	//物理形状
	int phyLen = dis->readByte();
	curAni->polygonShapes.resize(phyLen);
	curAni->shapeType.resize(phyLen);
	curAni->shapeRadius.resize(phyLen);
	curAni->shapeSize.resize(phyLen);
	for(int i=0;i<phyLen;i++)
	{
		cbyte type = dis->readByte();
		float radius = dis->readFloat();
		curAni->shapeType[i] = type; 
		curAni->shapeRadius[i] = radius;
		if(type == SHAPE_TYPE_N)
		{
			int infoLen = dis->readInt();
			array2(float) info;
			info.resize(infoLen);
			for(int j=0;j<infoLen;j++)
			{
				array1(float) data;
				data.push_back(dis->readFloat());
				data.push_back(dis->readFloat());
				info[j] = data;
			}
			curAni->polygonShapes[i] = info;
		}
		else if(type == SHAPE_TYPE_RECT)
		{
			array1(float) info;
			info.resize(2);
			info[0] = dis->readFloat();
			info[1] = dis->readFloat();
			curAni->shapeSize[i] = info;
		}

	}
	curAni->nodeID = dis->readInt();
	DataInputStream::closeFile(dis);
	if(!isUIFrame){
		if(aniID<animations.size()){
			animations[aniID] = curAni;
		}
	}else{//是UI需要加载动画
		if(aniID<gameui.size()){
			gameui[aniID] = curAni;
		}
		for (int j = 0; j < curAni->frameCount; j++) {
			XFrame* frame = curAni->frames[j];
			for (short i = 0; i < frame->skins.size(); i++) {
				if( frame->skins[i]->baseInfo[SKIN_SELECT_FIREST]>=0 &&
					animations[frame->skins[i]->baseInfo[SKIN_SELECT_FIREST]] == NULL){
						animations[frame->skins[i]->baseInfo[SKIN_SELECT_FIREST]] = loadAnimation(frame->skins[i]->baseInfo[SKIN_SELECT_FIREST],false);
				}
				if(frame->skins[i]->baseInfo[SKIN_SELECT_SEC]>=0&&
					animations[frame->skins[i]->baseInfo[SKIN_SELECT_SEC]] == NULL){
						animations[frame->skins[i]->baseInfo[SKIN_SELECT_SEC]]  = loadAnimation(frame->skins[i]->baseInfo[SKIN_SELECT_SEC],false);
				}
			}
		}
	}
	return curAni;
};
void SResManager::loadAnimation(DataInputStream* dis,XAnimation* ani,int fpIndex,bool isUIFrame)
{
	XFrame* frame = new XFrame();
	ani->frames[fpIndex] = frame;
	if(!isUIFrame){
		int boxCount = dis->readByte();
		frame->boxs.resize(boxCount);
		for (int i = 0; i < boxCount; i++)
		{
			frame->boxs[i].resize(BOX_LEN);
			for (int j = 0; j < BOX_LEN; j++)
			{
				frame->boxs[i][j] = dis->readShort();
			}
		}

		//播放次数
		frame->playCount = dis->readShort();
		//每一帧受伤状态
		frame->fpHurt = dis->readShort();
		//每一帧位移
		frame->fpOffset = dis->readShort();
		//每一帧僵直
		frame->fpPause = dis->readShort();
		//每一帧音效
		frame->fpMusic= dis->readShort();
		//备用信息
		frame->fpSpare= dis->readInt();
		//关键帧
		frame->keyFrame = dis->readInt();
	}
	//module数量
	short moduleCount = dis->readShort();
	frame->skins.resize(moduleCount);
	frame->skinsorder.resize(moduleCount);
	for (int f = 0; f < moduleCount; f++)
	{
		frame->skinsorder[f] = dis->readInt();
	}
	for (int f = 0; f < moduleCount; f++)
	{
		frame->skins[f] = new XSkin();
		//换装信息
		cbyte ecount = dis->readByte();
		for(int i=0;i<ecount;i++)
		{
			array1(int)info;
			info.resize(2);
			info[0] = dis->readShort();
			info[1] = dis->readShort();
			frame->skins[f]->equipinfo.push_back(info);
			loadATexture(info[0],isUIFrame);
		}
		//滤色
		frame->skins[f]->lvse = dis->readByte()==1;
		//可见性
		frame->skins[f]->m_isVisiable = dis->readByte()==1;
		//属性
		frame->skins[f]->baseInfo.resize(SKIN_INFO_LEN);
		for (int i = 0; i < SKIN_INFO_LEN; i++)
		{
			frame->skins[f]->baseInfo[i] = dis->readShort();
			if(i == SKIN_INFO_TEXTUREID)
			{
				loadATexture(frame->skins[f]->baseInfo[i],isUIFrame);
			}
		}
		frame->skins[f]->setBaseInfo();
		//补间动画
		short keyFpCount = dis->readShort();
		frame->skins[f]->timenodes.resize(keyFpCount);

		for (int i = 0; i < keyFpCount; i++)
		{
			frame->skins[f]->timenodes[i] = new XTimeNodeData();
			for (int k = 0; k < INFO_LEN; k++)
			{
				frame->skins[f]->timenodes[i]->info[k] = dis->readFloat();
			}
			for (int k = 0; k < INFO_COLOR_LEN; k++)
			{
				frame->skins[f]->timenodes[i]->color[k] = dis->readInt();
			}
			dis->readString();
		}
		//button
		cbyte flag = dis->readByte();
		if(flag ==1)
		{
			frame->skins[f]->m_button = new XButton();
			frame->skins[f]->m_button->init();
			frame->skins[f]->m_button->synBtn = dis->readInt();
			for(int si =0;si<frame->skins[f]->m_button->btn_info.size();si++)
			{
				for(int sj=0;sj<frame->skins[f]->m_button->btn_info[si].size();sj++)
				{
					frame->skins[f]->m_button->btn_info[si][sj] = dis->readInt();
				}
			}
			//txt
			flag = dis->readByte();
			if(flag ==1)
			{
				//frame->skins[f]->m_button->text = dis->readString();
				frame->skins[f]->m_button->fontSize = dis->readInt();
				for(int si=0;si<3;si++)
				{
					frame->skins[f]->m_button->fontcolor[si] = dis->readInt();
				}
			}
			//音效
			frame->skins[f]->m_button->musicID = dis->readInt();
		}
		//scrollbar
		flag = dis->readByte();
		if(flag ==1)
		{
			frame->skins[f]->m_scrollbar = new XScrollbar();
			frame->skins[f]->m_scrollbar->init();
			for(int si =0;si<frame->skins[f]->m_scrollbar->btn_info.size();si++)
			{
				for(int sj=0;sj<frame->skins[f]->m_scrollbar->btn_info[si].size();sj++)
				{
					frame->skins[f]->m_scrollbar->btn_info[si][sj] = dis->readInt();
				}
			}
			frame->skins[f]->m_scrollbar->minValue = dis->readInt();
			frame->skins[f]->m_scrollbar->maxValue = dis->readInt();
			frame->skins[f]->m_scrollbar->s_value = dis->readInt();
			frame->skins[f]->m_scrollbar->point_Height = dis->readInt();
		}

		//numbar
		flag = dis->readByte();
		if(flag ==1)
		{
			frame->skins[f]->m_numbar = new XNumBar();
			frame->skins[f]->m_numbar->init();
			for(int sj=0;sj<frame->skins[f]->m_numbar->btn_info.size();sj++)
			{
				frame->skins[f]->m_numbar->btn_info[sj] = dis->readInt();
			}
			frame->skins[f]->m_numbar->s_value = dis->readFloat();
			frame->skins[f]->m_numbar->maxW = dis->readInt();
			frame->skins[f]->m_numbar->allowFloat = dis->readInt() ==1;
			frame->skins[f]->m_numbar->anchor = dis->readInt();
		}
		//textBox
		flag = dis->readByte();
		if(flag ==1)
		{
			frame->skins[f]->m_textbox = new XTextBox();
			//frame->skins[f]->m_textbox->text = dis->readString();
			frame->skins[f]->m_textbox->fontSize = dis->readInt();
			frame->skins[f]->m_textbox->anchor = dis->readInt();

			frame->skins[f]->m_textbox->speedX= dis->readFloat();
			frame->skins[f]->m_textbox->speedY= dis->readFloat();
			frame->skins[f]->m_textbox->fontOffsetX= dis->readFloat();
			frame->skins[f]->m_textbox->fontOffsetY= dis->readFloat();

			frame->skins[f]->m_textbox->w = dis->readInt();
			frame->skins[f]->m_textbox->h = dis->readInt();

			frame->skins[f]->m_textbox->autoChangeLine = dis->readInt()==1;
			frame->skins[f]->m_textbox->autoClip = dis->readInt()==1;
			frame->skins[f]->m_textbox->fontColor[0] = dis->readInt();
			frame->skins[f]->m_textbox->fontColor[1] = dis->readInt();
			frame->skins[f]->m_textbox->fontColor[2] = dis->readInt();
			dis->readByte();
			dis->readString();
			//frame->skins[f]->m_textbox->isEditBox = dis->readByte()==1;
			//frame->skins[f]->m_textbox->pswChar = dis->readString();
		}
		//plist
		flag = dis->readByte();
		if(flag ==1)
		{
			frame->skins[f]->m_particle = new XParticle();
			frame->skins[f]->m_particle->plsitPath = dis->readString();
			frame->skins[f]->m_particle->plisCount = dis->readInt();
			frame->skins[f]->m_particle->inteverX = dis->readFloat();
			frame->skins[f]->m_particle->inteverY = dis->readFloat();
			frame->skins[f]->m_particle->isRecycle = dis->readInt()>0;
		}
		//checkbox
		flag = dis->readByte();
		if(flag ==1)
		{
			frame->skins[f]->m_checkbox = new XCheckBox();
			frame->skins[f]->m_checkbox->init();
			for(int si =0;si<frame->skins[f]->m_checkbox->btn_info.size();si++)
			{
				for(int sj=0;sj<frame->skins[f]->m_checkbox->btn_info[si].size();sj++)
				{
					frame->skins[f]->m_checkbox->btn_info[si][sj] = dis->readInt();
				}
			}
			//music
			frame->skins[f]->m_checkbox->musicID = dis->readInt();
			frame->skins[f]->m_checkbox->isChecked = dis->readByte()==1;
		}
		//形状
		flag = dis->readByte();
		if(flag ==1)
		{
			cbyte type = dis->readByte();
			if(type == SHAPE_TYPE_N)
			{
				int infoLen = dis->readInt();
				array2(float) info;
				info.resize(infoLen);
				for(int j=0;j<infoLen;j++)
				{
					array1(float) data;
					data.push_back(dis->readFloat());
					data.push_back(dis->readFloat());
					info[j] = data;
				}
			}
			else if(type == SHAPE_TYPE_RECT)
			{
				float info1 = dis->readFloat();
				float info2 = dis->readFloat();
			}
		}
	}
}
 /***********************************************
 加载一个纹理 
 **********************************************/
 void SResManager::loadATexture(int textureID,bool isUIFrame)
 {
	 bool textureisExists = false;
	 CCTexture2D *texture = NULL;
	 char spngName[64];
	 memset(spngName,0,sizeof(spngName));
	 sprintf(spngName,"resource/%d.png",textureID);
	 if(XAnimation::testure_animation->objectForKey(spngName)){
		 textureisExists = true;
		// texture = (CCTexture2D*) XAnimation::testure_animation->objectForKey(spngName);
	 }else{
		 char pStr[64];
		 memset(pStr,0,sizeof(pStr));
		 sprintf(pStr,"resource/%d.plist",textureID);
		 if(USEOPIMG)
		 {
			 char spngName2[64];
			 memset(spngName2,0,sizeof(spngName2));
			 sprintf(spngName2,"resource/%d.bin",textureID);

			 std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(spngName2);
			 DataInputStream* dis = DataInputStream::openFile(fullPath.c_str(),"rb");
			 int len = dis->readInt();
			 dis->skip(len);
			 int width = dis->readInt();
			 int height = dis->readInt();
			 array1(unbyte)imgData;
			 dis->readunbyte(imgData);
			 texture = new CCTexture2D();
			 CCImage* IMG = new CCImage();
			 char *str = new char[imgData.size()+1];
			 copy(imgData.begin(),imgData.end(), str);
			 IMG->initWithImageData(str,imgData.size(),CCImage::kFmtPng,width,height);
			 texture->initWithImage(IMG);
			 delete str;
			 delete IMG;
			DataInputStream::closeFile(dis);
		 }else
		 {
			texture =  CCTextureCache::sharedTextureCache()->addImage(spngName);
		 }
		 
		 XAnimation::testure_animation->setObject(texture,spngName);
		 CCSpriteFrameCache::sharedSpriteFrameCache() ->addSpriteFramesWithFile(pStr,texture);
	 }
	/* if(dic_aniConfig == NULL)
	 {
		 dic_aniConfig = CCDictionary::create();
		 CC_SAFE_RETAIN(dic_aniConfig);
	 }
	 if(!testure_animation)
	 {
		 testure_animation = CCDictionary::create();
		 CC_SAFE_RETAIN(testure_animation);
	 }
	 ZPlist* tpConfig = NULL;
	 if(dic_aniConfig->objectForKey(textureID) ==NULL)
	 {
		 //加载配置文件
		 char str[64];
		 memset(str,0,sizeof(str));
		 sprintf(str,"resource/%d.bin",textureID);
		 std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(str);
		 DataInputStream* dis = DataInputStream::openFile(fullPath.c_str(),"rb");
		 if(dis)
		 {
			 tpConfig = new ZPlist();
			 tpConfig->autorelease();
			 int count = dis->readInt();
			 tpConfig->pFiles.resize(count);
			 for(int i = 0;i<count;i++)
			 {
				 tpConfig->pFiles[i] = dis->readString();
			 }
			 dic_aniConfig->setObject(tpConfig,textureID);
			 DataInputStream::closeFile(dis);
		 }
	 }else{
		 tpConfig = (ZPlist*)(dic_aniConfig->objectForKey(textureID));
	 }
	 if(tpConfig)
	 {
		 for(int i=0;i<tpConfig->pFiles.size();i++)
		 {
			 string texName = tpConfig->pFiles[i];
			 bool textureisExists = false;
			 CCTexture2D *texture = NULL;
			 if(testure_animation->objectForKey(texName)){
				 textureisExists = true;
				 texture = (CCTexture2D*) testure_animation->objectForKey(texName.c_str());
			 }
			 if(!textureisExists)
			 {
				 //textureTargetID.push_back(texName);
				 char pStr[64];
				 memset(pStr,0,sizeof(pStr));
				 sprintf(pStr,"resource/%s.plist",texName.c_str());

				 char imgStr[64];
				 memset(imgStr,0,sizeof(imgStr));
				 sprintf(imgStr,"resource/%s.png",texName.c_str());

				 texture =  CCTextureCache::sharedTextureCache()->addImage(imgStr);
				 testure_animation->setObject(texture,texName.c_str());
				 CCSpriteFrameCache::sharedSpriteFrameCache() ->addSpriteFramesWithFile(pStr,texture);
			 }
			 node->setTextureAlas(texture,texName,textureID);
			 //if(RUNATPC)
			 //	CCLOG(CCTextureCache::sharedTextureCache()->description());//监测当前有多少纹理未被释放
		 }
	 }else{//没有配置文件
		 bool textureisExists = false;
		 CCTexture2D *texture = NULL;
		 char spngName[64];
		 memset(spngName,0,sizeof(spngName));
		 sprintf(spngName,"resource/%d.png",textureID);
		 if(testure_animation->objectForKey(spngName)){
			 textureisExists = true;
			 texture = (CCTexture2D*) testure_animation->objectForKey(spngName);
		 }else{
			 char pStr[64];
			 memset(pStr,0,sizeof(pStr));
			 sprintf(pStr,"resource/%d.plist",textureID);
			 texture =  CCTextureCache::sharedTextureCache()->addImage(spngName);
			 testure_animation->setObject(texture,spngName);
			 CCSpriteFrameCache::sharedSpriteFrameCache() ->addSpriteFramesWithFile(pStr,texture);
		 }
		 char key[64];
		 memset(key,0,sizeof(key));
		 sprintf(key,"%d.single",textureID);
		 node->setTextureAlas_singlePng(texture,key);
	 }*/
 }
 XAnimation* SResManager::createAAnimation(int aniID)
 {
	 XAnimation* ani = loadAnimation(aniID,true);
	 XAnimation* res = XAnimation::create(ani);

	 return res;
 }
 bool SResManager::touchInBlock(int frameID,int blockID,float x,float y)
 {
	 return gameui[frameID]->frames[0]->skins[blockID]->containTouchPoint(x,y);
 }
 CCPoint SResManager::getPosition(int frameID,int blockID)
 {
	 return gameui[frameID]->frames[0]->s_getLocation(blockID);
 }
 int SResManager::getBlockZorder(int frameID,int blockID)
 {
	 return gameui[frameID]->frames[0]->skins[blockID]->getZOrder();
 }
 /************************************************************************/
 /* 不循环播放   结束后清除                                                                  */
 /************************************************************************/
 void SResManager::ZUI_show_needRemoved(CCNode* node,int aniID,int frameID,int blockID)
 {
	 if(gameui[frameID] == NULL)
	 {
		 loadAnimation(frameID,true);
	 }
	 CCPoint p = gameui[frameID]->frames[0]->skins[blockID]->s_getLocation();
	 XAnimation* ani  = createAAnimation(aniID);
	 ani->flagId = aniID;
	 ani->setXY(p.x+m_gamestate->curScreenW/2,p.y+m_gamestate->curScreenH/2);
	 ani->initBaseBySprite();
	 ani->removedAtOver = true;
	 node->addChild(ani,1000+aniID);
	  ui_added.push_back(ani);
 }
 void SResManager::ZUI_show_needRemoved(CCNode* node,int aniID,int frameID,int blockID,int flagID)
 {
	 if(gameui[frameID] == NULL)
	 {
		 loadAnimation(frameID,true);
	 }
	 CCPoint p = gameui[frameID]->frames[0]->skins[blockID]->s_getLocation();
	 XAnimation* ani  = createAAnimation(aniID);
	 ani->flagId = aniID;
	 float xx = p.x+m_gamestate->curScreenW/2;
	 float yy = p.y+m_gamestate->curScreenH/2;
	 ani->setXY(p.x+m_gamestate->curScreenW/2,p.y+m_gamestate->curScreenH/2);
	 ani->initBaseBySprite();
	 ani->removedAtOver = true;
	 node->addChild(ani,flagID);
	 ui_added.push_back(ani);
 }
 void SResManager::ZUI_show_needRemovedByPosition(CCNode* node,int frameID,float x,float y)
 {
	 if(gameui[frameID] == NULL)
	 {
		 loadAnimation(frameID,true);
	 }
	 XAnimation* ani  = createAAnimation(frameID);
	 ani->setXY(x,y);
	 ani->initBaseBySprite();
	 ani->removedAtOver = true;
	 node->addChild(ani,1000);
	 ui_added.push_back(ani);
 }
 void SResManager::ZUI_setButtonState(int frameID,int blockID,int state)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(frame->skins[blockID]->m_button)
			 {
				 frame->skins[blockID]->m_button->setState(state);
				 //同步按钮
				 if( frame->skins[blockID]->m_button->synBtn>=0 && 
					 frame->skins[blockID]->m_button->synBtn<frame->skins.size() &&
					 frame->skins[frame->skins[blockID]->m_button->synBtn]->m_button)
				 {
					 frame->skins[frame->skins[blockID]->m_button->synBtn]->m_button->setState(state);
				 }
				 break;
			 }
			 break;
		 }
	 }
 }
void SResManager::ZUI_setOpticity(int frameID,int opcity)
{

	for(int i=ui_added.size()-1;i>=0;i--)
	{
		if(ui_added[i]->flagId == frameID)
		{
			XFrame* frame = ui_added[i]->frames[0];
			for(int j=0;j<frame->skins.size();j++)
			{
				frame->skins[j]->m_setOpticity(opcity);
			}
			break;
		}
	}
}

CCSize SResManager::ZUI_getSize(int frameID, int blockID)
{
	CCSize size(0, 0);

	if(gameui[frameID] && blockID>=0 && blockID< gameui[frameID]->frames[0]->skins.size())
	{
		size.width = gameui[frameID]->frames[0]->skins[blockID]->baseInfo[SKIN_INFO_RECT_W];
		size.height= gameui[frameID]->frames[0]->skins[blockID]->baseInfo[SKIN_INFO_RECT_H];
	}	
	
	return size;
}

 void SResManager::ZUI_setScale(int frameID,float scaleX,float scaleY)
 {
	 gameui[frameID]->setScale(scaleX,scaleY);
 }
 void SResManager::ZUI_setScale(int frameID,int blockID,float scaleX,float scaleY)
 {
	 if(gameui[frameID] && blockID>=0 && blockID< gameui[frameID]->frames[0]->skins.size())
		 gameui[frameID]->frames[0]->skins[blockID]->s_setScale(scaleX,scaleY);
 }
 void SResManager::ZUI_addAFrame(int frameId,float x,float y)
 {
	 XAnimation* ani = loadAnimation(frameId,true);
	// ani->aniID = frameId;
	 ani->initBaseBySprite();
	 ani->setXY(x,y);
 }
 /************************************************************************/
 /* 删除一个UI 移除该UI所有资源                                                                     */
 /************************************************************************/
 void SResManager::ZUI_deleteAFrame(int frameId)
 {
	 if( gameui[frameId] == NULL)
	 {
		 return;
	 }
	 for(int i=0;i<ui_added.size();i++)
	 {
		 if(ui_added[i]->flagId == frameId)
		 {
			 ZUI_removeAFrame(frameId);
		 }
	 }
	 if( gameui[frameId])
	 {
		 CC_SAFE_DELETE(gameui[frameId]);
		 gameui[frameId] = NULL;
	 }

 }
 void SResManager::ZUI_show(CCNode* node,int frameId,bool fillalpha,float x,float y,bool canPointOther)
 {
	 if( gameui[frameId] == NULL)
	 {
		 ZUI_addAFrame(frameId,x,y);
	 }

	 gameui[frameId]->removeFromParent();
	 gameui[frameId]->setXY(x,y);
	 gameui[frameId]->canPointOthers = canPointOther;
	 gameui[frameId]->reset();
	 gameui[frameId]->fillAlpha = fillalpha;

	 node->addChild(gameui[frameId],1000);
	 ui_added.push_back(gameui[frameId]);
	 ui_added[ui_added.size()-1]->flagId = frameId;
 }
 void SResManager::ZUI_show(CCNode* node,int frameId,bool fillalpha,float x,float y,bool canPointOther,int zOrder)
 {
	 if( gameui[frameId] == NULL)
	 {
		 ZUI_addAFrame(frameId,x,y);
	 }

	 gameui[frameId]->removeFromParent();
	 gameui[frameId]->setXY(x,y);
	 gameui[frameId]->canPointOthers = canPointOther;
	 gameui[frameId]->reset();
	 gameui[frameId]->fillAlpha = fillalpha;

	 node->addChild(gameui[frameId],zOrder);
	 ui_added.push_back(gameui[frameId]);
	 ui_added[ui_added.size()-1]->flagId = frameId;
 }
 /************************************************************************/
 /* ui文本同时显示                                                                     */
 /************************************************************************/
 void SResManager::ZUI_showForText(CCNode* node,int frameId,bool fillalpha,float x,float y,bool canPointOther)
 {
	 if( gameui[frameId] == NULL)
	 {
		 ZUI_addAFrame(frameId,x,y);
	 }
	 gameui[frameId]->removeFromParent();
	 gameui[frameId]->setXY(x,y);
	 gameui[frameId]->canPointOthers = canPointOther;
	 gameui[frameId]->reset();
	 gameui[frameId]->fillAlpha = fillalpha;
	 node->addChild(gameui[frameId],1000);
	 ui_added.push_back(gameui[frameId]);
	 ui_added[ui_added.size()-1]->flagId = frameId;

	 XFrame* frame = ui_added[ui_added.size()-1]->frames[0];
	 for(int blockID = 0;blockID<frame->skins.size();blockID++)
	 {
		 if(frame->skins[blockID]->m_textbox)
		 {
			 ZUI_setText(frameId,blockID,ZUI_getText(frameId,blockID));
		 }
	 }
 }
 void SResManager::ZUI_show(CCNode* node,int frameId,bool fillalpha,int zOrder)
 {
	 for(int i=0;i<ui_added.size();i++)
	 {
		 if(ui_added[i]->flagId == frameId)
		 {
			 return;
		 }
	 }
	 if(frameId>=0 && frameId<gameui.size())
	 {
		 if( gameui[frameId] == NULL)
		 {
			 loadAnimation(frameId,true);
		 }
		 gameui[frameId]->fillAlpha = fillalpha;

		 gameui[frameId]->reset();
		 node->addChild(gameui[frameId],zOrder);
		 ui_added.push_back(gameui[frameId]);
		 ui_added[ui_added.size()-1]->flagId = frameId;
	 }
 }
 void SResManager::ZUI_show(CCNode* node,int frameId,bool fillalpha)
 {
	 for(int i=0;i<ui_added.size();i++)
	 {
		 if(ui_added[i]->flagId == frameId)
		 {
			 return;
		 }
	 }

	 if(frameId>=0 && frameId<gameui.size())
	 {
		 if( gameui[frameId] == NULL)
		 {
			  loadAnimation(frameId,true);
		 }
		 gameui[frameId]->fillAlpha = fillalpha;
		 gameui[frameId]->reset();

		 node->addChild(gameui[frameId]);
		 ui_added.push_back(gameui[frameId]);
		 ui_added[ui_added.size()-1]->flagId = frameId;
	 }
 }
 void SResManager::ZUI_removeAFrame(int frameId)
 {
	
	 if(frameId>=0 && frameId<gameui.size() && gameui[frameId])
	 {
		 gameui[frameId]->removeFromParent();
		 for(int i=ui_added.size()-1;i>=0;i--)
		 {
			 if(ui_added[i]->flagId ==  frameId)
			 {
				 ui_added[i]->reset();
				 ui_added.erase(ui_added.begin()+i);
				 break;
			 }
		 }
	 }
 }
 void SResManager::ZUI_doMove(int frameID,int blockID,float x,float y)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size())
			 {
				 frame->skins[blockID]->doMove(x,y);
			 }
			 break;
		 }
	 }
 }
 void SResManager::ZUI_setDelayTime(int frameID,int dt)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 ui_added[i]->setDelayTime(dt);
			 break;
		 }
	 }
 }
 void SResManager::ZUI_setCheckBoxStateChangedListener(CCObject* sender,int frameID,int blockID,ZUI_StateChangedEvent listener)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_checkbox)
			 {
				 frame->skins[blockID]->m_checkbox->setStateChengedListener(sender,listener);
			 }
			 break;
		 }
	 }
 }
 void SResManager::ZUI_setValueChangedListener(CCObject* sender,int frameID,int blockID,ZUI_ValueChangedEvent listener)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_scrollbar)
			 {
				 frame->skins[blockID]->m_scrollbar->setValuechangedListener(sender,listener);
			 }
			 break;
		 }
	 }
 }
 void SResManager::ZUI_setNumForNumbar(int frameID,int blockID,float num)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_numbar)
			 {
				 frame->skins[blockID]->m_numbar->setNum(num);
				 frame->skins[blockID]->m_numbar->m_setVisiable(frame->skins[blockID]->m_isVisiable);
			 }
			 break;
		 }

	 }
 }
 void SResManager::ZUI_setNumForNumbar(int frameID,int blockID,string num)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_numbar)
			 {
				 frame->skins[blockID]->m_numbar->setNum(num);
			 }
			 break;
		 }

	 }
 }
 void SResManager::ZUI_setNumForNumbar_LL(int frameID,int blockID,unsigned long long num)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_numbar)
			 {
				 string str;
				 stringstream ss;
				 ss<<num;
				 ss>>str; 
				 frame->skins[blockID]->m_numbar->setNum(str);
			 }
			 break;
		 }

	 }
 }
 void SResManager::ZUI_setValueForScrollBar(int frameID,int blockID,int num)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_scrollbar)
			 {
				 frame->skins[blockID]->setValue(num);
			 }
			 break;
		 }

	 }
 }
 bool SResManager::isChecked(int frameID,int blockID)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_checkbox)
			 {
				 return frame->skins[blockID]->checkBoxIsChecked();
			 }
			 break;
		 }
	 }
	 return false;
 }
 void SResManager::ZUI_setCheckBoxState(int frameID,int blockID,bool state)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_checkbox)
			 {
				 frame->skins[blockID]->setCheckBoxState(state);
			 }
			 break;
		 }
	 }
 }
 void SResManager::ZUI_setStateChangedListener(CCObject* sender,int frameID,int blockID,ZUI_StateChangedEvent listener)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_checkbox)
			 {
				 frame->skins[blockID]->m_checkbox->setStateChengedListener(sender,listener);
			 }
			 break;
		 }
	 }
 }
 void SResManager::ZUI_SetFrameButtonsListener(CCObject* sender,int frameID,ZUI_ClickEventByID listener)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 for(int blockID =0;blockID<frame->skins.size() ;blockID++)
			 {
				 if(frame->skins[blockID]->m_button)
				 {
					 frame->skins[blockID]->m_button->setClickListener(sender,listener,blockID);
				 }
			 }
			 break;
		 }
	 }
 }
 void SResManager::ZUI_setClickListener(CCObject* sender,int frameID,int blockID,ZUI_ClickEvent listener)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_button)
			 {
				 frame->skins[blockID]->m_button->setClickListener(sender,listener);
			 }
			 break;
		 }
	 }
 }
 /************************************************************************/
 /* 设置控件状态                                                                     */
 /************************************************************************/
 void SResManager::ZUI_setStateForControl(int frameID,int blockID,int state)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() &&frame->skins[blockID]->m_button)
			 {
				 frame->skins[blockID]->m_button->setState(state);
				 //同步按钮
				 if( frame->skins[blockID]->m_button->synBtn>=0 && 
					 frame->skins[blockID]->m_button->synBtn<frame->skins.size() &&
					 frame->skins[frame->skins[blockID]->m_button->synBtn]->m_button)
				 {
					 frame->skins[frame->skins[blockID]->m_button->synBtn]->m_button->setState(state);
				 }
			 }
			 break;
		 }

	 }
 }
 /************************************************************************/
/* 开始进度条
 type kCCProgressTimerTypeRadial 中心点旋转  kCCProgressTimerTypeBar进度条
 duration 时间
 fFromPercentage 开始值%
 fToPercentage 结束值
 reverseProgress 是否循环
 selector 回调函数  exp :SResManager::callBack(CCNode* node)  callfuncN_selector(SResManager::callBack)
/************************************************************************/
 void SResManager::ZUI_setProgressTimer(int frameID,int blockID,CCProgressTimerType type,float duration, float fFromPercentage, float fToPercentage,bool ReverseProgress,SEL_CallFuncN selector)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() )
			 {
				 frame->skins[blockID]->startProgressTimer(type,duration,fFromPercentage,fToPercentage,ReverseProgress,selector);
			 }
			 break;
		 }

	 }
 }
 void SResManager::ZUI_stopProgress(int frameID,int blockID)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() )
			 {
				 frame->skins[blockID]->stopProgress();
			 }
			 break;
		 }

	 }
 }
 /************************************************************************/
 /* 设置骨骼可见性                                                                     */
 /************************************************************************/
 void SResManager::ZUI_setVisiableForBone(XFrame* frame,int blockID,bool visiable)
 {
	 if(blockID>=0 && blockID<frame->skins.size() )
	 {
		 frame->skins[blockID]->m_setVisiable(visiable);
		 //是骨骼。绑定的子对象需要同步
		 if(frame->skins[blockID]->baseInfo[SKIN_INFO_ISBONE]>0)
		 {
			 for(int i=0;i<frame->skins.size();i++)
			 {
				 if(frame->skins[i]->baseInfo[SKIN_INFO_PARENTID] == blockID)
				 {
					 frame->skins[i]->m_setVisiable(visiable);
				 }
			 }
		 }
	 }
 }
 void SResManager::ZUI_setVisiable(int frameID,int blockID,bool visiable)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() )
			 {
				 frame->skins[blockID]->m_setVisiable(visiable);
				 //是骨骼。绑定的子对象需要同步
				 if(frame->skins[blockID]->baseInfo[SKIN_INFO_ISBONE]>0)
				 {
					 ZUI_setVisiableForBone(frame,blockID,visiable);
				 }
			 }
			 break;
		 }

	 }
 }
 /************************************************************************/
 /* 设置文字信息 BY editor                                                                     */
 /************************************************************************/
 void SResManager::ZUI_setTextBySelf(int frameID,int blockID)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() )
			 {
				 if( frame->skins[blockID]->m_textbox)
				 {
					 frame->skins[blockID]->m_textbox->setText(ZUI_getText(frameID,blockID));
				 }
			 }
			 break;
		 }
	 }
 }
 void SResManager::ZUI_setText(int frameID,int blockID,string text)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() )
			 {
				 if( frame->skins[blockID]->m_textbox)
				 {
					 frame->skins[blockID]->m_textbox->setText(text);
				 }
			 }
			 break;
		 }
	 }
 }
string SResManager::ZUI_getText(int frameID,int blockID)
 {
	 string text = "";
	 if(uistrings)
	 {
		 char buf[20];
		 memset(buf,0,sizeof(buf));
		 sprintf(buf,"f_%d_%d",frameID,blockID);
		 text = ((CCString*)uistrings->objectForKey(buf))->m_sString;
		// text.replace("|#","\n");
		string_replace(text,"|#","\n");
	 }
	 return text;
 }
/************************************************************************/
/* UI换装                                                                     */
/************************************************************************/
void SResManager::changeEquip(int frameID,int blockID,int equipIndex)
{
	for(int i=ui_added.size()-1;i>=0;i--)
	{
		if(ui_added[i]->flagId == frameID)
		{
			XFrame* frame = ui_added[i]->frames[0];
			if(blockID>=0 && blockID<frame->skins.size() )
			{
				frame->skins[blockID]->changeEquip(equipIndex);
			}
			break;
		}
	}
}
 void SResManager::changeSkin(int frameID,int blockID,char*path)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size() )
			 {
				 frame->skins[blockID]->changeTexture(path);
			 }
			 break;
		 }

	 }
 }
 void SResManager::changeTextureForButton(int frameID,int blockID,char*path,int type)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size()&& frame->skins[blockID]->m_button )
			 {
				 frame->skins[blockID]->m_button->changeRes(path,type);
			 }
			 break;
		 }

	 }
 }
/************************************************************************/
/* 检测按钮是否被点击                                                                     */
/************************************************************************/
 bool SResManager::ZUI_ButtonPressed(int frameID,int blockID)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 && blockID<frame->skins.size()&& frame->skins[blockID]->m_button )
			 {
				 return frame->skins[blockID]->m_button->bePressed();
			 }
			 break;
		 }

	 }
	 return false;
 }
 void SResManager::ZUI_update()
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->runOver)
		 {
			 ui_added[i]->removeFromParent();
			 XAnimation* ani = ui_added[i];
			 ui_added.erase(ui_added.begin()+i);
			 CC_SAFE_DELETE(ani);
		 }else
		 {
			  ui_added[i]->play();
		 }
	 }
	 //
	 for(int i=ui_animations.size()-1;i>=0;i--)
	 {
		 if(ui_animations[i]->runOver)
		 {
			 ui_animations[i]->removeFromParent();
			 XAnimation* ani = ui_animations[i];
			 ui_animations.erase(ui_animations.begin()+i);
			 CC_SAFE_DELETE(ani);
		 }else
		 {
			  ui_animations[i]->play();
		 }
	 }
 }
 void SResManager::ccTouchesBegan(float x,float y)
 {
	
	 if(!allowAcceptPoint)return;
	  //m_game->touchBegin(x,y);
	 touch_x = x;
	 touch_y = y;
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 XFrame* frame = ui_added[i]->frames[0];
		 bool pressekSkin = false;
		 for(int j = frame->skins.size()-1;j>=0;j--)
		 {
			 if(frame->skins[j]->m_isVisiable && frame->skins[j]->containTouchPoint(x,y))
			 {
				 if(frame->skins[j]->m_button && frame->skins[j]->m_button->isPressable())
				 {
					 frame->skins[j]->m_button->setState(BTN_ST_PRES);
					 if( frame->skins[j]->m_button->synBtn>=0 && 
						 frame->skins[j]->m_button->synBtn<frame->skins.size() &&
						 frame->skins[frame->skins[j]->m_button->synBtn]->m_button)
					 {
						  frame->skins[frame->skins[j]->m_button->synBtn]->m_button->setState(BTN_ST_PRES);
					 }
					 pressekSkin = true;
					 break;
				 }
				 else  if(frame->skins[j]->m_checkbox)
				 {
					 frame->skins[j]->bePressedForCheckBox(true);//复选框
					 break;
				 }
			 }
			 if(frame->skins[j]->m_scrollbar && frame->skins[j]->containTouchPointOnScrollBtn(x,y))
			 {
				 frame->skins[j]->m_scrollbar->setState(BTN_ST_PRES);
				 pressekSkin = true;
				 break;
			 }
		 }
		 if(pressekSkin)break;
		 if(i<ui_added.size() && !ui_added[i]->canPointOthers)
		 {
			 break;
		 }
	 }
 }
 void SResManager::ccTouchesMoved(float x,float y)
 {
//	 m_game->touchMoved(x,y);
	 touch_x = -10000;
	 touch_y = -10000;
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 bool someBodyScroll = false;
		 XFrame* frame = ui_added[i]->frames[0];
		 for(int j = frame->skins.size()-1;j>=0;j--)
		 {
			 //scroll
			 if(frame->skins[j]->m_scrollbar && frame->skins[j]->containTouchPoint(x,y))
			 {
				 if(frame->skins[j]->m_scrollbar &&  frame->skins[j]->m_scrollbar->bePressed())
				 {
					 frame->skins[j]->onScorll(x,y);
					 someBodyScroll = true;
					 break;
				 }
			 }
		 }
		 if(someBodyScroll)
		 {
			 break;
		 }
	 }
 } 
 void SResManager::ccTouchesEnded(float x,float y)
 {

	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(i>= ui_added.size())break;
		 XFrame* frame = ui_added[i]->frames[0];
		 for(int j = frame->skins.size()-1;j>=0;j--)
		 {
			//click
			 if(frame->skins[j]->containTouchPoint(x,y))
			 {
				 if(frame->skins[j]->m_button &&  frame->skins[j]->m_button->bePressed())
				 {
					 playButtonMusic(frame->skins[j]->m_button->musicID);
					 frame->skins[j]->m_button->setState(BTN_ST_NOR);
					 frame->skins[j]->m_button->click();
					 
					 //同步按钮
					 if( frame->skins[j]->m_button->synBtn>=0 && 
						 frame->skins[j]->m_button->synBtn<frame->skins.size() &&
						 frame->skins[frame->skins[j]->m_button->synBtn]->m_button)
					 {
						 frame->skins[frame->skins[j]->m_button->synBtn]->m_button->setState(BTN_ST_NOR);
						 frame->skins[frame->skins[j]->m_button->synBtn]->m_button->click();
					 }
				 }
			 }
			 if(frame->skins[j]->m_button&&  frame->skins[j]->m_button->bePressed())
			 {
				  frame->skins[j]->m_button->setState(BTN_ST_NOR);
			 }
			 else  if(frame->skins[j]->m_checkbox && frame->skins[j]->m_checkbox->bePressed)
			 {
				 frame->skins[j]->changeCheckBoxState();
				 break;
			 }
		 }
		 if(i<ui_added.size() && !ui_added[i]->canPointOthers)
		 {
			 break;
		 }
	 }
	 if(abs(x-touch_x)<=2 && abs(y-touch_y)<=2)
	 {
		 ccClickedEnded(x,y);
	 }
	// m_game->touchEnded(x,y);
 } 
 void SResManager::ccClickedEnded(float x,float y)
 {
	// m_game->click(x,y);
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 bool someBodyScroll = false;
		 XFrame* frame = ui_added[i]->frames[0];
		 for(int j = frame->skins.size()-1;j>=0;j--)
		 {
			 //scroll
			 if(frame->skins[j]->containTouchPoint(x,y))
			 {
				 if(frame->skins[j]->m_scrollbar)
				 {
					 frame->skins[j]->onScorll(x,y);
					 someBodyScroll = true;
					 break;
				 }
			 }
		 }
		 if(someBodyScroll)
		 {
			 break;
		 }
		 if(i<ui_added.size() && !ui_added[i]->canPointOthers)
		 {
			 break;
		 }
	 }
 }
 /************************************************************************/
 /* 下层UI是否能接收触摸                                                                   */
 /************************************************************************/
 bool SResManager::canAcceptPoint()
 {
	 if(ui_added.size()>0)
	 {
		 int order = ui_added.size()-1;
		 if(order>=0)
		 {
			 return !ui_added[order]->fillAlpha;//下层覆盖了半透明视为下层UI不能接受触摸
		 }
		 
	 }
	 return true;
 }
 /************************************************************************/
 /* 获得当前所有的UI                                                                     */
 /************************************************************************/
 array1(int) SResManager::getCurFrames()
 {
	 array1(int)result;
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 result.push_back(ui_added[i]->flagId);
	 }
	 return result;
 }

 void SResManager::ZUI_showAnimation(CCNode* node,int aniID,float x,float y,bool removedAtOver, int zorder)
 {
	 if(animations[aniID] == NULL)
	 {
		 loadAnimation(aniID,false);
	 }
	 XAnimation* ani = XAnimation::create(animations[aniID]);
	 ani->removedAtOver = removedAtOver;
	 ani->flagId = aniID;
	 ani->initBaseBySprite();
	 ani->setXY(x,y);
	 ui_animations.push_back(ani);
	 int order = zorder == 0 ? 2000+ui_animations.size(): zorder;
	 node->addChild(ani, order);

 }
 void SResManager::ZUI_removeAnimation(int aniID)
 {
	 for(int i=ui_animations.size()-1;i>=0;i--)
	 {
		 if( ui_animations[i]->flagId == aniID)
		 {
			 ui_animations[i]->removeFromParent();
			 XAnimation* ani = ui_animations[i];
			 ui_animations.erase(ui_animations.begin()+i);
			 CC_SAFE_DELETE(ani);
		 }
	 }
 }
 void SResManager:: ZUI_setFrameStartFP(int frameID,int startFp)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			ui_added[i]->setStartFP(startFp);
		 }
	 }
 }
 void SResManager:: ZUI_SetBlockPosition(int frameID,int blockID,float x,float y)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {

			 XFrame* frame = ui_added[i]->frames[0];
			 if(blockID>=0 &&  blockID< frame->skins.size()-1)
			 {
				 frame->skins[blockID]->m_setPosition(x,y);
			 }
		 }
	 }
 }
 void SResManager:: ZUI_SETPosition(int frameID,int x,int y)
 {
	 for(int i=ui_added.size()-1;i>=0;i--)
	 {
		 if(ui_added[i]->flagId == frameID)
		 {
			 ui_added[i]->setPosition(ccp(x,y));
		 }
	 }
 }
 XAnimation* SResManager::getAnimation(int animationId)
 {
	 return animations[animationId];
 }
#define MUSIC_UI_OK 0
 #define MUSIC_UI_CANCEL 1
 void SResManager:: playButtonMusic(int musicID)
 {
	 /*string path= "";
	 switch(musicID)
	 {
	 case MUSIC_UI_OK:
		 path = "music/OK.ogg";
		 break;
	 case MUSIC_UI_CANCEL:
		 path = "music/CANCEL.ogg";
		 break;
	 }*/
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(EFF_BUTTONCLICK);
 }
