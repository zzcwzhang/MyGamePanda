#ifndef __SGAMESTATE___
#define  __SGAMESTATE___
#include "SConfig.h"
#include "SResManager.h"
#include "SStartPage.h"
#include "ZGame.h"

#define GST_MAINMENU 1//主菜单
#define GST_GAMEING 2//游戏状态
#define GST_SSTARTPAGE 3//游戏初始状态
#define SCREEN_W 720
#define SCREEN_W_HALF 360
#define SCREEN_H_HALF 640
#define  SMS_KEY_GOLD_1 1//1000金币
#define  SMS_KEY_GOLD_2 2//30000金币
#define  SMS_KEY_GOLD_3 3//30000金币

#define BGM_START  "music/startBGM.ogg" //背景音
#define BGM_F  "music/bgm.ogg" //背景音
#define  BTN_MUSIC_OK 0
#define  BTN_MUSIC_CANCEL 1
#define  MUSIC_GMONEY 2//金币
#define MAX_LEVEL 40// 最多关卡数

#define LEVEL_PROCESS 0// 关卡进度
#define LEVEL_BULLETCOUNT 1// 当前关卡子弹数
#define LEVEL_COINCOUNT 2// 金钱数
#define LEVEL_STAR 3// 关卡星级
#define LEVELINFO_LEN 4// 关卡属性长度
#define LEVEL_COUNT 40// 关卡数目

// 关卡统计信息
#define LEVELTOTAL_LEN 4// 统计信息长度
#define LEVELTOTAL_USEBUTTLECOUNT 0//使用子弹数
#define LEVELTOTAL_ARMORTOTAL 1// 使用护甲道具数目
#define LEVELTOTAL_THROUGHTOTAL 2// 使用穿墙弹次数
#define LEVELTOTAL_SHOTTOTAL 3// 使用散弹次数


// 音效路径
#define EFF_BUTTONCLICK ("music/anniu.ogg")// 点击按钮
#define EFF_HERODEAD ("music/zhujuesiwang.ogg")// 主角死亡
#define EFF_ENEMYDEAD ("music/guaiwusiwang.ogg")// 怪物死亡
#define EFF_BOXBREAK ("music/muxiangbaozha.ogg")// 木箱粉碎
#define EFF_BOMBEXPLORE ("music/baozha.ogg")// 炸弹爆炸
#define EFF_BUTTLESHOOT ("music/fashe.ogg")// 子弹发射
#define EFF_BUTTLEREBOUND ("music/zaidanfantan.ogg")// 子弹反弹	
#define EFF_ARMOR ("music/dunpai.ogg")// 英雄召唤护盾

// 背景音乐路径
#define BGM_ICE ("music/bingchangjing.ogg")// 冰场景
#define BGM_MAINMENU ("music/fengmian.ogg")// 封面
#define BGM_GRAVEYARD ("music/mudizise.ogg")// 墓地紫色场景
#define BGM_FOREST ("music/senlinshamo.ogg")// 森林沙漠场景
#define BGM_SELECTION ("music/xuanguan.ogg")// 选关界面

// 监测事件
#define EVENT_TO_LEVEL			("toLevel")// 进入关卡
#define EVENT_RESTART_GAMING	("restartFromGaming")// 游戏界面重新开始
#define EVENT_RESTART_SUCCESS	("restartFromSuccess")// 统计界面重新开始
#define EVENT_RESTART_FAILED	("restartFromFailed")// 失败界面重新开始
#define EVENT_NEXT_SUCCESS		("toNextFromSuccess")// 统计界面进入一下关
#define EVENT_ARMOR				("useArmor")// 点击使用护甲
#define EVENT_THROUGH			("useThroughButtle")// 点击使用穿墙弹
#define EVENT_SHOT				("useShotButtle")// 使用散弹
#define EVENT_LEVEL_SUCCESSED	("levelSuccessed")// 关卡成功

// 教学屏幕锁定方式
#define TEACH_LOCKTYPE_NO	-1// 屏幕不锁定
#define TEACH_LOCKTYPE_RECT	0// 只锁定矩形区域内的部分
#define TEACH_LOCKTYPE_ALL	1// 全部锁定
// 教学步骤切换方式
#define TEACH_STEPTYPE_TOUCH -1// 点击进入下一步教学
#define TEACH_STEPTYPE_OTHER 0// 其他事件触发
#define TEACH_STEPTYPE_END 1// 本关教学结束
#define TEACH_STEPTYPE_ALLEND 2// 全部结束

//主菜单底 游戏底 设置  胜利 失败 商店 都做SUI处理
using namespace cocos2d;
class GameState : public cocos2d::CCLayer
{
public:
	// 监测事件类型
	enum {
		event_toLevel = 0,
		event_restartFromGaming,
		event_restartFromSuccess,
		event_restartFromFailed,
		event_toNextFromSuccess,
		event_useArmor,
		event_useThrough,
		event_useShot,
		event_levelSuccessed
	};

	// 添加监测事件
	void addTalkingEvent(int id);

