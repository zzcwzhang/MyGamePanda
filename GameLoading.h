#ifndef __X_GAMELOADING__
#define __X_GAMELOADING__
#include "SConfig.h"
NAMESPACE_ZJG_BEGIN
class GameLoading:public cocos2d::CCLayer
{
public:
	GameLoading(void);
	~GameLoading(void);
	void setProcess(int process);
private:
	CCLabelTTF* processLabel;
};
NAMESPACE_ZJG_END
#endif