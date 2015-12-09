#ifndef __x_XFRAME__
#define __x_XFRAME__
#include "SConfig.h"
#include "XSkin.h"


#define OP_STATE_NONE  0
#define  OP_STATE_MOVE 1//移动图元

#define FP_INFO_LEN			4
#define ANI_PHYSICS_LEN		5
#define BOX_LEN				5
#define AREA_LEN			4



#define BOX_ATT 0//攻击框
#define BOX_COL 1//碰撞框
#define BOX_SPARE1 2//备用框1
#define BOX_SPARE2 3//备用框2
#define BOX_SPARE3 4//备用框3
#define BOX_SPARE4 5//备用框4

class XAnimation;
class XFrame
{
public:
	XFrame(void);
	~XFrame(void);
public:
	int touchFlagX;//鼠标移动标示。用于缩放处理 1表示正 -1 表示镜像缩放
	int touchFlagY;//鼠标移动标示。用于缩放处理 1表示正 -1 表示镜像缩放
	int opState;
	int playCount;//播放次数
	int runnedCount;//跑过的次数
	int maxRunTime;//当前帧的最长播放时间
	bool hasTween;//需要播放补间
	CCPoint point_startDown;//触摸按下时的点
	CCPoint point_tmp;//临时使用点
	CCPoint size_tmp;
	void setPlayCount(int count){
		playCount = count;
	}
	void setState(int state);
	void setSkinCount(int count);
	void setTimeNodes(int skinIndex,int count,float data[],int colordata[]);
	void setParentId(int childSkinIndex,int parentSkinIndex);
	bool updateFrame(CCNode*node,int time,bool showBone);
	void updateTimeNodeInfo( int skinIndex,int timeNodeIndex,float data[],int colordata[]);
	void mouseMove(float x,float y);
	bool touchBegan(float x,float y,bool ctraPressed);
	void touchMoved(float x,float y);
	void touchClick(float x,float y,bool ctraPressed);//鼠标点击 ctrl键是否按下
	void touchEnded(float x,float y);
	void selSkinByRect(float x,float y,float w,float h);

	void setLocation_beforeBoned(int skindex,float x,float y);
	bool skinBeselected(float x,float y);
	bool mouseInPoint(float px,float aLocation);
	void setTouchFlag(XSkin* skin);
	void reset();
	void resetOrder(int order[],int len);

	CCPoint s_getLocation(int skinIndex);
	array1(int)selectedSkins;//选中的精灵
	int getCurSelSkinIndex();//获得当前选中皮肤的索引
	float getDegreeForTwoPoint(float px1, float py1, float px2, float py2);
public:
	
	array1(int)  skinsorder;//更新顺序(先父节点后子节点)
	array1(XSkin*)skins;//所有精灵
	array2(short)		boxs;//框体信息
	array1(short)		area;//每一帧区域 x y right bottom
	int			keyFrame;//关键帧
	int	fpCount;//每一帧播放的次数
	int		fpSpare;//每一帧备用信息
	int	fpHurt;//每一帧受伤状态
	int		fpOffset;//每一帧位移
	int		fpPause;//每一帧僵直
	int		fpMusic;//每一帧音效

};

#endif