	// 为某个动作添加延时
	void setDelayForAction(float dt, CCCallFunc* callfunc);

public:
	static GameState* gmstate;
	static SResManager* m_resManager;
	static ZGame* m_gameLayer;
	SStartPage* startPage;
	int getMoneyCount;//免费获得金币次数
	int delayt;
	int curState;
	int preState;
	int nextState;
	float	curScreenW;//当前屏幕分辨率
	float	curScreenH;
	int shopIndex;
	bool showShop;
	bool loadMusic;
	bool firstInMainMenu;//第一次进入主菜单
	int screenPIXW;
	int screenPIXH;
	int curLevel;			// 当前关卡
	array1(int) levelInfo;	// 关卡信息
	array1(int) levelStars; // 所有关卡的星级
	array1(int)	levelTotalInfo; // 关卡统计信息

public:
	~GameState();
	virtual bool init();  
	static void pureGS();
	static GameState* sharedGS();
	static SResManager*sharedRes();
	static ZGame* sharedGame();
	CREATE_FUNC(GameState);
	static cocos2d::CCScene* scene();
	void initLevelInfo(); // 初始化关卡信息
	void initLevelStar(); // 初始化关卡星级
	void initLevelTotal(); // 初始化监测事件信息
	void initstaticArray();
	void update(float t);
	void setState(int newState,int nextState);
	void intoNextState(int nextState,int delayt);
	CCTexture2D* getATexture(float tid);
	void loadHeroInfo();
	void saveHeroInfo();
	void loadGameingInfo();
	void seveGameIngInfo(int beishu,unsigned long long dizhu,bool isLandor);
	void initTasks();
	bool chackTask();
	void stopBGM(); // 停止播放背景音乐
	void playBGM(const char* path); // 播放BGM
	void playEffMusic(const char* path);
	void playButtonMusic(int type);
	void initMusic();//加载音效
	void sendMessageResult(int type,int code);
public:
	//virtual void registerWithTouchDispatcher();  
	virtual void ccTouchesBegan(CCSet *pTouch, CCEvent *pEvent);  
	virtual void ccTouchesMoved(CCSet *pTouch, CCEvent *pEvent);  
	virtual void ccTouchesEnded(CCSet *pTouch, CCEvent *pEvent);  
public:
	void music_ValueChanged(CCObject*sender,float svalue);
	void music_effect_ValueChanged(CCObject*sender,float svalue);
	void setMusic_click(CCObject*sender);
	void setMusic_back_click(CCObject*sender);
	void setGoodsCount();
	void shop_show();
	void shop__back_click(CCObject*sender);
	void shop__goods1_click(CCObject*sender);
	void shop__goods2_click(CCObject*sender);
	void shop__goods3_click(CCObject*sender);
	void shop__goods4_click(CCObject*sender);
	void shop__goods5_click(CCObject*sender);
	void shop__goods6_click(CCObject*sender);

	void tip_buyGoods_OK_click(CCObject*sender);
	void tip_buyGoods_CANCEL_click(CCObject*sender);
	void taskpage_show();
	void task__back_click(CCObject*sender);

	void noMoney_show();
	void noMoney_back_click(CCObject*sender);

	void loginReward_show();
	void loginReward_get_click(CCObject*sender);
	void goodsNotEnough(int type);//道具不足

	void cb_shackChacked(CCObject*sender,bool checked);
	void cb_sortChecked(CCObject*sender,bool checked);
public://需要保存的项目
	float bgmVolume;//背景音量
	float effVolume;//音效
	bool shacked;//震动
	bool sortByLeft;//从左到右排序
	long preTaskTime;//上一次任务获取时间
	array2(int)tasks;//当前任务 0 任务ID 1 是否完成 0 否 1 是
	int winCount;//胜利次数
	int failedCount;//失败次数
	int conWinCount;//连胜次数
	int conFailedCount;//连败次数
	int putongSG;//普通场玩的次数
	int hjcSG;//黄金场玩的次数
	int conLandWinCount;//当地主连胜次数
	int hjcWinCount;//黄金场胜利次数
	int TASK_BOMB;//炸弹沉底获胜
	int TASK_KINGB;//火箭沉底获胜
	int TASK_THREE ;//单张“3”沉底获胜
	int TASK_128_LANDWIN;//128倍地主胜利
	int TASK_128_NMWIN ;//128倍农民胜利
	int TASK_ONEHAND;//一手秒胜
	int TASK_NCCARD_FAILED;//零出牌失败
	int TASK_2BOMBWIN;//2炸弹胜利
	int TASK_3BOMBWIN;//3炸弹胜利
	array1(int) loginReward;//登录奖励
    CCDictionary *taskstrings;
	int rewIndex;
	int sceneIndex;
	int buyGoodsType;//购买物品类型
	
public:
	int teachProcess; // 当前教学的关卡进度 
	int inTeachSteate;// 在教学状态(0不在 1在)
	int curTeachStep; // 当前教学进度
	int preTeachStep; // 前一个教学进度
	int curTeachFream; // 当前教学界面
	int preTeachFream; // 前一个教学界面
	int curBlockCount; // 当前教学的红框数目
	int curTouchType; // 教学过程中的屏幕锁定类型
	CCDictionary* teachDis; // 教学信息

	bool canTouchdPos(int x, int y);
	bool isInTeaching() // 是否在教学中
	{
		return curLevel >= teachProcess && inTeachSteate != 0 && curLevel < 3; 
	}

	void initTeaching();  // 初始化教学
	void loadTeachInfo(); // 加载教学信息

	void intoNextTeachStep(float dt = 0); // 延迟一段时间进入下一个教学步骤
	void setTeachStep(int step); // 设置教学步骤
	void intoCurTeachStep();

	void removeCurTeachFream(float dt); // 延迟一段时间后删除教学界面
	void removeCurTeachFream(); // 删除当前教学界面
	void removePreTeachFream(float dt); // 延迟一段时间后删除前一个教学界面
	void removePreTeachFream(); // 删除前一个教学界面
};
#define m_gamestate GameState::sharedGS()
#define m_gameRes GameState::sharedRes()
#define m_game GameState::sharedGame()
#endif