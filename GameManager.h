#ifndef _X_GAMEMANAGER___
#define  _X_GAMEMANAGER___
#include "SConfig.h"
using namespace cocos2d;
class GameManager: public cocos2d::CCLayer
{
public:
	GameManager(void);
	~GameManager(void);
	CREATE_FUNC(GameManager);
	static cocos2d::CCScene* scene();
};
#endif