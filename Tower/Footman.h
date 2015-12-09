#pragma once;

#include "Tower/Shooter.h"
#include "Tower/Bullet.h"


#define INFO(a) inf->footmanarray[i][a]

class Footman:public Shooter
{
public:
	enum Data
	{
		ID = 0,
		ATK,
		ATKTYPE,
		shootspeed,
		shootrange,
		bugprice,
		upleveprice,
		fulllevelprice
	};

public:
	Footman();

	~Footman();

	static Footman* create(CCNode* father,CCPoint point,int ID);
	static Footman* create(CCNode* father,int cellid,int ID);

	bool init(CCNode* father,CCPoint point,int ID);
	
	virtual void Fire(Atkable* aim);

	void setBuildLevel(int level);

	int sellSelf();

	int getNextLevelPrice();

	

};


