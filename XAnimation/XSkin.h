#ifndef __x_XSKIN__
#define __x_XSKIN__
#include "SConfig.h"
#include "XTextBox.h"
#include "Tools.h"
//����¼�
typedef void (CCObject::*ZUI_ClickEvent)(CCObject*);
#define toucheventselector(_SELECTOR) (ZUI_ClickEvent)(&_SELECTOR)

//����¼�
typedef void (CCObject::*ZUI_ClickEventByID)(CCObject*,int handleId);
#define toucheventselectorById(_SELECTOR) (ZUI_ClickEventByID)(&_SELECTOR)
//�����¼�
typedef void (CCObject::*ZUI_ValueChangedEvent)(CCObject*,float);
#define valuechangedventselector(_SELECTOR) (ZUI_ValueChangedEvent)(&_SELECTOR)


//״̬�ı��¼�
typedef void (CCObject::*ZUI_StateChangedEvent)(CCObject*,bool);
#define statechangedventselector(_SELECTOR) (ZUI_StateChangedEvent)(&_SELECTOR)


#define MOUSE_STATE_LEFT_RIGHT 0//������ҵ���߻����ұ� Xб��
#define MOUSE_STATE_UP_DOWN 1//������ҵ������������ Yб��
#define MOUSE_STATE_INMYAREA 2//������ҵ����� ��ת

#define SKIN_INFO_LEN 13 //�������ݳ���
#define SKIN_INFO_TEXTUREID 0//����ID
#define SKIN_INFO_SPRITEID 1// ����ID

#define SKIN_INFO_RECT_X 2//�������е�����
#define SKIN_INFO_RECT_Y 3//
#define SKIN_INFO_RECT_W 4//
#define SKIN_INFO_RECT_H 5//
#define SKIN_INFO_ISBONE 6//�Ƿ��ǹ���
#define SKIN_INFO_PARENTID 7//���ڵ�Index
#define SKIN_SELECT_FIREST 8//��һ��ѡ��
#define SKIN_SELECT_SEC 9//�ڶ���ѡ�ж���
#define SKIN_OTHER1 10
#define SKIN_OTHER2 11
#define SKIN_OTHER3 12

#define  NONE  -9999
#define  INFO_LEN  17
#define  INFO_STARTFP  0
#define  INFO_X  1//X
#define  INFO_Y  2//Y
#define  INFO_ROTX  3//x��ת ����б��
#define  INFO_ROTY  4//Y��ת ����б��
#define  INFO_SCALEX 5//W
#define  INFO_SCALEY  6//H
#define  INFO_ROTATION  7//��ת�Ƕ�
#define  INFO_ALPHA  8//͸����
#define  INFO_ANCHOR_X  9//��תê��X
#define  INFO_ANCHOR_Y  10//��תê��Y
#define  INFO_HASTHING  11//�Ƿ�����¼� 0���¼� 1 ���¼�
#define  INFO_LOCKED  12//���� 0������ 1 ����
#define  INFO_VISIBLE  13//��ʾ 0��ʾ 1����ʾ
#define  INFO_SKEWX  14//X����б
#define  INFO_SKEWY  15//Y����б
#define  INFO_ACC 16//�ȼ���

#define  VISIBLE  0//��ʾ
#define  DISVISIBLE  1//����ʾ

#define INFO_COLOR_LEN 3//��ɫ
#define INFO_COLOR_R 0
#define INFO_COLOR_G 1
#define INFO_COLOR_B 2

#define  BTN_ST_NOR 0//��ͨ״̬
#define  BTN_ST_PRES 1//���״̬
#define  BTN_ST_DIS 2//����״̬
#define COR_IMG_PRO_LEN  8
#define COR_IMG_TEXID  0//IMG id
#define COR_IMG_SPRITEID  1//sprite id
#define COR_IMG_OFFSETX 2
#define COR_IMG_OFFSETY 3
#define  COR_IMG_COLOR_R 4
#define  COR_IMG_COLOR_G 5
#define  COR_IMG_COLOR_B 6
#define  COR_IMG_ALPHA 7
#define BTN_TYPE_PRESSED 0
#define BTN_TYPE_DISABLE 1
#define BTN_TYPE_NOR_TXT 2
#define BTN_TYPE_PRESSED_TXT 3
#define BTN_TYPE_DISABLE_TXT 4

#define CHECKBOX_TYPE_CHECKED 0//��ѡ��ѡ��
#define CHECKBOX_TYPE_NOTCHECKED 1//��ѡ��δѡ��
#define CHECKBOX_TYPE_PRESSED 2//��ѡ����

#define SCROLLB_TYPE_DEFAULT 0//��������ť-Ĭ��
#define SCROLLB_TYPE_PRESSED 1//��������ť-����״̬
#define SCROLLB_TYPE_DISABLE 2//��������ť-����״̬
#define SCROLLB_TYPE_PROCESS 3//��������ť-������
#define ANCHOR_L 0//ê����
#define ANCHOR_HV 1//����
#define ANCHOR_R 2//��
struct XTimeNodeData 
{
		float info[INFO_LEN];
		int color[INFO_COLOR_LEN];
		bool isLocked(){
			return info[INFO_LOCKED] ==1;
		}
};
struct XCheckBox
{
	CCObject* sper;
	ZUI_StateChangedEvent stateChangedEventListener;
	array2(int) btn_info;
	int musicID;
	bool isChecked;
	bool bePressed;
	void init()
	{
		stateChangedEventListener = NULL;
		sper = NULL;
		musicID = -1;
		bePressed = false;
		isChecked = false;
		btn_info.resize(3);
		for(int i=0;i<btn_info.size();i++)
		{
			btn_info[i].resize(COR_IMG_PRO_LEN);
		}
	}
	void destory()
	{
		stateChangedEventListener = NULL;
	}

