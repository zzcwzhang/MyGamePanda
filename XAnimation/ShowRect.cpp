#include "ShowRect.h"
#include "GameState.h"

ShowRect::ShowRect(void)
{
	w = 0;
	h = 0;
}


ShowRect::~ShowRect(void)
{
	
}
/************************************************************************/
/* 设置父节点                                                                     */
/************************************************************************/
void ShowRect::setRectInfo(float x,float y,float w,float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

}
void ShowRect::setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
void ShowRect::draw(void)
{
	glLineWidth( 2.0f );
	ccDrawColor4B(r,g,b,a);
	CCPoint vertices[] = { ccp(x,y), ccp(x,y+h), ccp(x+w,y+h),
		ccp(x+w,y),ccp(x,y)};
	ccDrawPoly(vertices, 5, false);

	/*ccPointSize(6);
	ccDrawPoints( vertices, 4);
	//中心点
	ccDrawColor4B(255,0,0,255);
	CCPoint center[] = {ccp(w/2,h/2)};
	ccPointSize(6);
	ccDrawPoints( center, 1);*/
}