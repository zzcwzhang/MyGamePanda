#ifndef __x_XFRAME__
#define __x_XFRAME__
#include "SConfig.h"
#include "XSkin.h"


#define OP_STATE_NONE  0
#define  OP_STATE_MOVE 1//�ƶ�ͼԪ

#define FP_INFO_LEN			4
#define ANI_PHYSICS_LEN		5
#define BOX_LEN				5
#define AREA_LEN			4



#define BOX_ATT 0//������
#define BOX_COL 1//��ײ��
#define BOX_SPARE1 2//���ÿ�1
#define BOX_SPARE2 3//���ÿ�2
#define BOX_SPARE3 4//���ÿ�3
#define BOX_SPARE4 5//���ÿ�4

class XAnimation;
class XFrame
{
public:
	XFrame(void);
	~XFrame(void);
public:
	int touchFlagX;//����ƶ���ʾ���������Ŵ��� 1��ʾ�� -1 ��ʾ��������
	int touchFlagY;//����ƶ���ʾ���������Ŵ��� 1��ʾ�� -1 ��ʾ��������
	int opState;
	int playCount;//���Ŵ���
	int runnedCount;//�ܹ��Ĵ���
	int maxRunTime;//��ǰ֡�������ʱ��
	bool hasTween;//��Ҫ���Ų���
	CCPoint point_startDown;//��������ʱ�ĵ�
	CCPoint point_tmp;//��ʱʹ�õ�
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
	void touchClick(float x,float y,bool ctraPressed);//����� ctrl���Ƿ���
	void touchEnded(float x,float y);
	void selSkinByRect(float x,float y,float w,float h);

	void setLocation_beforeBoned(int skindex,float x,float y);
	bool skinBeselected(float x,float y);
	bool mouseInPoint(float px,float aLocation);
	void setTouchFlag(XSkin* skin);
	void reset();
	void resetOrder(int order[],int len);

	CCPoint s_getLocation(int skinIndex);
	array1(int)selectedSkins;//ѡ�еľ���
	int getCurSelSkinIndex();//��õ�ǰѡ��Ƥ��������
	float getDegreeForTwoPoint(float px1, float py1, float px2, float py2);
public:
	
	array1(int)  skinsorder;//����˳��(�ȸ��ڵ���ӽڵ�)
	array1(XSkin*)skins;//���о���
	array2(short)		boxs;//������Ϣ
	array1(short)		area;//ÿһ֡���� x y right bottom
	int			keyFrame;//�ؼ�֡
	int	fpCount;//ÿһ֡���ŵĴ���
	int		fpSpare;//ÿһ֡������Ϣ
	int	fpHurt;//ÿһ֡����״̬
	int		fpOffset;//ÿһ֡λ��
	int		fpPause;//ÿһ֡��ֱ
	int		fpMusic;//ÿһ֡��Ч

};

#endif