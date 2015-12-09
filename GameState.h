#ifndef __SGAMESTATE___
#define  __SGAMESTATE___
#include "SConfig.h"
#include "SResManager.h"
#include "SStartPage.h"
#include "ZGame.h"

#define GST_MAINMENU 1//���˵�
#define GST_GAMEING 2//��Ϸ״̬
#define GST_SSTARTPAGE 3//��Ϸ��ʼ״̬
#define SCREEN_W 720
#define SCREEN_W_HALF 360
#define SCREEN_H_HALF 640
#define  SMS_KEY_GOLD_1 1//1000���
#define  SMS_KEY_GOLD_2 2//30000���
#define  SMS_KEY_GOLD_3 3//30000���

#define BGM_START  "music/startBGM.ogg" //������
#define BGM_F  "music/bgm.ogg" //������
#define  BTN_MUSIC_OK 0
#define  BTN_MUSIC_CANCEL 1
#define  MUSIC_GMONEY 2//���
#define MAX_LEVEL 40// ���ؿ���

#define LEVEL_PROCESS 0// �ؿ�����
#define LEVEL_BULLETCOUNT 1// ��ǰ�ؿ��ӵ���
#define LEVEL_COINCOUNT 2// ��Ǯ��
#define LEVEL_STAR 3// �ؿ��Ǽ�
#define LEVELINFO_LEN 4// �ؿ����Գ���
#define LEVEL_COUNT 40// �ؿ���Ŀ

// �ؿ�ͳ����Ϣ
#define LEVELTOTAL_LEN 4// ͳ����Ϣ����
#define LEVELTOTAL_USEBUTTLECOUNT 0//ʹ���ӵ���
#define LEVELTOTAL_ARMORTOTAL 1// ʹ�û��׵�����Ŀ
#define LEVELTOTAL_THROUGHTOTAL 2// ʹ�ô�ǽ������
#define LEVELTOTAL_SHOTTOTAL 3// ʹ��ɢ������


// ��Ч·��
#define EFF_BUTTONCLICK ("music/anniu.ogg")// �����ť
#define EFF_HERODEAD ("music/zhujuesiwang.ogg")// ��������
#define EFF_ENEMYDEAD ("music/guaiwusiwang.ogg")// ��������
#define EFF_BOXBREAK ("music/muxiangbaozha.ogg")// ľ�����
#define EFF_BOMBEXPLORE ("music/baozha.ogg")// ը����ը
#define EFF_BUTTLESHOOT ("music/fashe.ogg")// �ӵ�����
#define EFF_BUTTLEREBOUND ("music/zaidanfantan.ogg")// �ӵ�����	
#define EFF_ARMOR ("music/dunpai.ogg")// Ӣ���ٻ�����

// ��������·��
#define BGM_ICE ("music/bingchangjing.ogg")// ������
#define BGM_MAINMENU ("music/fengmian.ogg")// ����
#define BGM_GRAVEYARD ("music/mudizise.ogg")// Ĺ����ɫ����
#define BGM_FOREST ("music/senlinshamo.ogg")// ɭ��ɳĮ����
#define BGM_SELECTION ("music/xuanguan.ogg")// ѡ�ؽ���

// ����¼�
#define EVENT_TO_LEVEL			("toLevel")// ����ؿ�
#define EVENT_RESTART_GAMING	("restartFromGaming")// ��Ϸ�������¿�ʼ
#define EVENT_RESTART_SUCCESS	("restartFromSuccess")// ͳ�ƽ������¿�ʼ
#define EVENT_RESTART_FAILED	("restartFromFailed")// ʧ�ܽ������¿�ʼ
#define EVENT_NEXT_SUCCESS		("toNextFromSuccess")// ͳ�ƽ������һ�¹�
#define EVENT_ARMOR				("useArmor")// ���ʹ�û���
#define EVENT_THROUGH			("useThroughButtle")// ���ʹ�ô�ǽ��
#define EVENT_SHOT				("useShotButtle")// ʹ��ɢ��
#define EVENT_LEVEL_SUCCESSED	("levelSuccessed")// �ؿ��ɹ�

// ��ѧ��Ļ������ʽ
#define TEACH_LOCKTYPE_NO	-1// ��Ļ������
#define TEACH_LOCKTYPE_RECT	0// ֻ�������������ڵĲ���
#define TEACH_LOCKTYPE_ALL	1// ȫ������
// ��ѧ�����л���ʽ
#define TEACH_STEPTYPE_TOUCH -1// ���������һ����ѧ
#define TEACH_STEPTYPE_OTHER 0// �����¼�����
#define TEACH_STEPTYPE_END 1// ���ؽ�ѧ����
#define TEACH_STEPTYPE_ALLEND 2// ȫ������

//���˵��� ��Ϸ�� ����  ʤ�� ʧ�� �̵� ����SUI����
using namespace cocos2d;
class GameState : public cocos2d::CCLayer
{
public:
	// ����¼�����
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

	// ��Ӽ���¼�
	void addTalkingEvent(int id);

