#pragma once
#include "cocos2d.h"
#include "ZConfig.h"
#include "GameInfo/ReadInfo.h"

class GameRun;

#define kTag_BUFFMANGER 15

#define FOREACH_ATKOBJ \
	for (int i = 0 ;i<Atkable::AtkableArray->count();i++) \
	{ \
		Atkable* obj = (Atkable*)Atkable::AtkableArray->objectAtIndex(i); 
#define FOREACH_END }


enum AtkableState
{
	AS_NORMAL =0,//正常;
	AS_GOD = 0x01<<1,//无敌;
	AS_ICE = 0x01<<2,//冰冻;
	AS_SLOW = 0x01<<3,//减速;
	AS_DIZZINESS = 0x01<<4,//眩晕;
};

enum continueHart
{
	ACH_POISON = 1,
	ACH_FIRE,
};

typedef unsigned long AT_state;



class Atkable :public cocos2d::CCNode
{
public:

	class Buff
	{
	public:
		Buff(AT_state BuffID,int time,int level)
		{
			buffID = BuffID;
			times = time;
			b_level = level;
		};

		AT_state buffID;
		int times;
		int b_level;
	};

	class ContinueHart
	{
	public:
		ContinueHart(int chID,int hart,int times)
		{
			mchID = chID;
			mpower = hart;
			mtimes = times;
			minterval = 60;
		};

		int mchID ;
		int mpower;
		int mtimes;
		int minterval;
	};

	Atkable();
	~Atkable();

	CREATE_FUNC(Atkable);

	void draw();

	//包含所有Atkable的列表;
	static cocos2d::CCArray* AtkableArray;


	//**工具**;

	//精灵中点;
	virtual cocos2d::CCPoint getMidPoint();
	//精灵包围盒;
	virtual CCRect getBox();

	//**接口**;

	void getHart(int power,int hartStyle,int hlevel = 1);

	void getBuff(AT_state id,int times, int level);

	void getContinueHart(int chID , int power,int times);


	CCSize getSPContentSize();

	virtual void Destroyed();

	//根据Y坐标自动设置层叠等级;
	void setAutoZoder(bool isForever);

protected:
	//实体精灵;
	CCSprite* msp;
	//血条;
	CCProgressTimer* progress1;

	//速度控速;
	CCScheduler *scheduler;
	CCActionManager* actionManager;
	void SpeedControl();

	//状态;
	void updateState(Buff* tbuf);
	AT_state mState;	
	std::list<Buff*> buffArray;
	
	//持续伤害;
	std::list<ContinueHart*> cHartArray;

	CC_SYNTHESIZE(int,ID,ID);
	//实体生命与上限;
	CC_SYNTHESIZE(int,mMaxHP,MaxHP);
	CC_SYNTHESIZE(int,mCurHP,CurHP);
	//护甲;
	CC_SYNTHESIZE(int,DEF,DEF);
	CC_SYNTHESIZE(int,APDEF,APDEF);
	//实体被摧毁奖励金钱;
	CC_SYNTHESIZE(int,mRewardMoney,RewardMoney);
	//实体界;(怪物/障碍/其它)
	CC_SYNTHESIZE(int,mKingdom,Kingdom);


	

private:
	//const CCPoint m_anchorPoint;

	//测试用初始化;
	bool init();
	void autoZorder(float);

	

};


//委托类;
class LifeReduceDelegate
{
public:
	virtual void lifereduce(int hart =1) = 0;//调用GameRun的函数,使生命泉生命减少;
};