	void setStateChengedListener(CCObject* sper,ZUI_StateChangedEvent listener)
	{
		this->sper = sper;
		stateChangedEventListener = listener;
	}
	/************************************************************************/
	/* ״̬�ı�                                                                     */
	/************************************************************************/
	void stateChaged()
	{
		isChecked = !isChecked;
		if (sper && stateChangedEventListener)
		{
			(sper->*stateChangedEventListener)(sper,isChecked);
		}
	}
	void setState(bool state)
	{
		isChecked = state;
	}
};
/************************************************************************/
/* ���Ӷ���                                                                     */
/************************************************************************/
struct XParticle
{
	array1(CCParticleSystem *)particles;//���Ӷ���
	int plisCount;
	string plsitPath;
	float inteverX;
	float inteverY;
	bool isRecycle;
	bool hided;//����
	void init()
	{
		hided = false;
		isRecycle = false;
		plisCount = 1;
		inteverX = 0;
		inteverY = 0;
	}
	void destory()
	{
		/*for(int i=particles.size()-1;i>=0;i--)
		{
			if(particles[i])
			{
				particles[i]->removeAllChildren();
				particles[i]->removeFromParent();
				particles[i] = NULL;
			}
		}*/
		particles.clear();
	}
	void stop()
	{
		for(int i=0;i<particles.size();i++)
		{
			particles[i]->setDuration(0);
		}
	}
	void added(CCSprite* skin,float x,float y)
	{
		destory();
		string ppath = "plists/"+plsitPath;
		for(int i=0;i<plisCount;i++)
		{

			CCParticleSystem *plist = CCParticleSystemQuad::create(ppath.c_str());
			plist->setPosition(ccp(x+i*inteverX,y+i*inteverY));
			if(isRecycle)
			{
				plist->setDuration(-1);
			}
			particles.push_back(plist);
			skin->addChild(plist);
		}
		/************************************************************************
		this->particle->setDuration(time*1.0f/FPS_RATE);//�ۼ�ʱ������
		if(!particle->isActive()&&particle->getParticleCount()==0)
		isAutoRemoveOnFinish
		/************************************************************************/
	}
};
struct XNumBar
{
public:
	int s_value;//��ʼֵ
	int maxW;//���ֵ
	int anchor;
	int m_opticity;
	bool allowFloat;
	array1(float) btn_info;
	CCSprite*parent;
	//CCSprite* num_default_bg;//Ĭ��ͼƬ
	array1(CCSprite*)sprit_nums;
	void init()
	{
		m_opticity =255;
		allowFloat = false;
		s_value = 0;//��ʼֵ
		maxW = 100;//���ֵ
		anchor = ANCHOR_L;
		btn_info.resize(COR_IMG_PRO_LEN);
	}
	void destory()
	{
		for(int i=0;i<sprit_nums.size();i++)
		{
			if(sprit_nums[i])
			{
				sprit_nums[i]->removeFromParent();
				CC_SAFE_DELETE(sprit_nums[i]);
			}
		}
		sprit_nums.resize(0);
	}
	void m_setVisiable(bool visiable)
	{
		for(int i=0;i<sprit_nums.size();i++)
		{
			if(sprit_nums[i])
			{
				sprit_nums[i]->setVisible(visiable);
			}
		}
	}
	void setNum(string str)
	{
		for(int i=0;i<sprit_nums.size();i++)
		{
			if(sprit_nums[i])
			{
				sprit_nums[i]->removeFromParent();
				CC_SAFE_DELETE(sprit_nums[i]);
			}
		}

		sprit_nums.resize(str.length());
		CCSize size = parent->getContentSize();
		float numW = allowFloat?size.width/11:size.width/10;//�����ֿ��
		float curW = numW;
		float scale = 1.0f;
		float x = 0;
		float y = size.height/2;
		if(numW*str.length()>maxW)
		{
			scale = maxW/(numW*str.length());
			curW = scale*numW;
		}
		switch(anchor)
		{
		case ANCHOR_R:
			x-=curW*str.length();
			break;
		case ANCHOR_HV:
			x-=curW*str.length()/2;
			break;
		}
		x+= btn_info[COR_IMG_OFFSETX];
		y+= btn_info[COR_IMG_OFFSETY];
		for(int i=0;i<str.length();i++)
		{

			//CCRect ptRect =parent->getTextureRect();
			int num = (int)str[i]-48;
			int cx =num *numW;
			sprit_nums[i] = CCSprite::createWithTexture(parent->getTexture(),CCRect(cx,0,numW,size.height));
			sprit_nums[i]->retain();
			sprit_nums[i]->setScaleX(scale);
			sprit_nums[i]->setOpacity(m_opticity);
			sprit_nums[i]->setPosition(ccp(x+i*curW,y));
			sprit_nums[i]->setColor(ccc3(btn_info[COR_IMG_COLOR_R],btn_info[COR_IMG_COLOR_G],btn_info[COR_IMG_COLOR_B]));
			parent->addChild(sprit_nums[i]);
		}
	}
	void setNum(float num)
	{
		stringstream os;
		if(allowFloat)
		{
			os << num;
		}else
		{
			int tn = (int)num;
			os<<tn;
		}
		string str = os.str();
		setNum(str);

	}
	void added(CCSprite* pnode)
	{
		parent = pnode;
		setNum(s_value);
	}
	void update(int opcity)
	{
		m_opticity = opcity;
		for(int i=0;i<sprit_nums.size();i++)
		{
			sprit_nums[i]->setOpacity(opcity);
			sprit_nums[i]->setColor(ccc3(btn_info[COR_IMG_COLOR_R],btn_info[COR_IMG_COLOR_G],btn_info[COR_IMG_COLOR_B]));
		}
	}
};
struct XScrollbar
{
public:
	int s_value;//��ʼֵ
	int minValue ;//��Сֵ
	int maxValue;//���ֵ
	int point_Height;//������չ�߶�
	int btn_state;
	int processW;
	CCSize size_process;
	array2(int) btn_info;
	CCSprite* btn_default_bg;//Ĭ��ͼƬ
	CCSprite* btn_pressed_bg;//����
	CCSprite* btn_disable_bg;//����
	CCSprite* process_bg;//������
	CCObject* vcobj_sender;
	ZUI_ValueChangedEvent valueChangedListener;
	void setValuechangedListener(CCObject* sender,ZUI_ValueChangedEvent listener)
	{
		this->vcobj_sender = sender;
		valueChangedListener = listener;
	}
	void init()
	{
		processW = 0;
		s_value = 0;//��ʼֵ
		minValue = 0;//��Сֵ
		maxValue = 100;//���ֵ
		setState(BTN_ST_NOR);
		btn_info.resize(4);
		for(int i=0;i<btn_info.size();i++)
		{
			btn_info[i].resize(COR_IMG_PRO_LEN);
		}
		btn_default_bg = NULL;
		btn_pressed_bg = NULL;
		btn_disable_bg = NULL;
		process_bg = NULL;
	}
	void setValue(int svalue)
	{
		if(svalue<minValue)svalue = minValue;
		if(svalue>maxValue)svalue = maxValue;
		this->s_value = svalue;
		if (vcobj_sender && valueChangedListener)
		{
			(vcobj_sender->*valueChangedListener)(vcobj_sender,s_value);
		}
		if(process_bg)
		{
			CCSize size = process_bg->getTexture()->getContentSize();
			float w =  s_value*size.width/(maxValue-minValue);
			process_bg->setTextureRect(CCRect(0,0,w,size.height));
		}
	}
	void setValue(int svalue,float x,float y)
	{
		if(svalue<minValue)svalue = minValue;
		if(svalue>maxValue)svalue = maxValue;
		this->s_value = svalue;
		if (vcobj_sender && valueChangedListener)
		{
			(vcobj_sender->*valueChangedListener)(vcobj_sender,s_value);
		}

		if(process_bg)
		{
			CCSize size = process_bg->getTexture()->getContentSize();
			float w =  s_value*size.width/(maxValue-minValue);
			process_bg->setTextureRect(CCRect(0,0,w,size.height));
			x = process_bg->getPositionX()+w;
		}
		if(btn_default_bg)
		{
			btn_default_bg->setPosition(ccp(x,y));
		}
	}
	void setState(int state)
	{
		btn_state = state;
	}
	bool bePressed()
	{
		return btn_state == BTN_ST_PRES;
	}
	void destory()
	{
		if(btn_default_bg)
		{
			btn_default_bg->removeFromParent();
			CC_SAFE_DELETE(btn_default_bg);
		}
		if(btn_pressed_bg)
		{
			btn_pressed_bg->removeFromParent();
			CC_SAFE_DELETE(btn_pressed_bg);
		}
		if(btn_disable_bg)
		{
			btn_disable_bg->removeFromParent();
			CC_SAFE_DELETE(btn_disable_bg);
		}
		if(process_bg)
		{
			process_bg->removeFromParent();
			CC_SAFE_DELETE(process_bg);
		}
	}
	CCPoint getLocation()
	{
		return btn_default_bg->getPosition();
	}
	CCPoint getSize()
	{
		CCPoint size = btn_default_bg->getContentSize();
		switch(btn_state)
		{
		case BTN_ST_PRES:
			if(btn_pressed_bg)
			{
				size = btn_pressed_bg->getContentSize();
			}
			break;
		case BTN_ST_DIS:
			if(btn_disable_bg)
			{
				size = btn_disable_bg->getContentSize();
			}
			break;
		}
		return size;
	}
	/************************************************************************/
	/* ��ʾĬ�ϱ���                                                                     */
	/************************************************************************/
	bool showNorBg()
	{
		return btn_state == BTN_ST_NOR || (btn_state == BTN_ST_PRES && !btn_pressed_bg)|| (btn_state == BTN_ST_DIS && !btn_disable_bg);
	}
	void updateBtnLocation(float x,float y)
	{
		if(process_bg)
		{
			CCSize size = process_bg->getTexture()->getContentSize();
			float w =  s_value*size.width/(maxValue-minValue);
			x = process_bg->getPositionX()+w;
		}
		if(btn_default_bg)
		{
			//x += btn_info[SCROLLB_TYPE_DEFAULT][COR_IMG_OFFSETX];
			//y += btn_info[SCROLLB_TYPE_DEFAULT][COR_IMG_OFFSETY];
			btn_default_bg->setPosition(ccp(x,y));
		}
		if(btn_pressed_bg)
		{
			//x += btn_info[SCROLLB_TYPE_PRESSED][COR_IMG_OFFSETX];
			//y += btn_info[SCROLLB_TYPE_PRESSED][COR_IMG_OFFSETY];
			btn_pressed_bg->setPosition(ccp(x,y));
		}
		if(btn_disable_bg)
		{
			//x += btn_info[SCROLLB_TYPE_DISABLE][COR_IMG_OFFSETX];
			//y += btn_info[SCROLLB_TYPE_DISABLE][COR_IMG_OFFSETY];
			btn_disable_bg->setPosition(ccp(x,y));
		}
	}
	void initRes(int x,int y,float w)
	{
		x += s_value*w/(maxValue-minValue);//�������ƶ�
		for(int i=0;i<btn_info.size();i++)
		{
			if(i == SCROLLB_TYPE_PROCESS)
			{
				char buf[64];
				memset(buf,0,sizeof(buf));
				sprintf(buf,"p_%d_%d.png",btn_info[i][COR_IMG_TEXID],btn_info[i][COR_IMG_SPRITEID]);
				CCSpriteFrameCache *framecache = CCSpriteFrameCache::sharedSpriteFrameCache();
				CCSpriteFrame*frame = framecache->spriteFrameByName(buf);
				CCSprite* tmp = new CCSprite();
				tmp->initWithSpriteFrame(frame);
				CCImage* img = Tools::getImgFromSprite(tmp,tmp->getContentSize().width,tmp->getContentSize().height);
				CCTexture2D * tex = new CCTexture2D();
				tex->initWithImage(img);
				process_bg = new CCSprite();
				process_bg->initWithTexture(tex);
				CC_SAFE_DELETE(tmp);
				if(process_bg)
				{
					process_bg->setAnchorPoint(ccp(0,0.5f));
					process_bg->retain();
				}
				
			}else
			{
				char image[64];
				memset(image,0,sizeof(image));
				sprintf(image,"p_%d_%d.png",btn_info[i][COR_IMG_TEXID],btn_info[i][COR_IMG_SPRITEID]);
				CCSpriteFrameCache *framecache = CCSpriteFrameCache::sharedSpriteFrameCache();
				CCSpriteFrame*frame = framecache->spriteFrameByName(image);
				if(frame)
				{
					switch(i)
					{
					case SCROLLB_TYPE_DEFAULT:
						btn_default_bg = new CCSprite();
						btn_default_bg->initWithSpriteFrame(frame);
						btn_default_bg->retain();
						break;
					case SCROLLB_TYPE_PRESSED://����
						btn_pressed_bg = new CCSprite();
						btn_pressed_bg->initWithSpriteFrame(frame);
						btn_pressed_bg->retain();
						break;
					case SCROLLB_TYPE_DISABLE://����
						btn_disable_bg = new CCSprite();
						btn_disable_bg->initWithSpriteFrame(frame);
						btn_disable_bg->retain();
						break;
					}
				}
			}
			
		}
	}
	void added(CCNode* pnode,float x,float y,float w)
	{
		processW= w;
		if(process_bg)
		{
			CCSize size = process_bg->getTexture()->getContentSize();
			processW = size.width;
			float w =  s_value*size.width/(maxValue-minValue);
			process_bg->setPosition(ccp(x+btn_info[SCROLLB_TYPE_PROCESS][COR_IMG_OFFSETX],y+btn_info[SCROLLB_TYPE_PROCESS][COR_IMG_OFFSETY]));
			process_bg->setTextureRect(CCRect(0,0,w,size.height));
			pnode->addChild(process_bg);
		    x = process_bg->getPositionX()+w;
		}

		//x += s_value*processW/(maxValue-minValue);//�������ƶ�
		if(btn_default_bg)
		{
			//x += btn_info[SCROLLB_TYPE_DEFAULT][COR_IMG_OFFSETX];
			//y += btn_info[SCROLLB_TYPE_DEFAULT][COR_IMG_OFFSETY];
			btn_default_bg->setPosition(ccp(x,y));
			pnode->addChild(btn_default_bg);
		}
		if(btn_pressed_bg)
		{
			//x += btn_info[SCROLLB_TYPE_PRESSED][COR_IMG_OFFSETX];
			//y += btn_info[SCROLLB_TYPE_PRESSED][COR_IMG_OFFSETY];
			btn_pressed_bg->setPosition(ccp(x,y));
			pnode->addChild(btn_pressed_bg);
		}
		if(btn_disable_bg)
		{
			//x += btn_info[SCROLLB_TYPE_DISABLE][COR_IMG_OFFSETX];
			//y += btn_info[SCROLLB_TYPE_DISABLE][COR_IMG_OFFSETY];
			btn_disable_bg->setPosition(ccp(x,y));
			pnode->addChild(btn_disable_bg);
		}
	}
	void update(int opcity)
	{

		int opcity_nor = 0;
		int opcity_pressed = 0;
		int opcity_disable = 0;
		opcity = 255-opcity;
		if(opcity<0)opcity = 0;
		switch(btn_state)
		{
		case BTN_ST_NOR:
			opcity_nor = btn_info[SCROLLB_TYPE_DEFAULT][COR_IMG_ALPHA]+opcity;
			opcity_nor = 255-opcity_nor;
			if(opcity_nor<0)opcity_nor =0;
			if(opcity_nor>255)opcity_nor = 255;
			break;
		case BTN_ST_PRES:

			opcity_pressed = btn_info[SCROLLB_TYPE_PRESSED][COR_IMG_ALPHA]+opcity;
			opcity_pressed = 255-opcity_pressed;
			if(opcity_pressed<0)opcity_pressed =0;
			if(opcity_pressed>255)opcity_pressed = 255;
			break;
		case BTN_ST_DIS:
			opcity_disable = btn_info[SCROLLB_TYPE_DISABLE][COR_IMG_ALPHA]+opcity;
			opcity_disable = 255-opcity_disable;
			if(opcity_disable<0)opcity_disable =0;
			if(opcity_disable>255)opcity_disable = 255;
			break;
		}
		switch(btn_state)
		{
		case BTN_ST_PRES:
			if(!btn_pressed_bg)
			{
				opcity_nor = opcity_pressed;
			}
			break;
		case BTN_ST_DIS:
			if(!btn_disable_bg)
			{
				opcity_nor = opcity_disable;
			}
			break;
		}
		if(btn_default_bg)
		{
			btn_default_bg->setOpacity(opcity_nor);
			btn_default_bg->setColor(ccc3(btn_info[SCROLLB_TYPE_DEFAULT][COR_IMG_COLOR_R],btn_info[SCROLLB_TYPE_DEFAULT][COR_IMG_COLOR_G],btn_info[SCROLLB_TYPE_DEFAULT][COR_IMG_COLOR_B]));
		}
		if(btn_pressed_bg)
		{

			btn_pressed_bg->setOpacity(opcity_pressed);
			btn_pressed_bg->setColor(ccc3(btn_info[SCROLLB_TYPE_PRESSED][COR_IMG_COLOR_R],btn_info[SCROLLB_TYPE_PRESSED][COR_IMG_COLOR_G],btn_info[SCROLLB_TYPE_PRESSED][COR_IMG_COLOR_B]));
		}
		if(btn_disable_bg)
		{
			btn_disable_bg->setOpacity(opcity_disable);
			btn_disable_bg->setColor(ccc3(btn_info[SCROLLB_TYPE_DISABLE][COR_IMG_COLOR_R],btn_info[SCROLLB_TYPE_DISABLE][COR_IMG_COLOR_G],btn_info[SCROLLB_TYPE_DISABLE][COR_IMG_COLOR_B]));
		}
	}
};

