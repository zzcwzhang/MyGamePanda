#ifndef __BATTERY_CHOICE__
#define __BATTERY_CHOICE__

#include "Tower/Footman.h"
#include "SConfig.h"

class BatteryChoice : public CCLayer 
{
private:
	int fX;
	int fY;
public:
	int Stage;
	int Chapter;
	int Kind;
	CCLabelTTF * bPrice;
	vector<int>kindList; //init里装载;
	CCArray* spriteArray;
	BatteryChoice();
	~BatteryChoice();
public:
	void ShowChoiceMenu(CCPoint mpoint);
	static BatteryChoice*create(CCNode* node,CCPoint axie);
	
	void touchBegan(int Kind);
	int touchEnd(float x,float y);
	void onEnter();
	void onExit();
	
	virtual bool init(int c_level);
	
	void Appearance();
	void Exeunt();

	void checkCoinEnough(CCObject* obj);
};

class BatteryUpgrade : public CCLayer
{
public:
	int Levels;
	int Kind;
	Shooter *tower;
	CCArray* spriteArray;
	CCLabelTTF * uPrice;
	CCLabelTTF * sPrice;


	float circleScale;
public:
	void onEnter();
	void onExit();
	BatteryUpgrade();
	~BatteryUpgrade();
	static BatteryUpgrade*create(CCNode* node,Shooter*tower,CCPoint axie);
	virtual bool init();
	int touchEnd(float x,float y);
	void buAppearance();
	void buExeunt();

	void checkCoinEnough(CCObject* obj);

public:
	//接口;
	void ShowUpgradeMenu(int cellid);
};
#endif