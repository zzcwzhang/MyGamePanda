#ifndef _SSTARTPAGE__
#define  _SSTARTPAGE__
#include "SConfig.h"
class SStartPage:public cocos2d::CCLayer
{
public:
	SStartPage();
	~SStartPage();
	void update();
	void initMusic();
	void enterGame();
//	void initRes();
	bool loadMusic;
	bool loadMusicOver;

};
#endif