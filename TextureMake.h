#ifndef TEXTUREMAKE_H_
#define TEXTUREMAKE_H_
#include "SConfig.h"
 NAMESPACE_ZJG_BEGIN
class RectNode : public CCObject
{
public:
	CCRect m_rect;
public:
	RectNode(CCRect rect);
	~RectNode();
};

//////////////////////////////////////////////////////////////////////////
class TextureMake
{
public:
	TextureMake();
	~TextureMake();
	static TextureMake* create(int width, int height);
	void initWithWidthHeight(int width, int height);
	//CCRect addSprite(CCSprite *sprite,int keyId);
	CCRect addImage(CCImage *img,int keyId);
	CCRect replaceImage(CCImage *img,int keyId);
	CCRect rectForKey(int keyId);
	CCTexture2D* getTexture();
	CCImage *getImage();
	void clear();
	void saveToFile(char *fileName);
	short maxImgIndex;//Í¼Æ¬×î´óË÷Òý
	std::vector<short> m_Ids;
	CCSprite* getSprite(int key,int cx,int cy,int cw,int ch);
	CCTexture2D *m_pTexture;
private:
	//RectNode* addSpritInRect(CCRect rect, CCSprite *sprite);
	RectNode* addImageInRect(CCRect rect, CCImage *img);
	RectNode* getIntersectsRect(CCRect rect,CCSize spriteSize);
	void initWidthImage(CCImage *image,CCRect rect);
private:
	//CCRenderTexture *m_pRenderMake;

	CCDictionary *m_pMap;
	int m_width;
	int m_height;
	short m_offsetX;
	short m_offsetY;
	unsigned char *m_pdata;
};
NAMESPACE_ZJG_END
#endif