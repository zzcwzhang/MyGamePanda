#include "GameManager.h"
#include "GameState.h"
GameManager::GameManager(void)
{

}
GameManager::~GameManager(void)
{
	GameState::pureGS();
}
CCScene* GameManager::scene()
{
	CCScene *scene = CCScene::create();
	// 'layer' is an autorelease object
	GameManager *layer = GameManager::create();
	scene->addChild(layer);
	layer->addChild(m_gamestate);
	return scene;
}
