#ifndef __x_XANIMATION__
#define __x_XANIMATION__
#include "SConfig.h"
#define ASC_LEN				4
#define ACS_FRAME_INDEX		0
#define ACS_PLAYCOUNT		1
#define ACS_RUNTIME			2
#define ACS_MAXTIME			3
#define  SHAPE_TYPE_N 0//多边形
#define  SHAPE_TYPE_CIRCLE 1//物理形状--圆形
#define  SHAPE_TYPE_RECT 2//矩形
//点击事件
typedef void (CCObject::*ANI_OverEvent)(CCObject*);
#define overeventselector(_SELECTOR) (ANI_OverEvent)(&_SELECTOR)
class XFrame;
class XAnimation: public CCNodeRGBA,public CCTargetedTouchDelegate
{
public:
	XAnimation(void);
	~XAnimation(void);
	static XAnimation* create(XAnimation* ani);
public :
	CCSpriteBatchNode* roleNode;
	bool canPointOthers;//是否可以点击其他动画
	int childOrder;
	bool showBone;//显示骨骼
	bool touchPressed;//触摸按下
	bool infoIsChanging;//正在改变信息

	int curTime;// 当前播放时间
	int delayTime;//延迟帧数
	bool runOver;
	bool fillAlpha;//绘制半透明图
	void setBatchNode(char* pngFile);
	void initBaseBySprite();
	void removeAFrame(int frameIndex);//移除一帧
	void setFrameCount(int count);
	void setFrameInfo(int data[],int len);
	void setSkinCountForFrame(int frameIndex,int skinCount);
	void addSkinToFrame(int frameIndex,float skinInfo[]);
	void setTimeNodes(int frameIndex,int skinIndex,int count,float data[],int colordata[]);
	void updateFrame(int frameIndex,int skinIndex,float skinInfo[]);
	void playFrame(int frameIndex);
	bool updateAnimation(int timeIndex);
	void updateTimeNodeInfo(int fpIndex, int skinIndex,int timeNodeIndex,float data[],int colordata[]);
	CCSpriteFrame* getASpriteFrame(int imgID,int moduleID);
	void resetShowCurFrame();
	CCRect rect();
	void selSkinByRect(float x,float y,float w,float h);
	void setParentId(int childSkinIndex,int parentSkinIndex);
	void msetSkinRotation(int frameID,int skinID,float rvalue);
	int getCurSelSkinIndex();//获得当前选中皮肤的索引
	bool isActionOver();
	void mouseMove(float x,float y);
	bool containTouchPoint( cocos2d::CCTouch* touch);
	virtual bool ccTouchBegan( cocos2d::CCTouch *touch , cocos2d::CCEvent *event);
	virtual void ccTouchMoved( cocos2d::CCTouch *touch , cocos2d::CCEvent *event);
	virtual void ccTouchEnded( cocos2d::CCTouch *touch , cocos2d::CCEvent *event);
	bool touchBegan(float x,float y,bool ctraPressed);
	void touchMoved(float x,float y);
	void touchClick(float x,float y,bool ctraPressed);//鼠标点击 ctrl键是否按下
	void touchEnded(float x,float y);
	void play();
	void start();
	void removeMySelf();
	void setRemoveAtOver();
	void draw(void);
	void reset();
	void setDelayTime(int dt){
		delayTime = dt;
	};
	void setXY(int x,int y)
	{
		setPosition(ccp(x,y));
	}
	void setStartFP(int sfp)
	{
		asc[ACS_RUNTIME] = sfp;
	}
	//virtual void draw(void);
public:
	array1(XFrame*) frames;//所有的帧
	array1(int)asc; 
	array1(short)		physics;//物理属性
	array3(float) polygonShapes;//物理形状
	array1(cbyte) shapeType;//类型
	array1(float) shapeRadius;//半径
	array2(float) shapeSize;//矩形区域
	int flagId;
	cbyte isRecyle;
	cbyte Recycle_end;//完成后循环
	int recycle_end_startFP;//完成后循环帧起点
	int recycle_end_endFP;//完成后循环帧结束点
	int recycle_end_count;//循环次数 -1 无限循环
	bool recycleFP2FP;//循环某帧到某帧
	bool recycleStop;
	int recycleCount;//循环次数
	int frameCount;
	int nodeID;
	bool removedAtOver;//播放完后删除
	static CCDictionary* testure_animation;

};

#endif