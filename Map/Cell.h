#pragma once;
#include "ZConfig.h"
#include "cocos2d.h"


#define LIST_MAXCOUNT (9)
#define	LINE_MAXCOUNT (16)

#define cells  Cell::getCellarray()

enum CellObject
{
	eVoid = 0,
	eSpace,
	eBuild,
	eShooter
};


USING_NS_CC;

typedef CCPoint IntPoint;

class Cell
{
public:
	Cell(int Num);
	Cell();
	~Cell();
	IntPoint Pxy;
	CCRect CellRect;
	int curObject;
	void *m_object;

	


	int getID()
	{
		return (int)(Pxy.x+Pxy.y*LIST_MAXCOUNT);
	};

	CCPoint getMidPoint()
	{
		return ccp((Pxy.x+0.5)*ZC_RECTSIZE,(Pxy.y+0.5)*ZC_RECTSIZE);
	};


	static array1(Cell*) getCellarray();
	static void deleteCells();

private:
	static array1(Cell*) g_cells;
};