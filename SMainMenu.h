#ifndef __SMAINMENU___
#define  __SMAINMENU___
#define SCALE_POINT 0.72//�����ʱ��
#define SCALE_START 0.5//��ʼֵ
#define SCALE_PUTTED 1.0//չ��
#include "SConfig.h"

#define UISTATE_MENU		0// ����
#define UISTATE_SELECTION	1// ѡ��

class SMainMenu:public cocos2d::CCLayer
{
public:
	SMainMenu();
	~SMainMenu();
	static SMainMenu* shareMainMenu();
	static SMainMenu* game_mainmenu;
	void initRes();
	void update();
	void touchBegin(float x,float y);
	void touchMoved(float x,float y);
	void touchEnded(float x,float y);
	void intoGame(int sceneType);
	void initMainMenu();	// ��ʼ�����˵�
	void initSelection();	// ��ʼ��ѡ�ؽ���
	void initSetting();		// ��ʼ�����ý���
	void initHelp();		// ��ʼ����������
	void initProcessFrame(); // ��������
	void removeCurFrames();	// �Ƴ���ǰ����
	void loadSceneAnimation(); // ���س�������
	void removeSceneAnimation(); // �Ƴ���������

	// ��ǰλ���Ƿ�ɴ���
	bool canBeTouched(int x, int y);
	// ѡ�ؽ��������ƶ�
	void selectTouchMoveTo(int x, int y);
	// ���ð�ť���ɼ�
	void setButtonVisable(int frameID,int startBlock, int startID, int endID, bool isVisable);
	// �����л�������ť
	void fengmian_ChangButton();

public:
	// ��ť����¼�
	void fenmain_PopMenu_click(CCObject*sender);	// �����˵�
	void fenmain_PushMenu_click(CCObject*sender);	// ����˵�
	void anniu_Quit_click(CCObject*sender);			// �˳�
	void anniu_Help_click(CCObject*sender);			// ����
	void anniu_Setting_click(CCObject*sender);	
	// ����

	void xuanguan_BackMenu_click(CCObject*sender);	// ѡ�ؽ��淵�ذ�ť
	void xuanguan_Select_click(CCObject*sender, int handID);	// ѡ�ؽ������ؿ���ť
	void xuanguan1_Select_click(CCObject*sender, int handID);	// ѡ�ؽ������ؿ���ť
	void xuanguan2_Select_click(CCObject*sender, int handID);	// ѡ�ؽ������ؿ���ť
	void xuanguan3_Select_click(CCObject*sender, int handID);	// ѡ�ؽ������ؿ���ť
	//void xuanguan4_Select_click(CCObject*sender, int handID);	// ѡ�ؽ������ؿ���ť
	//void xuanguan5_Select_click(CCObject*sender, int handID);	// ѡ�ؽ������ؿ���ť
	//void xuanguan6_Select_click(CCObject*sender, int handID);	// ѡ�ؽ������ؿ���ť
	//void xuanguan7_Select_click(CCObject*sender, int handID);	// ѡ�ؽ������ؿ���ť

	void shezhi_Close_click(CCObject*sender);		// ���ý���ر�
	void shezhi_Music_checked(CCObject*sender,bool checked);	// ���ý������ֿ���
	void shezhi_Effect_checked(CCObject*sender,bool checked);	// ���ý�����Ч����

	void help_Close_click(CCObject*sender);			// ��������ر�

public:
	int selectFramesID[4]; // ���ڴ��ѡ�ؽ���ID
	CCPoint getFramePosion(int frameID); // �õ�����ĵ�ǰλ��
	float offX; // X����ƫ��ֵ
	float posX; // ��¼ÿ�ε����λ��
	bool isTouched; // ���δ����Ƿ����
	int preUiState;		// ǰһ��UI״̬
	int uiState;		// UI����״̬��0Ϊ���棬1Ϊѡ�ؽ���
	int changeDelay;	// ��ť�л���ʱ
	bool bBeClicked;	// ��ť�Ƿ�ɵ��
	int processDelay;	// ����������ʱ
	bool bToSelection;	// �Ƿ�ɵ�ѡ�ؽ���
	bool bTouchMoving;	// �Ƿ����ڿ��ٻ���ѡ�ؽ���
	void setUIState(int state)
	{
		preUiState = uiState;
		uiState = state; 
	}	// ����UI����״̬
};
#define m_mainmenu SMainMenu::shareMainMenu()
#endif