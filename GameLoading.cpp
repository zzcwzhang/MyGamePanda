#include "GameLoading.h"
#include "GameState.h"
NAMESPACE_ZJG_BEGIN
GameLoading::GameLoading(void)
{
	processLabel = CCLabelTTF::create();
	processLabel->setFontSize(30);
	processLabel->retain();
	processLabel->setPosition(ccp(m_gamestate->curScreenW/2,m_gamestate->curScreenH/2));
	addChild(processLabel);
}
GameLoading::~GameLoading(void)
{
	if(processLabel)
	{
		processLabel->removeFromParent();
		CC_SAFE_DELETE(processLabel);
		processLabel = NULL;
	}
}
void GameLoading::setProcess(int process)
{
	if(processLabel)
	{
		char buf[64];
		memset(buf,0,sizeof(buf));
		sprintf(buf,"Loading%d \%",process);
		processLabel->setString(buf);
		processLabel->visit();
	}
	visit();
}
NAMESPACE_ZJG_END