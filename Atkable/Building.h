#pragma once;

#include "Atkable/Atkable.h"
#include "Map/Cell.h"

#define BUILDING_PARA int sort
#define BUILDING_PARA_INIT sort

class Building :public Atkable
{
public:

	~Building();

	static Building* create(BUILDING_PARA);

	bool init(BUILDING_PARA);

	void sitDownCell();

	virtual void Destroyed();

	Cell* m_Cell;

private:
	float conX;
	float conY;
};