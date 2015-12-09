#pragma once;

#include "Atkable/Atkable.h"


class Bullet :public cocos2d::CCNode
{
public:
	~Bullet();
	//目标定位子弹;
	static Bullet* create(CCNode* father,CCPoint origin);
	bool init(CCNode* father,CCPoint origin);
	//设置基本属性;
	void setAttackProperty(int id,int hart, int hartstyle, int level);//必须设置;
	void setBulletBuff(AT_state buffID,int bufftimes,int bufflevel);//可以省略;
	void setBulletContinueHart(int chID , int power,int times);
	//攻击方式一:锁定目标攻击;
	void LockAttack(Atkable* aim);
	void hitCallBack();


	//攻击方式二：瞄准攻击;返回与目标的角度;  //是否旋转，飞行速度;
	float CollimationAttack(Atkable* aim);

	//攻击方式三：方向攻击;
	void DirectionAttack(float roa);

	//攻击方式四：环;
	void CircleAttack(float radius);

	void circleCallback();

	void update(float);

	//计算与目标角度;
	float countAngle(CCPoint aimPoint);
	//范围检测;
	bool checkAimInRange( Atkable* obj ,float mshootRange);

public:
	CCNode* mfather;
private:
	CCSprite* bsp;
	

	int m_ID;
	int m_hart;
	int m_hartStyle;
	int u_level;

	AT_state callbackBuff;
	int callbackBuffTimes;
	int m_bufflevel;

	int callbackchID ;
	int callbackpower;
	int callbacktimes;

	//旋转属性;
	CCPoint flyVec2; 
	
	//是否攻击一次;
	bool attackOnce;

	//旋转速度;
	float rotationSpeed;
	//飞行帧生命;
	int steplife;

	//攻击过列表;
	array1(Atkable*) atkedarray;

	float circle_radius;

};

