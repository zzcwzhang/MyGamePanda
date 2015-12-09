#include "Tools.h"
#include "SConfig.h"
bool Tools::isHappend(int rate)
{
	int ra = rand()%101;
	return ra< rate;
}
int Tools::getRandom(int maxv)
{

	int t =  rand();
	int index = t %maxv;
	return index;
}

long Tools::getcurrenttime()
{
	/*struct cc_timeval tv;
	CCTime::gettimeofdayCocos2d(&tv, NULL);
	long long  time = ((long long)tv.tv_sec) * 1000+ tv.tv_usec / 1000;
	return time;*/
	//struct tm *tm ;
	time_t timep ;
	long ctime = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 ) 
	time(&timep );
#else  
	struct cc_timeval now;  
	CCTime::gettimeofdayCocos2d (&now, NULL);  
	timep = now. tv_sec;
#endif  
	return timep;
}
CCImage* Tools::getImgFromSprite(CCSprite* sprite,float w,float h)
{
	CCImage * bgImg = NULL;
	ccColor4B color4B = {0, 0, 0, 0};  
	//开始准备绘制  
	CCRenderTexture* m_pRenderTexture = CCRenderTexture::create(w,h, kCCTexture2DPixelFormat_RGBA8888);  
	m_pRenderTexture->ignoreAnchorPointForPosition(true);  
	m_pRenderTexture->setPosition(ccp(400, 240));  
	m_pRenderTexture->setAnchorPoint(CCPointZero); 

	m_pRenderTexture->begin();  
	//绘制使用的临时精灵，与原图是同一图片  
	CCSprite* pTempSpr = CCSprite::createWithSpriteFrame(sprite->displayFrame());  
	pTempSpr->setPosition(ccp(w / 2, h / 2));  
	pTempSpr->visit();  
	//结束绘制  
	m_pRenderTexture->end();  
	//通过画布拿到这张画布上每个像素点的信息，封装到CCImage中  
	bgImg =m_pRenderTexture->newCCImage();  
	//绘制完成后清理画布的内容  
	m_pRenderTexture->clear(0, 0, 0, 0);  
	CC_SAFE_RELEASE(m_pRenderTexture);
	CC_SAFE_RELEASE(pTempSpr);
	return bgImg;
}
std::vector<std::string> Tools::split(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}