#pragma once
#include "ZConfig.h"
#include "Atkable/Atkable.h"

class Marker:public cocos2d::CCNode
{
public:

	//单例创建：创建一个新的标记会自动删除旧的标记;

	static Marker* create(Atkable* father);

	static Marker* getCurMark();

private:
	~Marker();

	bool init(Atkable* father);

	CCSprite* m_mark;

	static Marker* curMark;
};





