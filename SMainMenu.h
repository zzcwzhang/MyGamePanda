#ifndef __SMAINMENU___
#define  __SMAINMENU___
#define SCALE_POINT 0.72//点击的时候
#define SCALE_START 0.5//起始值
#define SCALE_PUTTED 1.0//展开
#include "SConfig.h"

#define UISTATE_MENU		0// 封面
#define UISTATE_SELECTION	1// 选关

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
	void initMainMenu();	// 初始化主菜单
	void initSelection();	// 初始化选关界面
	void initSetting();		// 初始化设置界面
	void initHelp();		// 初始化帮助界面
	void initProcessFrame(); // 过场界面
	void removeCurFrames();	// 移除当前界面
	void loadSceneAnimation(); // 加载场景动画
	void removeSceneAnimation(); // 移除场景动画

	// 当前位置是否可触摸
	bool canBeTouched(int x, int y);
	// 选关界面整体移动
	void selectTouchMoveTo(int x, int y);
	// 设置按钮不可见
	void setButtonVisable(int frameID,int startBlock, int startID, int endID, bool isVisable);
	// 封面切换弹出按钮
	void fengmian_ChangButton();

public:
	// 按钮点击事件
	void fenmain_PopMenu_click(CCObject*sender);	// 弹出菜单
	void fenmain_PushMenu_click(CCObject*sender);	// 收起菜单
	void anniu_Quit_click(CCObject*sender);			// 退出
	void anniu_Help_click(CCObject*sender);			// 帮助
	void anniu_Setting_click(CCObject*sender);	
	// 设置

	void xuanguan_BackMenu_click(CCObject*sender);	// 选关界面返回按钮
	void xuanguan_Select_click(CCObject*sender, int handID);	// 选关界面进入关卡按钮
	void xuanguan1_Select_click(CCObject*sender, int handID);	// 选关界面进入关卡按钮
	void xuanguan2_Select_click(CCObject*sender, int handID);	// 选关界面进入关卡按钮
	void xuanguan3_Select_click(CCObject*sender, int handID);	// 选关界面进入关卡按钮
	//void xuanguan4_Select_click(CCObject*sender, int handID);	// 选关界面进入关卡按钮
	//void xuanguan5_Select_click(CCObject*sender, int handID);	// 选关界面进入关卡按钮
	//void xuanguan6_Select_click(CCObject*sender, int handID);	// 选关界面进入关卡按钮
	//void xuanguan7_Select_click(CCObject*sender, int handID);	// 选关界面进入关卡按钮

	void shezhi_Close_click(CCObject*sender);		// 设置界面关闭
	void shezhi_Music_checked(CCObject*sender,bool checked);	// 设置界面音乐开关
	void shezhi_Effect_checked(CCObject*sender,bool checked);	// 设置界面音效开关

	void help_Close_click(CCObject*sender);			// 帮助界面关闭

public:
	int selectFramesID[4]; // 用于存放选关界面ID
	CCPoint getFramePosion(int frameID); // 得到界面的当前位置
	float offX; // X方向偏移值
	float posX; // 记录每次点击的位置
	bool isTouched; // 本次触摸是否结束
	int preUiState;		// 前一个UI状态
	int uiState;		// UI界面状态（0为封面，1为选关界面
	int changeDelay;	// 按钮切换延时
	bool bBeClicked;	// 按钮是否可点击
	int processDelay;	// 过场动画延时
	bool bToSelection;	// 是否可到选关界面
	bool bTouchMoving;	// 是否正在快速滑动选关界面
	void setUIState(int state)
	{
		preUiState = uiState;
		uiState = state; 
	}	// 设置UI界面状态
};
#define m_mainmenu SMainMenu::shareMainMenu()
#endif