#include "SStartPage.h"
#include "SimpleAudioEngine.h"  
#include "SResManager.h"
#include "XFrameID.h"
#include "GameState.h"
#include "Tools.h"
#include "SResManager.h"
#include "XAnimationID.h"
#include "InfoToJava.h"
using namespace CocosDenshion;  
SStartPage::SStartPage()
{
	loadMusic = true;
	loadMusicOver = false;
}
SStartPage::~SStartPage()
{
}
void SStartPage::update()
{
	m_gameRes->ZUI_update();
	if(loadMusic)
	{
		loadMusic = false;
		initMusic();
	}
	if(loadMusicOver)
	{
		loadMusicOver = false;
		enterGame();
	}
}
void SStartPage::enterGame()
{
	m_gamestate->intoNextState(GST_MAINMENU,1);
}
void SStartPage::initMusic()
{
	loadMusicOver = true;
}
/*void SStartPage::initRes()
{
	for(int i = 0;i<=Frame_xingbie;i++)
	{
		m_gameRes->loadAnimation(i,true);
		process++;;
	}
}*/