#ifndef __x_SHOWRECT__
#define __x_SHOWRECT__
#include "SConfig.h"


class ShowRect :public CCNode
{
public:
	
	ShowRect(void);
	~ShowRect(void);
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
	float w;
	float h;
	float x;
	float y;
    void setRectInfo(float x,float y,float w,float h);
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void draw(void);
};

#endif