#include "SMainMenu.h"
#include "GameState.h"
#include "XFrameID.h"
#include "Tools.h"
#include "InfoToJava.h"
#include "XAnimationID.h"
#include "SimpleAudioEngine.h"
//#include "../Game_Analytics_SDK_Cocos_3/include/TalkingData.h"
using namespace CocosDenshion;

SMainMenu* SMainMenu::game_mainmenu;

SMainMenu::SMainMenu()
{
//	initRes();
	/*CCSprite* SP = CCSprite::create("nmf.png");
	SP->setPosition(ccp(100,100));
	this->addChild(SP);*/
	preUiState = 0;
	uiState = 0;
	offX = 0.0f;
	posX = 0.0f;
	isTouched = true;
	changeDelay = 0;
	bBeClicked = true;
	int processDelay = 0;
	bToSelection = false;
	bTouchMoving = false;
}

SMainMenu::~SMainMenu()
{
}

void SMainMenu::initRes()
{

	if (preUiState == UISTATE_SELECTION)
	{
		// 播放动画
		m_gameRes->ZUI_showAnimation(this, fengmian_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
		m_gameRes->ZUI_showAnimation(this, fengmian_1, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
		m_gameRes->ZUI_showAnimation(this, fengye_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
	}

	switch (uiState)
	{
	case UISTATE_MENU:
		initMainMenu();
		break;
	case UISTATE_SELECTION:
		initSelection();
		break;
	}
}

void SMainMenu::initMainMenu()
{
	// 播放动画
	m_gameRes->ZUI_showAnimation(this, fengmian_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
	m_gameRes->ZUI_showAnimation(this, fengmian_1, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
	m_gameRes->ZUI_showAnimation(this, fengye_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
//	m_gameRes->ZUI_showAnimation(this, dianjipingmujixu, m_gamestate->curScreenW/2, m_gamestate->curScreenH/5, false);

	// 显示UI界面
	m_gameRes->ZUI_show(this, Frame_fengmian, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false, 10000);
	m_gameRes->ZUI_show(this, Frame_LOGO, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, true, 10001);
	
	// 注册按钮点击事件
	m_gameRes->ZUI_setClickListener(this, Frame_fengmian, Frame_fengmian_or_11, toucheventselector(SMainMenu::fenmain_PopMenu_click));
	m_gameRes->ZUI_setClickListener(this, Frame_fengmian, Frame_fengmian_or_13, toucheventselector(SMainMenu::fenmain_PushMenu_click));
	
	// 播放BGM
	m_gamestate->playBGM(BGM_MAINMENU);
}

void SMainMenu::initSetting()
{
	m_gameRes->ZUI_show(this, Frame_shezhi, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false, 10003);

	m_gameRes->ZUI_setCheckBoxState(Frame_shezhi, Frame_shezhi_or_22, true);
	m_gameRes->ZUI_setCheckBoxState(Frame_shezhi, Frame_shezhi_or_24, true);

	m_gameRes->ZUI_setClickListener(this, Frame_shezhi, Frame_shezhi_or_6, toucheventselector(SMainMenu::shezhi_Close_click));
	m_gameRes->ZUI_setValueChangedListener(this, Frame_shezhi, Frame_shezhi_or_20, valuechangedventselector(GameState::music_ValueChanged));
	m_gameRes->ZUI_setValueChangedListener(this, Frame_shezhi, Frame_shezhi_or_21, valuechangedventselector(GameState::music_effect_ValueChanged));
	m_gameRes->ZUI_setCheckBoxStateChangedListener(this, Frame_shezhi, Frame_shezhi_or_22, statechangedventselector(SMainMenu::shezhi_Music_checked));
	m_gameRes->ZUI_setCheckBoxStateChangedListener(this, Frame_shezhi, Frame_shezhi_or_24, statechangedventselector(SMainMenu::shezhi_Effect_checked));
}

void SMainMenu::initHelp()
{
	m_gameRes->ZUI_show(this, Frame_bangzhuguanyu, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false, 10003);

	m_gameRes->ZUI_setClickListener(this, Frame_bangzhuguanyu, Frame_bangzhuguanyu_or_2, toucheventselector(SMainMenu::help_Close_click));
}

void SMainMenu::initSelection()
{
	// 加载动画
	//m_gameRes->ZUI_showAnimation(this, fengmian_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
	//m_gameRes->ZUI_showAnimation(this, fengmian_1, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
	//m_gameRes->ZUI_showAnimation(this, fengye_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
	//	m_gameRes->ZUI_showAnimation(this, dianjipingmujixu, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);

	// 初始化选关界面
	float width = m_gamestate->curScreenW;
	selectFramesID[0] = Frame_xuanguan;
	selectFramesID[1] = Frame_xuanguan1;
	selectFramesID[2] = Frame_xuanguan2;
	selectFramesID[3] = Frame_xuanguan3;

	for (int i = 0; i < sizeof(selectFramesID)/sizeof(selectFramesID[0]); ++i)
	{
		m_gameRes->ZUI_show(this, selectFramesID[i], false, m_gamestate->curScreenW/2 + width*i, m_gamestate->curScreenH/2, true, 10000);
	}
	m_gameRes->ZUI_show(this, Frame_xuanguanfanhui, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, true, 10001);

	// 设置位置
	if (preUiState = UISTATE_MENU)
	{
		offX = 0;
	}
	for (int i = 0; i < sizeof(selectFramesID)/sizeof(selectFramesID[0]); ++i)
	{			
		if (getFramePosion(selectFramesID[i]).x > i * m_gamestate->curScreenW + m_gamestate->curScreenW/2)
		{
			offX = 0.0f;
			m_gameRes->ZUI_SETPosition(selectFramesID[i], i * m_gamestate->curScreenW + m_gamestate->curScreenW/2, m_gamestate->curScreenH/2);
		}
		else if (getFramePosion(selectFramesID[i]).x < (i - 3) * m_gamestate->curScreenW + m_gamestate->curScreenW/2)
		{
			offX = (i - 3) * m_gamestate->curScreenW;
			m_gameRes->ZUI_SETPosition(selectFramesID[i], (i - 3) * m_gamestate->curScreenW + m_gamestate->curScreenW/2, m_gamestate->curScreenH/2);
		}
		else
		{
			m_gameRes->ZUI_SETPosition(selectFramesID[i], i * m_gamestate->curScreenW + m_gamestate->curScreenW/2 + offX, m_gamestate->curScreenH/2);
		}
	}


	// 设置是否可点击
//	m_gamestate->levelInfo[LEVEL_PROCESS] = 40;//xs_test
	int lv = m_gamestate->levelInfo[LEVEL_PROCESS];
	lv = MAX_LEVEL;
	if (lv < 1)
	{
		lv = 1;
	}
	if (lv > MAX_LEVEL)
	{
		lv = MAX_LEVEL;
	}
	int closeBtn = lv%10;
	switch (lv/10)
	{
	case 0:
		setButtonVisable(Frame_xuanguan, Frame_xuanguan_or_671,Frame_xuanguan_or_671 + closeBtn, Frame_xuanguan_or_680, false);
		setButtonVisable(Frame_xuanguan1,Frame_xuanguan1_or_673, Frame_xuanguan1_or_673, Frame_xuanguan1_or_682, false);
		setButtonVisable(Frame_xuanguan2,Frame_xuanguan2_or_770, Frame_xuanguan2_or_770, Frame_xuanguan2_or_779, false);
		setButtonVisable(Frame_xuanguan3,Frame_xuanguan3_or_627, Frame_xuanguan3_or_627, Frame_xuanguan3_or_636, false);
		break;
	case 1:
		setButtonVisable(Frame_xuanguan, Frame_xuanguan_or_671,Frame_xuanguan_or_680 + 1, Frame_xuanguan_or_680, false);
		setButtonVisable(Frame_xuanguan1,Frame_xuanguan1_or_673, Frame_xuanguan1_or_673 + closeBtn, Frame_xuanguan1_or_682, false);
		setButtonVisable(Frame_xuanguan2,Frame_xuanguan2_or_770, Frame_xuanguan2_or_770, Frame_xuanguan2_or_779, false);
		setButtonVisable(Frame_xuanguan3,Frame_xuanguan3_or_627, Frame_xuanguan3_or_627, Frame_xuanguan3_or_636, false);
		break;
	case 2:
		setButtonVisable(Frame_xuanguan, Frame_xuanguan_or_671,Frame_xuanguan_or_680 + 1, Frame_xuanguan_or_680, false);
		setButtonVisable(Frame_xuanguan1,Frame_xuanguan1_or_673, Frame_xuanguan1_or_682 + 1, Frame_xuanguan1_or_682, false);
		setButtonVisable(Frame_xuanguan2,Frame_xuanguan2_or_770, Frame_xuanguan2_or_770 + closeBtn, Frame_xuanguan2_or_779, false);
		setButtonVisable(Frame_xuanguan3,Frame_xuanguan3_or_627, Frame_xuanguan3_or_627, Frame_xuanguan3_or_636, false);
		break;
	case 3:
		setButtonVisable(Frame_xuanguan, Frame_xuanguan_or_671,Frame_xuanguan_or_680 + 1, Frame_xuanguan_or_680, false);
		setButtonVisable(Frame_xuanguan1,Frame_xuanguan1_or_673, Frame_xuanguan1_or_682 + 1, Frame_xuanguan1_or_682, false);
		setButtonVisable(Frame_xuanguan2,Frame_xuanguan2_or_770, Frame_xuanguan2_or_779 + 1, Frame_xuanguan2_or_779, false);
		setButtonVisable(Frame_xuanguan3,Frame_xuanguan3_or_627, Frame_xuanguan3_or_627 + closeBtn, Frame_xuanguan3_or_636, false);
		break;
	default:
		setButtonVisable(Frame_xuanguan, Frame_xuanguan_or_671,Frame_xuanguan_or_680 + 1, Frame_xuanguan_or_680, false);
		setButtonVisable(Frame_xuanguan1,Frame_xuanguan1_or_673, Frame_xuanguan1_or_682 + 1, Frame_xuanguan1_or_682, false);
		setButtonVisable(Frame_xuanguan2,Frame_xuanguan2_or_770, Frame_xuanguan2_or_779 + 1, Frame_xuanguan2_or_779, false);
		setButtonVisable(Frame_xuanguan3,Frame_xuanguan3_or_627, Frame_xuanguan3_or_636 + 1, Frame_xuanguan3_or_636, false);
		break;
	}

	// 设置星级
	for (int i = 0; i < 40; ++i)
	{
		int num = -1;
		int star = m_gamestate->levelStars[i];

		int page = Frame_xuanguan;
		if (i >= 0 && i < 10)
		{	
			page = Frame_xuanguan;
			num = i * 3 + Frame_xuanguan_or_681;
		}

		if (i >= 10 && i < 20)
		{
			page = Frame_xuanguan1;
			num = i%10 * 3 + Frame_xuanguan1_or_683;
		}

		if (i >= 20 && i < 30)
		{
			page = Frame_xuanguan2;
			num = i%10 * 3 + Frame_xuanguan2_or_780;
		}

		if (i >= 30 && i < 40)
		{
			page = Frame_xuanguan3;
			num = i%10 * 3 + Frame_xuanguan3_or_637;
		}

		int j;
		for (j = num; j < num + star; ++j)
		{
			m_gameRes->changeEquip(page, j, 1);
		}
		for (int k = j; k < 3 + num; ++k)
		{
			m_gameRes->changeEquip(page, k, 0);
		}
	}

	// 注册点击事件
	m_gameRes->ZUI_SetFrameButtonsListener(this, Frame_xuanguan, toucheventselectorById(SMainMenu::xuanguan_Select_click));
	m_gameRes->ZUI_SetFrameButtonsListener(this, Frame_xuanguan1, toucheventselectorById(SMainMenu::xuanguan1_Select_click));
	m_gameRes->ZUI_SetFrameButtonsListener(this, Frame_xuanguan2, toucheventselectorById(SMainMenu::xuanguan2_Select_click));
	m_gameRes->ZUI_SetFrameButtonsListener(this, Frame_xuanguan3, toucheventselectorById(SMainMenu::xuanguan3_Select_click));
	m_gameRes->ZUI_setClickListener(this, Frame_xuanguanfanhui, Frame_xuanguanfanhui_or_2, toucheventselector(SMainMenu::xuanguan_BackMenu_click));

	// 播放BGM
	m_gamestate->playBGM(BGM_SELECTION);
}

void SMainMenu::initProcessFrame()
{
	m_gameRes->ZUI_show(this, Frame_logoxiaoshi, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, true, 10001);
	processDelay = 20;
	bToSelection = true;
}

void SMainMenu::removeCurFrames()
{
	array1(int) frames = m_gameRes->getCurFrames();
	for (std::vector<int>::iterator iter = frames.begin(); iter != frames.end(); ++iter)
	{
		m_gameRes->ZUI_removeAFrame(*iter);
	}
}

void SMainMenu::loadSceneAnimation()
{
	switch (uiState)
	{
	case UISTATE_MENU:
		{
			// 加载动画
			m_gameRes->ZUI_showAnimation(this, fengmian_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
			m_gameRes->ZUI_showAnimation(this, fengmian_1, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
			m_gameRes->ZUI_showAnimation(this, fengye_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
//			m_gameRes->ZUI_showAnimation(this, dianjipingmujixu, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
		}
		break;
	case UISTATE_SELECTION:
		{
			// 加载动画
			m_gameRes->ZUI_showAnimation(this, fengmian_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
			m_gameRes->ZUI_showAnimation(this, fengmian_1, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
			m_gameRes->ZUI_showAnimation(this, fengye_2, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
			//m_gameRes->ZUI_showAnimation(this, dianjipingmujixu, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, false);
		}
		break;
	}
}

void SMainMenu::removeSceneAnimation()
{
	switch (uiState)
	{
	case UISTATE_MENU:
		{
////			m_gameRes->ZUI_removeAnimation(dianjipingmujixu);
//			m_gameRes->ZUI_removeAnimation(fengye_2);
//			m_gameRes->ZUI_removeAnimation(fengmian_2);
//			m_gameRes->ZUI_removeAnimation(fengmian_1);
		}
		break;
	case UISTATE_SELECTION:
		{
			//m_gameRes->ZUI_removeAnimation(dianjipingmujixu);
			m_gameRes->ZUI_removeAnimation(fengye_2);
			m_gameRes->ZUI_removeAnimation(fengmian_2);
			m_gameRes->ZUI_removeAnimation(fengmian_1);
		}
		break;
	}
}

void SMainMenu::fengmian_ChangButton()
{
	// 移动按钮
	CCPoint pt1 =  m_gameRes->getPosition(Frame_fengmian, Frame_fengmian_or_11);
	CCPoint pt2 =  m_gameRes->getPosition(Frame_fengmian, Frame_fengmian_or_13);
	m_gameRes->ZUI_doMove(Frame_fengmian, Frame_fengmian_or_11, pt2.x - pt1.x, 0);
	m_gameRes->ZUI_doMove(Frame_fengmian, Frame_fengmian_or_13, pt1.x - pt2.x, 0);
}

void SMainMenu::fenmain_PopMenu_click(CCObject*sender)
{

	if (bBeClicked)
	{
		// 弹出菜单
		m_gameRes->ZUI_show(this, Frame_anniu, false, m_gamestate->curScreenW/2, m_gamestate->curScreenH/2, true, 10002);
		m_gameRes->ZUI_setClickListener(this, Frame_anniu, Frame_anniu_or_2, toucheventselector(SMainMenu::anniu_Quit_click));
		m_gameRes->ZUI_setClickListener(this, Frame_anniu, Frame_anniu_or_3, toucheventselector(SMainMenu::anniu_Help_click));
		m_gameRes->ZUI_setClickListener(this, Frame_anniu, Frame_anniu_or_1, toucheventselector(SMainMenu::anniu_Setting_click));
		changeDelay = 0;
		bBeClicked = false;
	}
}
void SMainMenu::fenmain_PushMenu_click(CCObject*sender)
{
	// 删除菜单界面
	m_gameRes->ZUI_removeAFrame(Frame_anniu);
	// 移动按钮
	fengmian_ChangButton();
}

void SMainMenu::anniu_Quit_click(CCObject*sender)
{
	CCDirector::sharedDirector()->end();
}
void SMainMenu::anniu_Help_click(CCObject*sender)
{
	initHelp();
}
void SMainMenu::anniu_Setting_click(CCObject*sender)
{
	initSetting();
}

void SMainMenu::xuanguan_BackMenu_click(CCObject*sender)
{
	removeSceneAnimation();
	removeCurFrames();
	setUIState(UISTATE_MENU);
	initMainMenu();
}
void SMainMenu::xuanguan_Select_click(CCObject*sender, int handID)
{
	// 如果正在快速滑动，则返回
	if (bTouchMoving)
	{
		return;
	}

	int level = -1;
	level = handID - Frame_xuanguan_or_671;

	removeSceneAnimation();
	removeCurFrames();
	//m_game->setState(G_ST_LOADING);
	intoGame(level);
}
void SMainMenu::xuanguan1_Select_click(CCObject*sender, int handID)
{
	// 如果正在快速滑动，则返回
	if (bTouchMoving)
	{
		return;
	}

	int level = -1;
	level = handID - Frame_xuanguan1_or_673 + 10;

	removeSceneAnimation();
	removeCurFrames();
	m_game->setState(G_ST_LOADING);
	intoGame(level);
}
void SMainMenu::xuanguan2_Select_click(CCObject*sender, int handID)
{
	// 如果正在快速滑动，则返回
	if (bTouchMoving)
	{
		return;
	}

	int level = -1;
	level = handID - Frame_xuanguan2_or_770 + 20;

	removeSceneAnimation();
	removeCurFrames();
	m_game->setState(G_ST_LOADING);
	intoGame(level);
}
void SMainMenu::xuanguan3_Select_click(CCObject*sender, int handID)
{
	// 如果正在快速滑动，则返回
	if (bTouchMoving)
	{
		return;
	}

	int level = -1;
	level = handID - Frame_xuanguan3_or_627 + 30;

	removeSceneAnimation();
	removeCurFrames();
	//m_game->setState(G_ST_LOADING);
	intoGame(level);
}
//void SMainMenu::xuanguan4_Select_click(CCObject*sender, int handID)
//{
//	int level = -1;
//	level = handID - Frame_xuanguan4_or_7 + 20;
//
//	removeSceneAnimation();
//	removeCurFrames();
//	m_game->setState(G_ST_LOADING);
//	intoGame(level);
//}
//void SMainMenu::xuanguan5_Select_click(CCObject*sender, int handID)
//{
//	int level = -1;
//	level = handID - Frame_xuanguan5_or_7 + 25;
//
//	removeSceneAnimation();
//	removeCurFrames();
//	m_game->setState(G_ST_LOADING);
//	intoGame(level);
//}
//void SMainMenu::xuanguan6_Select_click(CCObject*sender, int handID)
//{
//	int level = -1;
//	level = handID - Frame_xuanguan6_or_7 + 30;
//
//	removeSceneAnimation();
//	removeCurFrames();
//	m_game->setState(G_ST_LOADING);
//	intoGame(level);
//}
//void SMainMenu::xuanguan7_Select_click(CCObject*sender, int handID)
//{
//	int level = -1;
//	level = handID - Frame_xuanguan7_or_7 + 35;
//
//	removeSceneAnimation();
//	removeCurFrames();
//	m_game->setState(G_ST_LOADING);
//	intoGame(level);
//}

void SMainMenu::shezhi_Close_click(CCObject*sender)
{
	m_gameRes->ZUI_removeAFrame(Frame_shezhi);
}
void SMainMenu::shezhi_Music_checked(CCObject*sender,bool checked)
{
	if (!checked)
	{
		m_gameRes->ZUI_setValueForScrollBar(Frame_shezhi, Frame_shezhi_or_20, 0);
		m_gamestate->bgmVolume = 0;
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m_gamestate->bgmVolume);
	}
	else
	{
		m_gameRes->ZUI_setValueForScrollBar(Frame_shezhi, Frame_shezhi_or_20, 50);
		m_gamestate->bgmVolume = 50/100;
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m_gamestate->bgmVolume);
	}
}
void SMainMenu::shezhi_Effect_checked(CCObject*sender,bool checked)
{
	if (!checked)
	{
		m_gameRes->ZUI_setValueForScrollBar(Frame_shezhi, Frame_shezhi_or_21, 0);
		m_gamestate->effVolume = 0;
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_gamestate->effVolume);
	}
	else
	{
		m_gameRes->ZUI_setValueForScrollBar(Frame_shezhi, Frame_shezhi_or_21, 50);
		m_gamestate->effVolume = 50/100;
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_gamestate->effVolume);
	}
}

void SMainMenu::help_Close_click(CCObject*sender)
{
	m_gameRes->ZUI_removeAFrame(Frame_bangzhuguanyu);
}

SMainMenu* SMainMenu::shareMainMenu()
{
	if(game_mainmenu == NULL)
	{
		game_mainmenu = new SMainMenu();
	}
	return game_mainmenu;
}

bool SMainMenu::canBeTouched(int x, int y)
{
	array1(int) frames = m_gameRes->getCurFrames();
	bool flag = true;

	switch (uiState)
	{
	case UISTATE_MENU:
		for (std::vector<int>::iterator iter = frames.begin(); iter != frames.end(); ++iter)
		{
			if (*iter == Frame_fengmian && (m_gameRes->touchInBlock(Frame_fengmian, Frame_fengmian_or_11, x, y) 
				|| m_gameRes->touchInBlock(Frame_fengmian, Frame_fengmian_or_13, x, y)))
			{
				flag = false;
			}
			if (*iter == Frame_anniu && (m_gameRes->touchInBlock(Frame_anniu, Frame_anniu_or_1, x, y)
				|| m_gameRes->touchInBlock(Frame_anniu, Frame_anniu_or_3, x, y) 
				|| m_gameRes->touchInBlock(Frame_anniu, Frame_anniu_or_2, x, y)))
			{
				flag = false;
			}
			if (*iter == Frame_shezhi/* && (m_gameRes->touchInBlock(Frame_shezhi, Frame_shezhi_or_6, x, y)
				|| m_gameRes->touchInBlock(Frame_shezhi, Frame_shezhi_or_11, x, y) 
				|| m_gameRes->touchInBlock(Frame_shezhi, Frame_shezhi_or_12, x, y)
				|| m_gameRes->touchInBlock(Frame_shezhi, Frame_shezhi_or_13, x, y)
				|| m_gameRes->touchInBlock(Frame_shezhi, Frame_shezhi_or_14, x, y))*/)
			{
				flag = false;
			}
			if (*iter == Frame_bangzhuguanyu/* && (m_gameRes->touchInBlock(Frame_bangzhuguanyu, Frame_bangzhuguanyu_or_2, x, y))*/)
			{
				flag = false;
			}
		}
		break;
	case UISTATE_SELECTION:
		/*for (std::vector<int>::iterator iter = frames.begin(); iter != frames.end(); ++iter)
		{
			if (m_gameRes->touchInBlock(Frame_fengmian, Frame_fengmian_or_1, x, y))
			{
				flag = false;
				break;
			}
		}*/
		break;
	}

	return flag;
}

CCPoint SMainMenu::getFramePosion(int frameID)
{
	for (int i = 0; i < sizeof(selectFramesID)/sizeof(selectFramesID[0]); ++i)
	{
		if (selectFramesID[i] == frameID)
		{
			return ccp(i * m_gamestate->curScreenW + m_gamestate->curScreenW/2 + offX, m_gamestate->curScreenH/2);
		}
	}

	return ccp(0,0);
}

void SMainMenu::selectTouchMoveTo(int x, int y)
{
	// 如果是开始点击，则出初始化位置
	if (isTouched)
	{
		posX = x;
		isTouched = false;
	}
	// 偏移量增加
	offX += (x - posX);

	if (x - posX > 3)
	{
		bTouchMoving = true;
	}
	else
	{
		bTouchMoving = false;
	}

	for (int i = 0; i < sizeof(selectFramesID)/sizeof(selectFramesID[0]); ++i)
	{			
		if (getFramePosion(selectFramesID[i]).x > i * m_gamestate->curScreenW + m_gamestate->curScreenW/2)
		{
			offX = 0.0f;
			m_gameRes->ZUI_SETPosition(selectFramesID[i], i * m_gamestate->curScreenW + m_gamestate->curScreenW/2, m_gamestate->curScreenH/2);
		}
		else if (getFramePosion(selectFramesID[i]).x < (i - 3) * m_gamestate->curScreenW + m_gamestate->curScreenW/2)
		{
			offX = (i - 3) * m_gamestate->curScreenW;
			m_gameRes->ZUI_SETPosition(selectFramesID[i], (i - 3) * m_gamestate->curScreenW + m_gamestate->curScreenW/2, m_gamestate->curScreenH/2);
		}
		else
		{
			m_gameRes->ZUI_SETPosition(selectFramesID[i], i * m_gamestate->curScreenW + m_gamestate->curScreenW/2 + offX, m_gamestate->curScreenH/2);
		}
	}
	posX = x;
}

void SMainMenu::touchBegin(float x,float y)
{
	switch (uiState)
	{
	case 0:
		// 在UI按钮上不能触摸
		if (canBeTouched(x, y))
		{
			removeSceneAnimation();
			removeCurFrames();
			m_gameRes->ZUI_removeAFrame(Frame_fengmian);
			setUIState(UISTATE_SELECTION);
			initProcessFrame();
		}
		break;
	case 1:
		break;
	default:
		break;
	}
}
void SMainMenu::touchMoved(float x,float y)
{
	switch (uiState)
	{
	case 1:
		selectTouchMoveTo(x, y);
		break;
	default:
		break;
	}
}
void SMainMenu::touchEnded(float x,float y)
{
	switch (uiState)
	{
	case 1:
		isTouched = true;
		//intoSelection();
		break;
	default:
		break;
	}
}

void SMainMenu::intoGame(int sceneType)
{
	m_gamestate->curLevel = sceneType;
	m_gamestate->setState(GST_GAMEING,-1);
	m_gamestate->addTalkingEvent(GameState::event_toLevel);
}

void SMainMenu::update()
{
	m_gameRes->ZUI_update();
	
	if (!bBeClicked)
	{
		changeDelay++;
	}
	if (changeDelay >= 6)
	{
		fengmian_ChangButton();
		changeDelay = 0;
		bBeClicked = true;
	}


	if (bToSelection)
	{
		processDelay--;
		if (processDelay <= 0)
		{
			setUIState(UISTATE_SELECTION);
			initSelection();
			bToSelection = false;
			processDelay = 20;
		}
	}
}

void SMainMenu::setButtonVisable(int frameID,int startBlock, int startID, int endID, bool isVisable)
{
	//if (startID > endID)
	//	return;
	for (int i = startBlock; i < startID; i++)
	{
		m_gameRes->ZUI_setStateForControl(frameID, i, BTN_ST_NOR);
	}
	for (int i = startID; i <= endID; i++)
	{
		m_gameRes->ZUI_setStateForControl(frameID, i, BTN_ST_DIS);
	}
}