struct XButton
{
public:
	int musicID;
	int synBtn;//ͬ����ť
	int btn_state;
	array2(int) btn_info;
	string text;//����
	int fontSize ;
	int fontcolor[3];
	CCLabelTTF* btn_txt_label;
	CCSprite* btn_sp_txt_normal;//����ͼƬ
	CCSprite* btn_sp_pressed;//����
	CCSprite* btn_sp_txt_pressed;//����ͼƬ
	CCSprite* btn_sp_disable;//����
	CCSprite* btn_sp_txt_disable;//����ͼƬ
	CCObject* sper;
	ZUI_ClickEvent clickEventListener;
	ZUI_ClickEventByID clickEventListerById;
	int handleId;
	CCImage* bgImg;
	
	void setClickListener(CCObject* sper,ZUI_ClickEvent listener)
	{
		this->sper = sper;
		clickEventListener = listener;
	}
	void setClickListener(CCObject* sper,ZUI_ClickEventByID listener,int handleId)
	{
		this->sper = sper;
		clickEventListerById = listener;
		this->handleId = handleId;
	}
	void init()
	{
		handleId = -1;
		musicID = -1;
		btn_state = BTN_ST_NOR;
		fontSize = 14;
		btn_info.resize(5);
		for(int i=0;i<btn_info.size();i++)
		{
			btn_info[i].resize(COR_IMG_PRO_LEN);
		}
		clickEventListener = NULL;
		btn_txt_label = NULL;
		btn_sp_pressed = NULL;
		btn_sp_disable = NULL;
		btn_sp_txt_normal = NULL;
		btn_sp_txt_pressed = NULL;
		btn_sp_txt_disable = NULL;
		bgImg = NULL;
	}
	void initBGImg(CCSprite* sprite,float w,float h)
	{
		ccColor4B color4B = {0, 0, 0, 0};  
		//��ʼ׼������  
		CCRenderTexture* m_pRenderTexture = CCRenderTexture::create(w,h, kCCTexture2DPixelFormat_RGBA8888);  
		m_pRenderTexture->ignoreAnchorPointForPosition(true);  
		m_pRenderTexture->setPosition(ccp(400, 240));  
		m_pRenderTexture->setAnchorPoint(CCPointZero); 

		m_pRenderTexture->begin();  
		//����ʹ�õ���ʱ���飬��ԭͼ��ͬһͼƬ  
		CCSprite* pTempSpr = CCSprite::createWithSpriteFrame(sprite->displayFrame());  
		pTempSpr->setPosition(ccp(w / 2, h / 2));  
		pTempSpr->visit();  
		if(btn_sp_txt_normal)
		{
			CCSprite* pTempSpr2 = CCSprite::createWithSpriteFrame(btn_sp_txt_normal->displayFrame());  
			pTempSpr2->setPosition(ccp(w / 2+btn_info[BTN_TYPE_NOR_TXT][COR_IMG_OFFSETX], h / 2+btn_info[BTN_TYPE_NOR_TXT][COR_IMG_OFFSETY]));  
			pTempSpr2->visit();  
			CC_SAFE_RELEASE(pTempSpr2);
		}
		//����  

		//��������  
		m_pRenderTexture->end();  
		//ͨ�������õ����Ż�����ÿ�����ص����Ϣ����װ��CCImage��  
		bgImg =m_pRenderTexture->newCCImage();  
		bgImg->retain();
		//������ɺ�������������  
		m_pRenderTexture->clear(0, 0, 0, 0);  
		CC_SAFE_RELEASE(m_pRenderTexture);
		CC_SAFE_RELEASE(pTempSpr);
	}
	void click()
	{
		if(handleId>=0)
		{
			if (sper && clickEventListerById && btn_state != BTN_ST_DIS)
			{
				(sper->*clickEventListerById)(sper,handleId);
			}
		}
		else if (sper && clickEventListener && btn_state != BTN_ST_DIS)
		{
			(sper->*clickEventListener)(sper);
		}
	}
	void destory()
	{
		if(btn_txt_label)
		{
			btn_txt_label->removeFromParent();
			CC_SAFE_DELETE(btn_txt_label);
			btn_txt_label = NULL;
		}
		if(btn_sp_pressed)
		{
			btn_sp_pressed->removeFromParent();
			CC_SAFE_DELETE(btn_sp_pressed);
			btn_sp_pressed = NULL;
		}
		if(btn_sp_disable)
		{
			btn_sp_disable->removeFromParent();
			CC_SAFE_DELETE(btn_sp_disable);
			btn_sp_disable = NULL;
		}
		if(btn_sp_txt_normal)
		{
			btn_sp_txt_normal->removeFromParent();
			CC_SAFE_DELETE(btn_sp_txt_normal);
			btn_sp_txt_normal = NULL;
		}
		if(btn_sp_txt_pressed)
		{
			btn_sp_txt_pressed->removeFromParent();
			CC_SAFE_DELETE(btn_sp_txt_pressed);
			btn_sp_txt_pressed = NULL;
		}
		if(btn_sp_txt_disable)
		{
			btn_sp_txt_disable->removeFromParent();
			CC_SAFE_DELETE(btn_sp_txt_disable);
			btn_sp_txt_disable = NULL;
		}
		if(bgImg)
		{
			CC_SAFE_DELETE(bgImg);
			bgImg = NULL;
		}
	}
	void changeRes(char* path,int type)
	{
		switch(type)
		{
		case BTN_TYPE_PRESSED:
			if(btn_sp_pressed == NULL)
			{
				btn_sp_pressed = new CCSprite();
				btn_sp_pressed->retain();
			}
			btn_sp_pressed->initWithFile(path);
			break;
		case BTN_TYPE_DISABLE:
			if(btn_sp_disable == NULL)
			{
				btn_sp_disable = new CCSprite();
				btn_sp_disable->retain();
			}
			btn_sp_disable->initWithFile(path);
			break;
		case BTN_TYPE_NOR_TXT:
			if(btn_sp_txt_normal == NULL)
			{
				btn_sp_txt_normal = new CCSprite();
				btn_sp_txt_normal->retain();
			}
			btn_sp_txt_normal->initWithFile(path);
			break;
		case BTN_TYPE_PRESSED_TXT:
			if(btn_sp_txt_pressed == NULL)
			{
				btn_sp_txt_pressed = new CCSprite();
				btn_sp_txt_pressed->retain();
			}
			btn_sp_txt_pressed->initWithFile(path);
			break;
		case BTN_TYPE_DISABLE_TXT://����ͼƬ          
			if(btn_sp_txt_disable == NULL)
			{
				btn_sp_txt_disable = new CCSprite();
				btn_sp_txt_disable->retain();
			}
			btn_sp_txt_disable->initWithFile(path);
			break;
		}
	}
	void initRes()
	{
		if(text.length()>0)
		{
			btn_txt_label = CCLabelTTF::create();
			btn_txt_label->setFontSize(fontSize);
			btn_txt_label->setColor(ccc3(fontcolor[0],fontcolor[1],fontcolor[2]));
			btn_txt_label->setString(text.c_str());
		}
		for(int i=0;i<btn_info.size();i++)
		{
			if(btn_info[i][COR_IMG_TEXID] == -1 || btn_info[i][COR_IMG_SPRITEID] == -1 )continue;
			char image[64];
			memset(image,0,sizeof(image));
			sprintf(image,"p_%d_%d.png",btn_info[i][COR_IMG_TEXID],btn_info[i][COR_IMG_SPRITEID]);
			CCSpriteFrameCache *framecache = CCSpriteFrameCache::sharedSpriteFrameCache();
			CCSpriteFrame*frame = framecache->spriteFrameByName(image);
			if(frame)
			{
				switch(i)
				{
				case BTN_TYPE_PRESSED:
					btn_sp_pressed = new CCSprite();
					btn_sp_pressed->initWithSpriteFrame(frame);
					btn_sp_pressed->retain();
					break;
				case BTN_TYPE_DISABLE:
					btn_sp_disable = new CCSprite();
					btn_sp_disable->initWithSpriteFrame(frame);
					btn_sp_disable->retain();
					break;
				case BTN_TYPE_NOR_TXT:
					btn_sp_txt_normal = new CCSprite();
					btn_sp_txt_normal->initWithSpriteFrame(frame);
					btn_sp_txt_normal->retain();
					break;
				case BTN_TYPE_PRESSED_TXT:
					btn_sp_txt_pressed = new CCSprite();
					btn_sp_txt_pressed->initWithSpriteFrame(frame);
					btn_sp_txt_pressed->retain();
					break;
				case BTN_TYPE_DISABLE_TXT://����ͼƬ          
					btn_sp_txt_disable = new CCSprite();
					btn_sp_txt_disable->initWithSpriteFrame(frame);
					btn_sp_txt_disable->retain();
					break;
				}
			}
		}
	}
	void added(CCNode* pnode,float x,float y)
	{
		if(btn_sp_pressed)
		{
			btn_sp_pressed->setOpacity(0);
			btn_sp_pressed->setPosition(ccp(x+btn_info[BTN_TYPE_PRESSED][COR_IMG_OFFSETX],y+btn_info[BTN_TYPE_PRESSED][COR_IMG_OFFSETY]));
			pnode->addChild(btn_sp_pressed);
			
		}

		if(btn_sp_disable)
		{
			btn_sp_disable->setOpacity(0);
			btn_sp_disable->setPosition(ccp(x+btn_info[BTN_TYPE_DISABLE][COR_IMG_OFFSETX],y+btn_info[BTN_TYPE_DISABLE][COR_IMG_OFFSETY]));
			pnode->addChild(btn_sp_disable);

		}
		if(btn_sp_txt_normal)
		{
			btn_sp_txt_normal->setPosition(ccp(x+btn_info[BTN_TYPE_NOR_TXT][COR_IMG_OFFSETX],y+btn_info[BTN_TYPE_NOR_TXT][COR_IMG_OFFSETY]));
			pnode->addChild(btn_sp_txt_normal);
		}
		if(btn_sp_txt_pressed)
		{
			btn_sp_txt_pressed->setOpacity(0);
			btn_sp_txt_pressed->setPosition(ccp(x+btn_info[BTN_TYPE_PRESSED_TXT][COR_IMG_OFFSETX],y+btn_info[BTN_TYPE_PRESSED_TXT][COR_IMG_OFFSETY]));
			pnode->addChild(btn_sp_txt_pressed);
			
		}

		if(btn_sp_txt_disable)
		{
			btn_sp_txt_disable->setOpacity(0);
			btn_sp_txt_disable->setPosition(ccp(x+btn_info[BTN_TYPE_DISABLE_TXT][COR_IMG_OFFSETX],y+btn_info[BTN_TYPE_DISABLE_TXT][COR_IMG_OFFSETY]));
			pnode->addChild(btn_sp_txt_disable);
		}

	}
	void setState(int state)
	{
		btn_state = state;
	}
	//�Ƿ���Ե��
	bool isPressable()
	{
		return btn_state != BTN_ST_DIS;
	}
	/************************************************************************/
	/* ��ʾĬ�ϱ���                                                                     */
	/************************************************************************/
	bool showNorBg()
	{
		return btn_state == BTN_ST_NOR || (btn_state == BTN_ST_PRES && btn_sp_pressed==NULL)|| (btn_state == BTN_ST_DIS && btn_sp_disable==NULL);
	}
	bool bePressed()
	{
		return btn_state == BTN_ST_PRES;
	}
	void update(int opcity)
	{
		
		opcity = 255-opcity;
		if(opcity<0)opcity = 0;
		int opcity_nor = 0;
		int opcity_pressed = 0;
		int opcity_disable = 0;
		int opcity_txt_nor = 0;
		int opcity_txt_pressed = 0;
		int opcity_txt_disable = 0;
		switch(btn_state)
		{
		case BTN_ST_NOR:
			//opcity_nor = btn_info[BTN_TYPE_][COR_IMG_ALPHA]+opcity;
			opcity_txt_nor = btn_info[BTN_TYPE_NOR_TXT][COR_IMG_ALPHA]+opcity;

			opcity_txt_nor = 255-opcity_txt_nor;
			if(opcity_txt_nor<0)opcity_txt_nor =0;
			if(opcity_txt_nor>255)opcity_txt_nor = 255;
			break;
		case BTN_ST_PRES:
			opcity_pressed = btn_info[BTN_TYPE_PRESSED][COR_IMG_ALPHA]+opcity;
			opcity_txt_pressed = btn_info[BTN_TYPE_PRESSED_TXT][COR_IMG_ALPHA]+opcity;

			opcity_pressed = 255-opcity_pressed;
			if(opcity_pressed<0)opcity_pressed =0;
			if(opcity_pressed>255)opcity_pressed = 255;

			opcity_txt_pressed = 255-opcity_txt_pressed;
			if(opcity_txt_pressed<0)opcity_txt_pressed =0;
			if(opcity_txt_pressed>255)opcity_txt_pressed = 255;
			break;
		case BTN_ST_DIS:
			opcity_disable = btn_info[BTN_TYPE_DISABLE][COR_IMG_ALPHA]+opcity;
			opcity_txt_disable = btn_info[BTN_TYPE_DISABLE_TXT][COR_IMG_ALPHA]+opcity;

			opcity_disable = 255-opcity_disable;
			if(opcity_disable<0)opcity_disable =0;
			if(opcity_disable>255)opcity_disable = 255;

			opcity_txt_disable = 255-opcity_txt_disable;
			if(opcity_txt_disable<0)opcity_txt_disable =0;
			if(opcity_txt_disable>255)opcity_txt_disable = 255;
			break;
		}
		switch(btn_state)
		{
		case BTN_ST_PRES:
			if(!btn_sp_txt_pressed)
			{
				opcity_txt_nor = opcity_txt_pressed;
			}
			break;
		case BTN_ST_DIS:
			if(!btn_sp_txt_disable)
			{
				opcity_txt_nor = opcity_txt_disable;
			}else
			{
				//opcity_txt_disable = opcity_txt_nor;
			}
			break;
		}
		//�ȿ������֡��ٿ���ͼƬ
		if(btn_txt_label)
		{
			//btn_txt_label->setAdditionalTransform(parent->nodeToParentTransform());
		}
		if(btn_sp_txt_normal)
		{
			btn_sp_txt_normal->setOpacity(opcity_txt_nor);
			btn_sp_txt_normal->setColor(ccc3(btn_info[BTN_TYPE_NOR_TXT][COR_IMG_COLOR_R],btn_info[BTN_TYPE_NOR_TXT][COR_IMG_COLOR_G],btn_info[BTN_TYPE_NOR_TXT][COR_IMG_COLOR_B]));
		}
		if(btn_sp_pressed)
		{
			btn_sp_pressed->setOpacity(opcity_pressed);
			btn_sp_pressed->setColor(ccc3(btn_info[BTN_TYPE_PRESSED][COR_IMG_COLOR_R],btn_info[BTN_TYPE_PRESSED][COR_IMG_COLOR_G],btn_info[BTN_TYPE_PRESSED][COR_IMG_COLOR_B]));
		}
		if(btn_sp_txt_pressed)
		{
			btn_sp_txt_pressed->setOpacity(opcity_txt_pressed);
			btn_sp_txt_pressed->setColor(ccc3(btn_info[BTN_TYPE_PRESSED_TXT][COR_IMG_COLOR_R],btn_info[BTN_TYPE_PRESSED_TXT][COR_IMG_COLOR_G],btn_info[BTN_TYPE_PRESSED_TXT][COR_IMG_COLOR_B]));

		}

		if(btn_sp_disable)
		{
			btn_sp_disable->setOpacity(opcity_disable);
			btn_sp_disable->setColor(ccc3(btn_info[BTN_TYPE_DISABLE][COR_IMG_COLOR_R],btn_info[BTN_TYPE_DISABLE][COR_IMG_COLOR_G],btn_info[BTN_TYPE_DISABLE][COR_IMG_COLOR_B]));
		}
		if(btn_sp_txt_disable)
		{
			btn_sp_txt_disable->setOpacity(opcity_txt_disable);
			btn_sp_txt_disable->setColor(ccc3(btn_info[BTN_TYPE_DISABLE_TXT][COR_IMG_COLOR_R],btn_info[BTN_TYPE_DISABLE_TXT][COR_IMG_COLOR_G],btn_info[BTN_TYPE_DISABLE_TXT][COR_IMG_COLOR_B]));
		}
	}
};
class XSkin : public CCSprite
{
public:
	
