#include "TextureMake.h"

NAMESPACE_ZJG_BEGIN

TextureMake::TextureMake()
{
	this->m_width = 0;
	this->m_height = 0;
	//this->m_pRenderMake = NULL;
	this->m_pTexture = NULL;
	this->m_pMap = NULL;
	m_offsetX = 0;
	m_offsetY = 0;
	m_pdata = NULL;
	//m_Ids.resize(130,0);
}

TextureMake::~TextureMake()
{
	clear();
}

TextureMake* TextureMake::create(int width, int height)
{
	TextureMake *pRet = new TextureMake();
	pRet->initWithWidthHeight(width,height);
	return pRet;
}

void TextureMake::initWithWidthHeight(int width, int height)
{
	this->m_height = height;
	this->m_width = width;
	this->m_pMap = new CCDictionary();
	//this->m_pRenderMake = CCRenderTexture::create(width,height);
	//this->m_pRenderMake->retain();
	//this->m_offsetX = 0;//width > 512 ? width/1024 : 0;
	//this->m_offsetY = 0;//height > 512 ? height/1024 : 0;
	unsigned int len = width * height * 4;
	this->m_pdata = (unsigned char*)malloc(len);
	memset(this->m_pdata,0,len);
}

//CCRect TextureMake::addSprite(CCSprite *sprite,int keyId)
//{
//	RectNode *node = (RectNode*)this->m_pMap->objectForKey(keyId);
//	if(node)
//	{
//		return node->m_rect;
//	}
//	CCRect rr = sprite->getTextureRect();
//	CCRect root = CCRect(2,2,m_width - 4,m_height - 4);
//	if(addSpritInRect(root,sprite))
//	{
//		CCRect rect = CCRect(sprite->getPositionX() + 1,sprite->getPositionY() - 1,rr.size.width,rr.size.height);
//		node = new RectNode(rect);
//		this->m_pMap->setObject(node,keyId);
//		return rect;
//	}
//	else 
//	{
//		CCAssert(false,"size no enougth!");
//		return CCRectZero;
//	}
//}

CCRect TextureMake::addImage(CCImage *img,int keyId)
{
	RectNode *node = (RectNode*)this->m_pMap->objectForKey(keyId);
	if(node)
	{
		return node->m_rect;
	}
	unsigned int imgWidth = img->getWidth();
	unsigned int imgHeight = img->getHeight();
	CCRect root = CCRect(0,0,m_width,m_height);
	if((node = addImageInRect(root,img)) != NULL)
	{
		this->m_pMap->setObject(node,keyId);
		m_Ids.push_back(keyId);
		this->maxImgIndex = keyId;
		return node->m_rect;
	}
	else
	{
		//CCAssert(false,"size no enougth!");
		return CCRectZero;
	}
}

CCRect TextureMake::replaceImage(CCImage *img,int keyId)
{
	RectNode *node = (RectNode*)this->m_pMap->objectForKey(keyId);
	if(node)
	{
		CCRect rect = node->m_rect;
		initWidthImage(img,rect);
	}
	else
	{
		return addImage(img,keyId);
	}
	return CCRectZero;
}

CCRect TextureMake::rectForKey(int keyId)
{
	CCObject *obj = this->m_pMap->objectForKey(keyId);
	if(obj)
	{
		RectNode *node = (RectNode*)obj;
		return node->m_rect;
	}
	else
	{
		return CCRectZero;
	}
}
CCSprite* TextureMake::getSprite(int key,int cx,int cy,int cw,int ch){
	CCRect rect = rectForKey(key);
	if(!rect.equals( CCRectZero))
	{
		int rx = rect.getMinX()+cx;
		int ry = rect.getMinY()+cy;
		
		CCRect r = CCRectZero;
		r.setRect(rx,ry,cw,ch);
		CCSprite *sprite = NULL;
		sprite = CCSprite::createWithTexture(m_pTexture,r);
		return sprite;
	}else{
		return NULL;
	}
}
RectNode* TextureMake::getIntersectsRect(CCRect rect,CCSize spriteSize)
{
	CCRect spriteRect = CCRect(rect.origin.x, rect.origin.y,spriteSize.width, spriteSize.height);
	int count = this->m_pMap->count();
	RectNode *sp = NULL;
	int i = 0;
	CCDictElement *elem =  this->m_pMap->m_pElements;
	while(i < count)
	{
		sp = (RectNode*)elem->getObject();
		CCRect rr = sp->m_rect;
		if(rr.intersectsRect(spriteRect))
		{
			return sp;
		}
		elem = (CCDictElement*)elem->hh.next;
		i++;
	}
	return NULL;
}

