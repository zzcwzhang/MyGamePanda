#pragma once;

#include "Atkable/Atkable.h"
#include "Map/MapList.h"

#define DEMON_PARA int sort
#define DEMON_PARA_INIT sort



class Demon :public Atkable
{
public:

	Demon();

	CC_SYNTHESIZE(LifeReduceDelegate*,myDelegate,Delegate);
	CC_SYNTHESIZE(int,m_moveSpeed,MoveSpeed);
	CC_SYNTHESIZE(int,m_attack,Attack);
public:

	static Demon* create(DEMON_PARA);

	
	bool init(DEMON_PARA);


	void setPath(array1(CCPoint) path);

	void InvadeMap(MapList* map);


	array1(CCPoint) mpath;


private:
	MapList* being_attacked;

	//脸向;
	bool g_flipX;
	int direction;
	int p_index;
	//旧移动，会引发问题;
	void BodySubstitute( bool filx,bool goback );
	void spaceJump();
	void moveDemon();
	void jumpDemon();
	void spaceJumpArrive();
	void SetCESHIData();
	void SetWaveData();
	//新移动;


};