	XSkin(void);
	~XSkin(void);
	static XSkin* create(XSkin* skin);
public:
	bool focused;//�Ƿ�ѡ��
	bool issetted;
	int m_parentNode;//���ڵ�
	CCNode* aniNodeForLink;//���ڶ����Ľڵ�
	CCRect rectInImage;//�������е�����
	float rotation;
	bool lvse;
	bool isTextBox;
	bool valueChanging;//���ڸı�ֵ
	array1(XTimeNodeData*) timenodes;
	array1(float)baseInfo;
	array2(int)equipinfo;
	int m_imgId;
	int m_spriteId;
	float info_tween[INFO_LEN];//��ǰ������Ϣ
	int color_tween[INFO_COLOR_LEN];
	int curColor[INFO_COLOR_LEN];//���и��ڵ��ʱ�����óɸ��ڵ���ͬ����ɫ
	int curTimeNode;//��ǰʱ��ڵ�
	CCNode* childRect;//ѡ�еľ��ο�
	CCSprite* spriteForBone;//��������
	XButton* m_button;
	XScrollbar* m_scrollbar;
	XNumBar* m_numbar;
	XTextBox* m_textbox;
	XParticle* m_particle;
	XCheckBox* m_checkbox;//��ѡ��
	CCProgressTimer *progressTimer;
	bool doprogress;//����ʾ����
	bool m_isVisiable;
	int m_opcitiy;
	float offsetX;
	float offsetY;
public:
	void doMove(float offx,float offy);
	void setParentNode(int nodeIndex);
	void setAniNode(CCNode* node);//�������ڶ����Ľڵ�
	void setBaseInfo();
	void setTimeNodes(int count,float data[],int colordata[]);
	bool updateTimeNodeData(int time);
	void updateTimeNodeInfo(int timeNodeIndex,float data[],int colordata[]);
	void updateCheckBox();
	void bePressedForCheckBox(bool pressed);
	void changeCheckBoxState();
	void setCheckBoxState(bool state);
	bool checkBoxIsChecked()
	{
		if(m_checkbox)
		{
			return m_checkbox->isChecked;
		}
		return false;
	};
	bool containTouchPoint( float x,float y);
	bool containTouchPointOnScrollBtn( float x,float y);
	CCPoint s_getLocation();
	void focus();
	void loseFocus();//ʧȥ����
	int getTimeNode(int time);
	bool intersectsRect(float x,float y,float w,float h);
	void stopProgress();//ֹͣ����
	void m_setVisiable(bool visiable);
	void start();
	void s_setScale(float scalex,float scaley);
	void m_setPosition(float x,float y);
	void changeTexture(char*path);
	void changeEquip(int equipIndex);
	void m_setOpticity(float opci)
	{
		m_opcitiy = opci;
	}
	//������
	void startProgressTimer(CCProgressTimerType type,float duration, float fFromPercentage, float fToPercentage,bool ReverseProgress,SEL_CallFuncN selector);
	void reset()
	{
		curTimeNode = 0;
	};
	void onScorll(float x,float y);
	void setValue(int num);
	void visit();
	void removeAllRes();
	void msetRotation(float rx){rotation = rx;};
	//void setRotationY(float ry){rotationY = ry;};
	//void update(float delta);
};
#endif