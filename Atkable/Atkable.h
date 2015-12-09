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
	AS_NORMAL =0,//����;
	AS_GOD = 0x01<<1,//�޵�;
	AS_ICE = 0x01<<2,//����;
	AS_SLOW = 0x01<<3,//����;
	AS_DIZZINESS = 0x01<<4,//ѣ��;
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

	//��������Atkable���б�;
	static cocos2d::CCArray* AtkableArray;


	//**����**;

	//�����е�;
	virtual cocos2d::CCPoint getMidPoint();
	//�����Χ��;
	virtual CCRect getBox();

	//**�ӿ�**;

	void getHart(int power,int hartStyle,int hlevel = 1);

	void getBuff(AT_state id,int times, int level);

	void getContinueHart(int chID , int power,int times);


	CCSize getSPContentSize();

	virtual void Destroyed();

	//����Y�����Զ����ò���ȼ�;
	void setAutoZoder(bool isForever);

protected:
	//ʵ�徫��;
	CCSprite* msp;
	//Ѫ��;
	CCProgressTimer* progress1;

	//�ٶȿ���;
	CCScheduler *scheduler;
	CCActionManager* actionManager;
	void SpeedControl();

	//״̬;
	void updateState(Buff* tbuf);
	AT_state mState;	
	std::list<Buff*> buffArray;
	
	//�����˺�;
	std::list<ContinueHart*> cHartArray;

	CC_SYNTHESIZE(int,ID,ID);
	//ʵ������������;
	CC_SYNTHESIZE(int,mMaxHP,MaxHP);
	CC_SYNTHESIZE(int,mCurHP,CurHP);
	//����;
	CC_SYNTHESIZE(int,DEF,DEF);
	CC_SYNTHESIZE(int,APDEF,APDEF);
	//ʵ�屻�ݻٽ�����Ǯ;
	CC_SYNTHESIZE(int,mRewardMoney,RewardMoney);
	//ʵ���;(����/�ϰ�/����)
	CC_SYNTHESIZE(int,mKingdom,Kingdom);


	

private:
	//const CCPoint m_anchorPoint;

	//�����ó�ʼ��;
	bool init();
	void autoZorder(float);

	

};


//ί����;
class LifeReduceDelegate
{
public:
	virtual void lifereduce(int hart =1) = 0;//����GameRun�ĺ���,ʹ����Ȫ��������;
};