	// Ϊĳ�����������ʱ
	void setDelayForAction(float dt, CCCallFunc* callfunc);

public:
	static GameState* gmstate;
	static SResManager* m_resManager;
	static ZGame* m_gameLayer;
	SStartPage* startPage;
	int getMoneyCount;//��ѻ�ý�Ҵ���
	int delayt;
	int curState;
	int preState;
	int nextState;
	float	curScreenW;//��ǰ��Ļ�ֱ���
	float	curScreenH;
	int shopIndex;
	bool showShop;
	bool loadMusic;
	bool firstInMainMenu;//��һ�ν������˵�
	int screenPIXW;
	int screenPIXH;
	int curLevel;			// ��ǰ�ؿ�
	array1(int) levelInfo;	// �ؿ���Ϣ
	array1(int) levelStars; // ���йؿ����Ǽ�
	array1(int)	levelTotalInfo; // �ؿ�ͳ����Ϣ

public:
	~GameState();
	virtual bool init();  
	static void pureGS();
	static GameState* sharedGS();
	static SResManager*sharedRes();
	static ZGame* sharedGame();
	CREATE_FUNC(GameState);
	static cocos2d::CCScene* scene();
	void initLevelInfo(); // ��ʼ���ؿ���Ϣ
	void initLevelStar(); // ��ʼ���ؿ��Ǽ�
	void initLevelTotal(); // ��ʼ������¼���Ϣ
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
	void stopBGM(); // ֹͣ���ű�������
	void playBGM(const char* path); // ����BGM
	void playEffMusic(const char* path);
	void playButtonMusic(int type);
	void initMusic();//������Ч
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
	void goodsNotEnough(int type);//���߲���

	void cb_shackChacked(CCObject*sender,bool checked);
	void cb_sortChecked(CCObject*sender,bool checked);
public://��Ҫ�������Ŀ
	float bgmVolume;//��������
	float effVolume;//��Ч
	bool shacked;//��
	bool sortByLeft;//����������
	long preTaskTime;//��һ�������ȡʱ��
	array2(int)tasks;//��ǰ���� 0 ����ID 1 �Ƿ���� 0 �� 1 ��
	int winCount;//ʤ������
	int failedCount;//ʧ�ܴ���
	int conWinCount;//��ʤ����
	int conFailedCount;//���ܴ���
	int putongSG;//��ͨ����Ĵ���
	int hjcSG;//�ƽ���Ĵ���
	int conLandWinCount;//��������ʤ����
	int hjcWinCount;//�ƽ�ʤ������
	int TASK_BOMB;//ը�����׻�ʤ
	int TASK_KINGB;//������׻�ʤ
	int TASK_THREE ;//���š�3�����׻�ʤ
	int TASK_128_LANDWIN;//128������ʤ��
	int TASK_128_NMWIN ;//128��ũ��ʤ��
	int TASK_ONEHAND;//һ����ʤ
	int TASK_NCCARD_FAILED;//�����ʧ��
	int TASK_2BOMBWIN;//2ը��ʤ��
	int TASK_3BOMBWIN;//3ը��ʤ��
	array1(int) loginReward;//��¼����
    CCDictionary *taskstrings;
	int rewIndex;
	int sceneIndex;
	int buyGoodsType;//������Ʒ����
	
public:
	int teachProcess; // ��ǰ��ѧ�Ĺؿ����� 
	int inTeachSteate;// �ڽ�ѧ״̬(0���� 1��)
	int curTeachStep; // ��ǰ��ѧ����
	int preTeachStep; // ǰһ����ѧ����
	int curTeachFream; // ��ǰ��ѧ����
	int preTeachFream; // ǰһ����ѧ����
	int curBlockCount; // ��ǰ��ѧ�ĺ����Ŀ
	int curTouchType; // ��ѧ�����е���Ļ��������
	CCDictionary* teachDis; // ��ѧ��Ϣ

	bool canTouchdPos(int x, int y);
	bool isInTeaching() // �Ƿ��ڽ�ѧ��
	{
		return curLevel >= teachProcess && inTeachSteate != 0 && curLevel < 3; 
	}

	void initTeaching();  // ��ʼ����ѧ
	void loadTeachInfo(); // ���ؽ�ѧ��Ϣ

	void intoNextTeachStep(float dt = 0); // �ӳ�һ��ʱ�������һ����ѧ����
	void setTeachStep(int step); // ���ý�ѧ����
	void intoCurTeachStep();

	void removeCurTeachFream(float dt); // �ӳ�һ��ʱ���ɾ����ѧ����
	void removeCurTeachFream(); // ɾ����ǰ��ѧ����
	void removePreTeachFream(float dt); // �ӳ�һ��ʱ���ɾ��ǰһ����ѧ����
	void removePreTeachFream(); // ɾ��ǰһ����ѧ����
};
#define m_gamestate GameState::sharedGS()
#define m_gameRes GameState::sharedRes()
#define m_game GameState::sharedGame()
#endif