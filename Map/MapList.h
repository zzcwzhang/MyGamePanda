#pragma once;

#include "cocos2d.h"
#include "ZConfig.h"


USING_NS_CC;

class Cell;

class MapList : public CCNode
{
private:

public:
	MapList();
	~MapList();
	static MapList*create(int tollgate);
	static int getTowerList(int mapNum,int index);
	bool initMap(int tollgate);
	void changeBGView(const char*str);
	static int getBossLifeTime(int mapNum);
	static int getBossHP(int mapNum);

	void update();


public:
	CCTMXTiledMap*tmxMap;
	CCSprite*BGView;
	int m_tollgate;

public:
	//生命地图;
	int mapHP;
	
	//地图路径-----------;
	void getPointArray();
	//画格点  左下角;
	std::list<CCPoint> drawlist;
	//矩形框的队列;
	std::list<CCRect> rectlist;
	array1(Cell*) celllist;
	//拐点容器;
	array1(CCPoint) pvec;

	void addbloodpoor(CCPoint poor_Point);

public:
	//接口;
	void hartBloodpoor(int demon_atk);

	Cell* getTouch(float px, float py);
	void SetSmoke( CCPoint pointed );

};


