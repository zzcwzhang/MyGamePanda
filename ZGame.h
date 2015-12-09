#ifndef _X_ZGAME__
#define _X_ZGAME__
#include "SConfig.h"

#include "Map/MapList.h"
#include "Atkable/Demon.h"
#include "Atkable/Building.h"
#include "Tower/Shooter.h"
#include "Tower/Marker.h"
#include "Map/BatteryChoice.h"

NAMESPACE_ZJG_BEGIN

#define second(a) a*FPS_RATE
#define m_choose ZGame::ShareBC()
#define m_upgrade ZGame::ShareUG()

#define G_ST_NULL   -1      //初始状态;
#define G_ST_LOADING 0      //资源加载;
#define G_ST_GAMEING 1		//游戏中;
#define G_ST_CHOOSETOWER 2  //选择炮塔菜单;
#define G_ST_UPGRADE 3		//选择炮塔菜单;
#define G_ST_MENU 4			//游戏控制菜单;

class ZHero;
USING_NS_CC;
class ZGame:public cocos2d::CCLayer
{
public:
	ZGame(void);
	~ZGame(void);
public:
	//游戏状态;
	int gameState;
	int nextState;
	int delayTime;
	int preGameState;
	int haveUI;

	//关卡;
	int coin;
	int curLv;
	int curWave;
	MapList* m_map;
	array1(int) towerAttackPower;

	//刷怪;
	int t_DemonRushClock;
	void clockStep();
	bool isDoubleSpeed;
	bool isPause;

	int cellNum;

	static BatteryChoice* m_towerChoose;
	static BatteryUpgrade* m_towerUpgrade;
public:
	void GameInit();
	void dataRead();
	void initUI();
	void initMap();
	void destory();
	void update(float t);
	void GameStep();
	void playBGM(); // 根据关卡播放背景音乐;
	void intoNextState(int state, int dt);
	void setState(int state);
public:
	void touchBegan(float x,float y);
	void touchMoved(float x,float y);
	void touchEnded(float x,float y);
	bool touchAtkable(float x,float y);

public: 
	//回调;
	void backtoXuanguan1(CCObject* obj);
	void reGame(CCObject* obj);
	void SpeedXX(CCObject* obj);
	void PauseGame(CCObject* obj);
	void ReStart(CCObject* obj);
	void Resume( CCObject* obj );

	void removeCurFrames();
	void AllTowerAutoShoot();

public:
	//塔菜单;
	static BatteryChoice* ShareBC();
	static BatteryUpgrade* ShareUG();
	bool pay( int price );
	
};
NAMESPACE_ZJG_END
#endif