#pragma once
#include "ZConfig.h"
#include "Atkable/Atkable.h"

class Marker:public cocos2d::CCNode
{
public:

	//��������������һ���µı�ǻ��Զ�ɾ���ɵı��;

	static Marker* create(Atkable* father);

	static Marker* getCurMark();

private:
	~Marker();

	bool init(Atkable* father);

	CCSprite* m_mark;

	static Marker* curMark;
};





