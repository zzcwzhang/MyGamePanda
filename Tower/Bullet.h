#pragma once;

#include "Atkable/Atkable.h"


class Bullet :public cocos2d::CCNode
{
public:
	~Bullet();
	//Ŀ�궨λ�ӵ�;
	static Bullet* create(CCNode* father,CCPoint origin);
	bool init(CCNode* father,CCPoint origin);
	//���û�������;
	void setAttackProperty(int id,int hart, int hartstyle, int level);//��������;
	void setBulletBuff(AT_state buffID,int bufftimes,int bufflevel);//����ʡ��;
	void setBulletContinueHart(int chID , int power,int times);
	//������ʽһ:����Ŀ�깥��;
	void LockAttack(Atkable* aim);
	void hitCallBack();


	//������ʽ������׼����;������Ŀ��ĽǶ�;  //�Ƿ���ת�������ٶ�;
	float CollimationAttack(Atkable* aim);

	//������ʽ�������򹥻�;
	void DirectionAttack(float roa);

	//������ʽ�ģ���;
	void CircleAttack(float radius);

	void circleCallback();

	void update(float);

	//������Ŀ��Ƕ�;
	float countAngle(CCPoint aimPoint);
	//��Χ���;
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

	//��ת����;
	CCPoint flyVec2; 
	
	//�Ƿ񹥻�һ��;
	bool attackOnce;

	//��ת�ٶ�;
	float rotationSpeed;
	//����֡����;
	int steplife;

	//�������б�;
	array1(Atkable*) atkedarray;

	float circle_radius;

};

