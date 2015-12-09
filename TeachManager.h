#ifndef _X_TEACHMANAGER___
#define  _X_TEACHMANAGER___
#include "SConfig.h"
using namespace cocos2d;

// 剪切信息
struct ClipRectInfo 
{
	CCPoint clipPoint;	// 剪切矩形的位置
	CCSize  clipSize;	// 剪切矩形的大小

	bool operator<(const ClipRectInfo& other)
	{
		return clipPoint.y < other.clipPoint.y;
	}
};

class TeachingFream : public CCLayerColor
{
public:
	TeachingFream();
	~TeachingFream();

	static TeachingFream* create(const ClipRectInfo& rectInfo);
	
	void initClipRectInfos(const ClipRectInfo& rectInfo);

	// 销毁
	void destroy();

private:
	array1(ClipRectInfo*) m_rectInfos;
};

class TeachManager: public cocos2d::CCObject
{
public:
	TeachManager(void);
	~TeachManager(void);
};

#define pTeachManager TeachManager::sharedTeachManager()
#endif