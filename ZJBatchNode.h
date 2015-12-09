#ifndef __ZJBATCHNODE__
#define __ZJBATCHNODE__
#include "SConfig.h"

NAMESPACE_ZJG_BEGIN
struct Equip
{
	int key;
	int changeID;
	array2(int)equipinfo;
};

class ZJBatchNode:public cocos2d::CCSpriteBatchNode
{
public:
	ZJBatchNode(void);
	~ZJBatchNode(void);
public:
	CCDictionary*	dic_textureAtlas;//
	CCDictionary*	dic_moduleKeys;//module的atlas字典
	array1(Equip*)	equips;
	array1(Equip*)	map_curequipInfo ;//当前换装信息

	void setTextureAlas(CCTexture2D *texture,string key,int binFileIndex);//多个plist
	void setTextureAlas_singlePng(CCTexture2D *texture,string key);//单个plist
	CCTextureAtlas* getTextureAtlas(int moduleID,int textureid);
	virtual void release();
	virtual void Clean();
	virtual void draw(void);
	virtual void removeAllChildrenWithCleanup(bool cleanup);
	void changeEquip(int orgImgIndex,int equipIndex);
public:
	inline void setMyColor(ccColor3B color){this->myColor = color;};
	inline ccColor3B getMyColor(){return this->myColor;};
protected:
	bool initConfig;
	ccColor3B myColor;
};
NAMESPACE_ZJG_END
#endif
