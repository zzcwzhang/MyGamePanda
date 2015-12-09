#ifndef __x_XTEXTBOX__
#define __x_XTEXTBOX__
#include "SConfig.h"



class XTextBox :public CCNode
{
public:
	XTextBox(void);
	~XTextBox(void);
	string text;
	float fontOffsetX;
	float fontOffsetY;
	int w;
	int h;
	float px;
	float py;
	int anchor;
	int fontSize;
	float speedX;
	float speedY;
	bool autoChangeLine;//自动换行 
	bool autoClip;//裁剪区域
	int fontColor[3];
	CCLabelTTF* m_label;
	void setSize(int w,int h);
	void draw(void);
	void setText(string text);
	void setText(string text,int anchor,int fontSize);
	void setTextColor(int r,int g,int b);
	void reset();
	void destory();
	float getTextHeight();
	void setTextOpcity(float opcity);
private:
	int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen);
	std::string u2a(const char *inbuf);
	std::string a2u(const char *inbuf);
};
#endif