//RectNode* TextureMake::addSpritInRect(CCRect rect, CCSprite *sprite)
//{
//	RectNode *node = NULL;
//	CCRect spriteRect = sprite->getTextureRect();
//	if(rect.size.width < spriteRect.size.width || rect.size.height < spriteRect.size.height)
//	{
//		return NULL;
//	}
//	RectNode *intersectSprite = getIntersectsRect(rect,spriteRect.size);
//	if(intersectSprite != NULL)
//	{
//		int x = intersectSprite->m_rect.getMaxX() + 1;
//		int width = rect.getMaxX() - x;
//		int y = intersectSprite->m_rect.getMaxY() + 1;
//		int height = rect.getMaxY() - y;
//		if((node = addSpritInRect(CCRect(x,rect.origin.y,width,rect.size.height),sprite)))
//		{
//			return node;
//		}
//		else if((node = addSpritInRect(CCRect(rect.origin.x,y,rect.size.width,height),sprite)))
//		{
//			return node;
//		}
//		return NULL;
//	}
//	else
//	{
//		sprite->setAnchorPoint(ccp(0,0));
//		sprite->setPosition(ccp(rect.origin.x ,rect.origin.y));
//		sprite->setFlipY(true);
//		sprite->getTexture()->setAliasTexParameters();
//		this->m_pRenderMake->begin();
//		sprite->visit();
//		this->m_pRenderMake->end();
//		node = new RectNode(rect);
//	}
//
//	return node;
//}

RectNode* TextureMake::addImageInRect(CCRect rect, CCImage *img)
{
	RectNode *node = NULL;
	unsigned int imgWidth = img->getWidth();
	unsigned int imgHeight = img->getHeight();
	if(rect.size.width < imgWidth || rect.size.height < imgHeight)
	{
		return NULL;
	}

	RectNode *intersectSprite = getIntersectsRect(rect,CCSize(imgWidth,imgHeight));
	if(intersectSprite != NULL)
	{
		int x = intersectSprite->m_rect.getMaxX() + 1;
		int width = rect.getMaxX() - x;
		int y = intersectSprite->m_rect.getMaxY() + 1;
		int height = rect.getMaxY() - y;
		if((node = addImageInRect(CCRect(x,rect.origin.y,width,rect.size.height),img)))
		{
			return node;
		}
		else if((node = addImageInRect(CCRect(rect.origin.x,y,rect.size.width,height),img)))
		{
			return node;
		}
		return NULL;
	}
	else
	{
		rect = CCRect(rect.origin.x ,rect.origin.y,imgWidth,imgHeight);
		initWidthImage(img,rect);
		node = new RectNode(rect);
	}
	return node;
}

