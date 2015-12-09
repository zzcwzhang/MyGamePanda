#ifndef __XTOOLS___
#define  __XTOOLS___
#include "SConfig.h"
class Tools
{
public:
	static bool isHappend(int rate);
	static int getRandom(int maxv);
	static long getcurrenttime();
	static CCImage* getImgFromSprite(CCSprite* sprite,float w,float h);
	static std::vector<std::string> split(std::string str,std::string pattern);
};
#endif