#ifndef __x_XANIMATION__
#define __x_XANIMATION__
#include "SConfig.h"
#define ASC_LEN				4
#define ACS_FRAME_INDEX		0
#define ACS_PLAYCOUNT		1
#define ACS_RUNTIME			2
#define ACS_MAXTIME			3
#define  SHAPE_TYPE_N 0//�����
#define  SHAPE_TYPE_CIRCLE 1//������״--Բ��
#define  SHAPE_TYPE_RECT 2//����
//����¼�
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
	bool canPointOthers;//�Ƿ���Ե����������
	int childOrder;
	bool showBone;//��ʾ����
	bool touchPressed;//��������
	bool infoIsChanging;//���ڸı���Ϣ

	int curTime;// ��ǰ����ʱ��
	int delayTime;//�ӳ�֡��
	bool runOver;
	bool fillAlpha;//���ư�͸��ͼ
	void setBatchNode(char* pngFile);
	void initBaseBySprite();
	void removeAFrame(int frameIndex);//�Ƴ�һ֡
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
	int getCurSelSkinIndex();//��õ�ǰѡ��Ƥ��������
	bool isActionOver();
	void mouseMove(float x,float y);
	bool containTouchPoint( cocos2d::CCTouch* touch);
	virtual bool ccTouchBegan( cocos2d::CCTouch *touch , cocos2d::CCEvent *event);
	virtual void ccTouchMoved( cocos2d::CCTouch *touch , cocos2d::CCEvent *event);
	virtual void ccTouchEnded( cocos2d::CCTouch *touch , cocos2d::CCEvent *event);
	bool touchBegan(float x,float y,bool ctraPressed);
	void touchMoved(float x,float y);
	void touchClick(float x,float y,bool ctraPressed);//����� ctrl���Ƿ���
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
	array1(XFrame*) frames;//���е�֡
	array1(int)asc; 
	array1(short)		physics;//��������
	array3(float) polygonShapes;//������״
	array1(cbyte) shapeType;//����
	array1(float) shapeRadius;//�뾶
	array2(float) shapeSize;//��������
	int flagId;
	cbyte isRecyle;
	cbyte Recycle_end;//��ɺ�ѭ��
	int recycle_end_startFP;//��ɺ�ѭ��֡���
	int recycle_end_endFP;//��ɺ�ѭ��֡������
	int recycle_end_count;//ѭ������ -1 ����ѭ��
	bool recycleFP2FP;//ѭ��ĳ֡��ĳ֡
	bool recycleStop;
	int recycleCount;//ѭ������
	int frameCount;
	int nodeID;
	bool removedAtOver;//�������ɾ��
	static CCDictionary* testure_animation;

};

#endif