void TextureMake::initWidthImage(CCImage *image,CCRect rect)
{
	unsigned char*            tempData = image->getData();
	unsigned int*             inPixel32 = NULL;
	unsigned char*            inPixel8 = NULL;
	unsigned short*           outPixel16 = NULL;
	unsigned int width = image->getWidth();
	unsigned int height = image->getHeight();
	bool                      hasAlpha = image->hasAlpha();
	CCSize                    imageSize = CCSizeMake((float)(width), (float)(height));
	CCTexture2DPixelFormat    pixelFormat;
	size_t                    bpp = image->getBitsPerComponent();
	
	// compute pixel format
	if(hasAlpha)
	{
		pixelFormat = kCCTexture2DPixelFormat_Default;
	}
	else
	{
		if (bpp >= 8)
		{
			pixelFormat = kCCTexture2DPixelFormat_RGB888;
		}
		else 
		{
			pixelFormat = kCCTexture2DPixelFormat_RGB565;
		}

	}

	// Repack the pixel data into the right format
	unsigned int length = width * height;

	if (pixelFormat == kCCTexture2DPixelFormat_RGB565)
	{
		if (hasAlpha)
		{
			// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"

			tempData = new unsigned char[width * height * 2];
			outPixel16 = (unsigned short*)tempData;
			inPixel32 = (unsigned int*)image->getData();

			for(unsigned int i = 0; i < length; ++i, ++inPixel32)
			{
				*outPixel16++ = 
					((((*inPixel32 >>  0) & 0xFF) >> 3) << 11) |  // R
					((((*inPixel32 >>  8) & 0xFF) >> 2) << 5)  |  // G
					((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);    // B
			}
		}
		else 
		{
			// Convert "RRRRRRRRRGGGGGGGGBBBBBBBB" to "RRRRRGGGGGGBBBBB"

			tempData = new unsigned char[width * height * 2];
			outPixel16 = (unsigned short*)tempData;
			inPixel8 = (unsigned char*)image->getData();

			for(unsigned int i = 0; i < length; ++i)
			{
				*outPixel16++ = 
					(((*inPixel8++ & 0xFF) >> 3) << 11) |  // R
					(((*inPixel8++ & 0xFF) >> 2) << 5)  |  // G
					(((*inPixel8++ & 0xFF) >> 3) << 0);    // B
			}
		}    
	}
	else if (pixelFormat == kCCTexture2DPixelFormat_RGBA4444)
	{
		// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRGGGGBBBBAAAA"

		inPixel32 = (unsigned int*)image->getData();  
		tempData = new unsigned char[width * height * 2];
		outPixel16 = (unsigned short*)tempData;

		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
				((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
				((((*inPixel32 >> 8) & 0xFF) >> 4) <<  8) | // G
				((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
				((((*inPixel32 >> 24) & 0xFF) >> 4) << 0);  // A
		}
	}
	else if (pixelFormat == kCCTexture2DPixelFormat_RGB5A1)
	{
		// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGBBBBBA"
		inPixel32 = (unsigned int*)image->getData();   
		tempData = new unsigned char[width * height * 2];
		outPixel16 = (unsigned short*)tempData;

		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
				((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | // R
				((((*inPixel32 >> 8) & 0xFF) >> 3) <<  6) | // G
				((((*inPixel32 >> 16) & 0xFF) >> 3) << 1) | // B
				((((*inPixel32 >> 24) & 0xFF) >> 7) << 0);  // A
		}
	}
	else if (pixelFormat == kCCTexture2DPixelFormat_A8)
	{
		// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "AAAAAAAA"
		inPixel32 = (unsigned int*)image->getData();
		tempData = new unsigned char[width * height];
		unsigned char *outPixel8 = tempData;

		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel8++ = (*inPixel32 >> 24) & 0xFF;  // A
		}
	}

	if (hasAlpha && pixelFormat == kCCTexture2DPixelFormat_RGB888)
	{
		// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRRRRGGGGGGGGBBBBBBBB"
		inPixel32 = (unsigned int*)image->getData();
		tempData = new unsigned char[width * height * 3];
		unsigned char *outPixel8 = tempData;

		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel8++ = (*inPixel32 >> 0) & 0xFF; // R
			*outPixel8++ = (*inPixel32 >> 8) & 0xFF; // G
			*outPixel8++ = (*inPixel32 >> 16) & 0xFF; // B
		}
	}

	if (hasAlpha && pixelFormat == kCCTexture2DPixelFormat_RGB888)
	{
		// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRRRRGGGGGGGGBBBBBBBB"
		inPixel32 = (unsigned int*)image->getData();
		tempData = new unsigned char[width * height * 3];
		unsigned char *outPixel8 = tempData;

		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel8++ = (*inPixel32 >> 0) & 0xFF; // R
			*outPixel8++ = (*inPixel32 >> 8) & 0xFF; // G
			*outPixel8++ = (*inPixel32 >> 16) & 0xFF; // B
		}
	}
	if (pixelFormat == kCCTexture2DPixelFormat_RGB888)
	{
		// Convert  "RRRRRRRRGGGGGGGGBBBBBBBB" to "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" 
		unsigned char *pixelData = image->getData();
		tempData = new unsigned char[width * height * 4];
		unsigned char *outPixel8 = tempData;
		int k = 0;
		for(unsigned int i = 0; i < length; ++i)
		{
			*outPixel8++ = (pixelData[k++] ) & 0xFF; // R
			*outPixel8++ = (pixelData[k++]) & 0xFF; // G
			*outPixel8++ = (pixelData[k++]) & 0xFF; // B
			*outPixel8++ = 0xFF; // A
		}
	}

	//initWithData(tempData, pixelFormat, width, height, imageSize);
	unsigned int* destData = (unsigned int *)m_pdata;
	unsigned int* srcData = (unsigned int *)tempData;
	for(int i = rect.origin.y; i < rect.origin.y + rect.size.height; i++)
	{
		unsigned int index = i * m_width + rect.origin.x;
		unsigned int pixelIndex = (i  - rect.origin.y)* rect.size.width;
		memcpy(&destData[index],&srcData[pixelIndex],rect.size.width*4);
	}
	if (tempData != image->getData())
	{
		delete [] tempData;
	}
}

void TextureMake::clear()
{
	if(this->m_pMap)
	{
		int count = this->m_pMap->count();
		RectNode *sp = NULL;
		int i = 0;
		CCDictElement *elem =  this->m_pMap->m_pElements;
		while(i < count)
		{
			sp = (RectNode*)elem->getObject();
			elem = (CCDictElement*)elem->hh.next;
			sp->release();
			i++;
		}
		this->m_pMap->removeAllObjects();
		this->m_pMap->release();
		this->m_pMap = NULL;
	}
	if(this->m_pdata)
	{
		delete m_pdata;
		m_pdata = NULL;
	}
	m_Ids.clear();
	//CC_SAFE_RELEASE_NULL(m_pTexture);
	CC_SAFE_DELETE(m_pTexture);
	//m_pTexture = NULL;
	//if(m_pTexture = NULL;
	/*if(this->m_pRenderMake)
	{
	this->m_pRenderMake->release();
	this->m_pRenderMake = NULL;
	}*/
}

void TextureMake::saveToFile(char *fileName)
{
	/*if(this->m_pRenderMake)
	{
	this->m_pRenderMake->saveToFile(fileName,kCCImageFormatPNG);
	}*/
}

CCTexture2D* TextureMake::getTexture()
{
	/*if(m_pTexture)
	{
		CCLog("m_pTexture != Null");
		//m_pTexture->release();
		delete m_pTexture;
		m_pTexture = NULL;
	}*/
	m_pTexture = new CCTexture2D();
	CCLog("initWithData ");
	m_pTexture->initWithData(m_pdata,kCCTexture2DPixelFormat_RGBA8888,m_width,m_height,CCSize(m_width,m_height));
	CCLog("initWithData over");
	m_pTexture->m_bHasPremultipliedAlpha = true;
	delete m_pdata;
	m_pdata = NULL;
	return m_pTexture;//this->m_pRenderMake->getSprite()->getTexture();
}

CCImage *TextureMake::getImage()
{
	CCImage *img = new CCImage();
	img->initWithImageData(m_pdata,m_width * m_height,CCImage::kFmtPng,m_width,m_height);
	return img;
}
//////////////////////////////////////////////////////////////////////////
RectNode::RectNode(CCRect rect)
{
	this->m_rect = rect;
}
RectNode ::~RectNode()
{

} 
NAMESPACE_ZJG_END