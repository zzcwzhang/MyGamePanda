#include "XRect.h"
#include "GameState.h"

XRect::XRect(void)
{
	w = 0;
	h = 0;
}


XRect::~XRect(void)
{
	
}
/************************************************************************/
/* ���ø��ڵ�                                                                     */
/************************************************************************/
void XRect::setSize(int w,int h)
{
	this->w = w;
	this->h = h;

}
void XRect::draw(void)
{
	glLineWidth( 2.0f );
	ccDrawColor4B(255,255,255,255);
	CCPoint vertices[] = { ccp(0,0), ccp(0,h), ccp(w,h),
		ccp(w,0),ccp(0,0)};
	ccDrawPoly(vertices, 5, false);
 	CCPoint vertices2[] = { ccp(0,0), ccp(0,h), ccp(w,h),
 		ccp(w,0),ccp(w,h/2)};
	ccPointSize(6);
	ccDrawPoints( vertices2, 5);
	//���ĵ�

	ccDrawColor4B(255,0,0,255);
	CCPoint center[] = {ccp(w/2,h/2)};
	ccPointSize(6);
	ccDrawPoints( center, 1);
}