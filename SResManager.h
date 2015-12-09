#ifndef __SRESMANAGER___
#define  __SRESMANAGER___
#include "DataInputStream.h"
#include "XAnimation/XAnimation.h"
#include "XAnimation/XFrame.h"
#include "SConfig.h"
#define ANI_FILE_DIR	"animations"
#define UI_FILE_DIR		"ui"
#define CONFIGFILE		"config.bin"
USING_SG_GAME;
class SResManager
{
public:
	SResManager(void);
	~SResManager(void);
public :
	bool    allowAcceptPoint;//能接收触摸
	int		textureCount;//纹理数量
	int		aniCount;//动画数量
	int		uicouunt;//ui数量
	array1(XAnimation*) animations;//所有的动画
	array1(XAnimation*) gameui;//所有UI
	array1(XAnimation*) ui_added;//当前增加的UI
	array1(XAnimation*) ui_animations;//所有动画展示
	CCDictionary *uistrings;//UI文字
	void loadResConfig();
	void string_replace(string&str,const string&needReplaceStr,const string&rtarget);
	XAnimation* loadAnimation(int aniID,bool isUIFrame);
	XAnimation* createAAnimation(int aniID);
	void loadAnimation(DataInputStream* dis,XAnimation* ani,int fpIndex,bool isUIFrame);
	void loadATexture(int textureID,bool isUIFrame);
	void ZUI_show_needRemoved(CCNode* node,int aniID,int frameID,int blockID);
	void ZUI_show_needRemoved(CCNode* node,int aniID,int frameID,int blockID,int flagID);
	void ZUI_show_needRemovedByPosition(CCNode* node,int frameID,float x,float y);
	void ZUI_addAFrame(int frameId,float x,float y);
	void ZUI_doMove(int frameId,int blockId,float x,float y);
	void ZUI_show(CCNode* node,int frameId,bool fillalpha,float x,float y,bool canPointOther);
	void ZUI_show(CCNode* node,int frameId,bool fillalpha,float x,float y,bool canPointOther,int zOrder);
	void ZUI_showForText(CCNode* node,int frameId,bool fillalpha,float x,float y,bool canPointOther);
	void ZUI_show(CCNode* node,int frameId,bool fillalpha);
	void ZUI_show(CCNode* node,int frameId,bool fillalpha,int zOrder);
	void ZUI_removeAFrame(int frameId);
	void ZUI_update();
	void ZUI_deleteAFrame(int frameId);
	void ZUI_setClickListener(CCObject* sender,int frameID,int blockID,ZUI_ClickEvent listener);
	void ZUI_SetFrameButtonsListener(CCObject* sender,int frameID,ZUI_ClickEventByID listener);
	void ZUI_setStateChangedListener(CCObject* sender,int frameID,int blockID,ZUI_StateChangedEvent listener);
	void ZUI_setNumForNumbar(int frameID,int blockID,float num);
	void ZUI_setNumForNumbar(int frameID,int blockID,string num);
	void ZUI_setNumForNumbar_LL(int frameID,int blockID,unsigned long long num);
	void ZUI_setValueForScrollBar(int frameID,int blockID,int num);

	CCSize ZUI_getSize(int frameID, int blockID);
	void ZUI_setScale(int frameID,float scaleX,float scaleY);
	void ZUI_setScale(int frameID,int blockID,float scaleX,float scaleY);
	void ZUI_setStateForControl(int frameID,int blockID,int state);
	void ZUI_setValueChangedListener(CCObject* sender,int frameID,int blockID,ZUI_ValueChangedEvent listener);
	void ZUI_setProgressTimer(int frameID,int blockID,CCProgressTimerType type,float duration, float fFromPercentage, float fToPercentage,bool ReverseProgress,SEL_CallFuncN selector);
	void ZUI_stopProgress(int frameID,int blockID);
	void ZUI_setVisiable(int frameID,int blockID,bool visiable);
	void ZUI_setVisiableForBone(XFrame* frame,int blockID,bool visiable);
	bool ZUI_ButtonPressed(int frameID,int blockID);
	void ZUI_setButtonState(int frameID,int blockID,int state);
	void ZUI_setOpticity(int frameID,int opcity);
	void ZUI_showAnimation(CCNode* node,int aniID,float x,float y,bool removedAtOver, int zorder = 0);

	void ZUI_setText(int frameID,int blockID,string text);
	void ZUI_setTextBySelf(int frameID,int blockID);
	void ZUI_removeAnimation(int aniID);
	void ZUI_setDelayTime(int frameID,int dt);
	void ZUI_setCheckBoxState(int frameID,int blockID,bool state);
	void ZUI_setCheckBoxStateChangedListener(CCObject* sender,int frameID,int blockID,ZUI_StateChangedEvent listener);
	void ZUI_setFrameStartFP(int frameID,int startFp);
	void ZUI_SETPosition(int frameID,int x,int y);
	void ZUI_SetBlockPosition(int frameID,int blockID,float x,float y);
	
	string ZUI_getText(int frameID,int blockID);

	CCPoint getPosition(int frameID,int blockID);
	bool touchInBlock(int frameID,int blockID,float x,float y);
	int getBlockZorder(int frameID,int blockID);
	void changeSkin(int frameID,int blockID,char*path);
	void changeEquip(int frameID,int blockID,int equipIndex);
	void changeTextureForButton(int frameID,int blockID,char*path,int type);
	bool isChecked(int frameID,int blockID);
	bool canAcceptPoint();//可以接受触摸
	array1(int) getCurFrames();
	void playButtonMusic(int musicID);
public:
	XAnimation* getAnimation(int animationId);
public:
	float touch_x;
	float touch_y;
	void ccTouchesBegan(float x,float y);  
	void ccTouchesMoved(float x,float y);  
	void ccTouchesEnded(float x,float y);  
	void ccClickedEnded(float x,float y);  
};
#endif