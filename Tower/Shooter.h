#pragma once

#include "Atkable/Atkable.h"
#include "Map/Cell.h"

#define kS_KIND_FOOTMAN 0
#define kS_KIND_HERO 1


class Shooter:public CCNode
{
public:
	//基类单独测试使用函数;
	static Shooter* create(CCNode* father,CCPoint point,int ID);
	bool init(CCNode* father,CCPoint point,int ID);
	void draw();
	//end

	Shooter();
	~Shooter();
	

	CC_SYNTHESIZE(int,mKind,Kind);	//种类：英雄、仆从;
	CC_SYNTHESIZE(int,mID,ID); //编号;
	CC_SYNTHESIZE(int,mATK,ATK); //攻击力;
	CC_SYNTHESIZE(int,mhartStyle,HartStyle);//攻击类型(物理、魔法、混合、神圣);
	CC_SYNTHESIZE(int,mshootSpeed,ShootSpeed);//攻击速度;
	CC_SYNTHESIZE(int,mshootRange,ShootRange);//攻击范围;
	CC_SYNTHESIZE(int,matkLevel,AtkLevel);//攻击等级;
	CC_SYNTHESIZE(int,mBuyPrice,BuyPrice);//购买金钱;
	CC_SYNTHESIZE(int,mUpLevelPrice,UpLevelPrice);//升级金钱;
	CC_SYNTHESIZE(int,mFullLevelPrice,FullLevelPrice);//满级金钱;
	CC_SYNTHESIZE(int,mUserLevel,UserLevel);//用户等级;
	CC_SYNTHESIZE(int,m_cellID,CellID);//所在细胞;
	//装备;
	void ReadEquipment();
	void EquipmentHarmony();
	//符文;
	void ReadRune();

	//在游戏中升级;
	virtual void setBuildLevel(int level){};
	int getBuildLevel(void)
	{ return mBuildLevel;};
	virtual int getNextLevelPrice(){return 0;};
	virtual int sellSelf();
	int getSellPrice();

	//雷达：不停寻找目标;
	virtual void Radar();
	virtual void Fire(Atkable* aim);//由子类代替;
	virtual CCRect getBox();
	bool isAutoRotate;

	//自动转向;
	float getMyRotation(Atkable* node);//趋近速度：离得目标角度越远速度越快;
	float getMyRotation(float aimRotation);
	void autoRotate();

	//范围检测;
	bool checkAimInRange(Atkable* obj);
	bool checkRectangleAndCircleCollision(CCPoint rectMidpoint,float rectHeight,float rectWidth,CCPoint circleMidpoint,float radius);

	//升级检测;
	void autoCheckUpLevel();

	void checkLevelUpEnough(CCObject *obj); 

public:

	static CCArray* shooterArray;

protected:
	CCSprite* towerSp;

	CCNode* m_father;
	//我的位置;
	CCPoint m_location;

	//设计间隔计数器;
	int sCDtime;
	//建筑等级;
	int mBuildLevel;

	CCSprite* atsp;
	//额外攻击力;
	int extraAttack;
};



