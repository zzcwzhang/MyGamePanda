#include "AppDelegate.h"
#include "GameManager.h"
#include "SConfig.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
#define USE_TALKINGDATA 1

using namespace CocosDenshion;  
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	pDirector->setOpenGLView(pEGLView);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(S_WIDTH, S_HEIGHT, kResolutionExactFit);
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);		//设置为正交投影
	// turn on display FPS
	pDirector->setDisplayStats(true);
	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	CCScene *pScene = GameManager::scene();
	//CCScene *pScene = CCScene::create();
	// run
	pDirector->runWithScene(pScene);


	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
