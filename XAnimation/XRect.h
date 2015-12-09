#ifndef __x_XRECT__
#define __x_XRECT__
#include "SConfig.h"


class XRect :public CCNode
{
public:
	
	XRect(void);
	~XRect(void);
	int w;
	int h;
    void setSize(int w,int h);
	void draw(void);
};

#endif