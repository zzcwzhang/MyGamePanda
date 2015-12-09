#include "XTextBox.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) 
#include "../iconv/iconv.h"
//#include "iconv.h"//libiconv.lib
#endif
XTextBox::XTextBox(void)
{
	m_label = NULL;
	w = 0;
	h = 0;
	autoChangeLine = false;
	autoClip = true;
	fontOffsetX = 0;
	fontOffsetY = 0;
	speedX = 0;
	speedY = 0;
}
XTextBox::~XTextBox(void)
{

}
void XTextBox::destory()
{
	if(m_label)
	{

		m_label->removeFromParent();
		CC_SAFE_DELETE(m_label);
		m_label = NULL;
	}
}
void XTextBox::reset()
{
	this->text = text;
	string text_M = a2u(text.c_str());
	if(m_label == NULL)
	{
		m_label = CCLabelTTF::create();
		m_label->retain();
	}
	CCVerticalTextAlignment verticalAlignment = kCCVerticalTextAlignmentTop;
	if(anchor ==1)
	{
		verticalAlignment = kCCVerticalTextAlignmentCenter;
	}else if(anchor ==2)
	{
		verticalAlignment = kCCVerticalTextAlignmentBottom;
	}
	m_label->setString(text_M.c_str());
	m_label->setVerticalAlignment(verticalAlignment);
	m_label->setFontSize(fontSize);
	

	if(autoChangeLine)
	{
		m_label->setDimensions(CCSizeMake(w,0));
	}else
	{
		m_label->setDimensions(CCSizeMake(0,0));
	}
	m_label->setColor(ccc3(fontColor[0],fontColor[1],fontColor[2]));
	m_label->removeFromParent();
	//把要滚动的文字加入到裁剪区域
	addChild(m_label);

}
void XTextBox::setText(string text)
{
/*#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) 
	this->text = text;
	string text_M = a2u(text.c_str());
	if(m_label != NULL)
	{
		m_label->setString(text_M.c_str());
	}
#else
	if(m_label != NULL)
	{
		m_label->setString(text.c_str());
	}
#endif*/
	if(m_label != NULL)
	{
		m_label->setString(text.c_str());
	}
	float h = getTextHeight();
	setPosition(ccp(px,py-h/2));
}
void XTextBox::setTextOpcity(float opcity)
{
	if(m_label)
	{
		m_label->setOpacity(opcity);
	}
}
float XTextBox::getTextHeight()
{
	if(m_label && m_label->getTexture())
	{
		return m_label->getTexture()->getPixelsHigh();
	}
	return 0;
}
void XTextBox::setText(string text,int anchor,int fontSize)
{
	this->text = text;
	#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) 
	string text_M = a2u(text.c_str());
#else
	string text_M = text;
#endif
	//
	if(m_label == NULL)
	{
		m_label = CCLabelTTF::create();
		m_label->retain();
	}
	CCVerticalTextAlignment verticalAlignment = kCCVerticalTextAlignmentTop;
	if(anchor ==1)
	{
		verticalAlignment = kCCVerticalTextAlignmentCenter;
	}else if(anchor ==2)
	{
		verticalAlignment = kCCVerticalTextAlignmentBottom;
	}
	m_label->setString(text_M.c_str());
	m_label->setVerticalAlignment(verticalAlignment);
	m_label->setFontSize(fontSize);
	m_label->setDimensions(CCSizeMake(w,h));
	addChild(m_label);
}
int XTextBox::code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) 
	iconv_t cd;
	const char *temp = inbuf;
	const char **pin = &temp;
	char **pout = &outbuf;
	memset(outbuf,0,outlen);
	cd = iconv_open(to_charset,from_charset);
	if(cd==0) return -1;
	if(iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
	iconv_close(cd);
#endif
	return 0;
}

std::string XTextBox::u2a(const char *inbuf)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) 
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if(code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete [] outbuf;
	return strRet;
#else
	return string(inbuf);
#endif
}

std::string XTextBox::a2u(const char *inbuf)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) 
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if(code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete [] outbuf;
	return strRet;
#else
	return string(inbuf);
#endif
}

/************************************************************************/
/* 设置父节点                                                                     */
/************************************************************************/
void XTextBox::setSize(int w,int h)
{
	this->w = w;
	this->h = h;
	if(m_label)
	{
		m_label->setDimensions(CCSizeMake(w,0));
	}
/*	//绘制裁剪区域
	CCDrawNode* shap = CCDrawNode::create();
	CCPoint point[4] = {ccp(0,0), ccp(w, 0), ccp(w, h), ccp(0, h)};
	shap->drawPolygon(point, 4, ccc4f(355, 255, 255, 255), 2, ccc4f(255, 255, 255, 255));
	CCClippingNode* cliper = CCClippingNode::create();
	cliper->setStencil(shap);
	cliper->setAnchorPoint(ccp(.5, .5));
	cliper->setPosition(ccp(0, 0));
	addChild(cliper);
	m_label->removeFromParent();
	//把要滚动的文字加入到裁剪区域
	cliper->addChild(m_label);*/

}
void XTextBox::setTextColor(int r,int g,int b)
{
	if(m_label)
	{
		m_label->setColor(ccc3(r,g,b));
	}
}
void XTextBox::draw(void)
{

}