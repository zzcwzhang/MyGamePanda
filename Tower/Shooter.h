#pragma once

#include "Atkable/Atkable.h"
#include "Map/Cell.h"

#define kS_KIND_FOOTMAN 0
#define kS_KIND_HERO 1


class Shooter:public CCNode
{
public:
	//���൥������ʹ�ú���;
	static Shooter* create(CCNode* father,CCPoint point,int ID);
	bool init(CCNode* father,CCPoint point,int ID);
	void draw();
	//end

	Shooter();
	~Shooter();
	

	CC_SYNTHESIZE(int,mKind,Kind);	//���ࣺӢ�ۡ��ʹ�;
	CC_SYNTHESIZE(int,mID,ID); //���;
	CC_SYNTHESIZE(int,mATK,ATK); //������;
	CC_SYNTHESIZE(int,mhartStyle,HartStyle);//��������(����ħ������ϡ���ʥ);
	CC_SYNTHESIZE(int,mshootSpeed,ShootSpeed);//�����ٶ�;
	CC_SYNTHESIZE(int,mshootRange,ShootRange);//������Χ;
	CC_SYNTHESIZE(int,matkLevel,AtkLevel);//�����ȼ�;
	CC_SYNTHESIZE(int,mBuyPrice,BuyPrice);//�����Ǯ;
	CC_SYNTHESIZE(int,mUpLevelPrice,UpLevelPrice);//������Ǯ;
	CC_SYNTHESIZE(int,mFullLevelPrice,FullLevelPrice);//������Ǯ;
	CC_SYNTHESIZE(int,mUserLevel,UserLevel);//�û��ȼ�;
	CC_SYNTHESIZE(int,m_cellID,CellID);//����ϸ��;
	//װ��;
	void ReadEquipment();
	void EquipmentHarmony();
	//����;
	void ReadRune();

	//����Ϸ������;
	virtual void setBuildLevel(int level){};
	int getBuildLevel(void)
	{ return mBuildLevel;};
	virtual int getNextLevelPrice(){return 0;};
	virtual int sellSelf();
	int getSellPrice();

	//�״��ͣѰ��Ŀ��;
	virtual void Radar();
	virtual void Fire(Atkable* aim);//���������;
	virtual CCRect getBox();
	bool isAutoRotate;

	//�Զ�ת��;
	float getMyRotation(Atkable* node);//�����ٶȣ����Ŀ��Ƕ�ԽԶ�ٶ�Խ��;
	float getMyRotation(float aimRotation);
	void autoRotate();

	//��Χ���;
	bool checkAimInRange(Atkable* obj);
	bool checkRectangleAndCircleCollision(CCPoint rectMidpoint,float rectHeight,float rectWidth,CCPoint circleMidpoint,float radius);

	//�������;
	void autoCheckUpLevel();

	void checkLevelUpEnough(CCObject *obj); 

public:

	static CCArray* shooterArray;

protected:
	CCSprite* towerSp;

	CCNode* m_father;
	//�ҵ�λ��;
	CCPoint m_location;

	//��Ƽ��������;
	int sCDtime;
	//�����ȼ�;
	int mBuildLevel;

	CCSprite* atsp;
	//���⹥����;
	int extraAttack;
};



