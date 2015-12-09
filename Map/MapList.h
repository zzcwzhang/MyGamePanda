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
	//������ͼ;
	int mapHP;
	
	//��ͼ·��-----------;
	void getPointArray();
	//�����  ���½�;
	std::list<CCPoint> drawlist;
	//���ο�Ķ���;
	std::list<CCRect> rectlist;
	array1(Cell*) celllist;
	//�յ�����;
	array1(CCPoint) pvec;

	void addbloodpoor(CCPoint poor_Point);

public:
	//�ӿ�;
	void hartBloodpoor(int demon_atk);

	Cell* getTouch(float px, float py);
	void SetSmoke( CCPoint pointed );

};


