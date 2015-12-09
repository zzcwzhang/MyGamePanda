#include "InfoToJava.h"
#include "GameState.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台 
#include "platform/android/jni/JniHelper.h"
#endif

InfoToJava* InfoToJava::sender;
InfoToJava::InfoToJava(void)
{
}
InfoToJava* InfoToJava::sharedSender()
{
	if(sender==NULL)
	{
		sender = new InfoToJava();
		sender->isNewDay = false;
	}
	return sender;
}

InfoToJava::~InfoToJava(void)
{

}
void InfoToJava::sendInfo(int v)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台 
	CCLOG("JniMethodInfo Start");
	JniMethodInfo minfo;//定义Jni函数信息结构体 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/game/doudizhu/ZJSMS","charge","(I)V");//获取java类对象 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID,v); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
	CCLOG("jni call java complete"); 
#endif 
}
void InfoToJava::onBackKeyDown(int v)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台 
	CCLOG("JniMethodInfo Start");
	JniMethodInfo minfo;//定义Jni函数信息结构体 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/game/jqgame/ScoreManager","onBackKeyDown","(I)V");//获取java类对象 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID,v); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
	CCLOG("jni call java complete"); 
#endif 
}
void InfoToJava::infoFramAndroid(int type,int code)
{
	CCLOG("ACCEPT_%d_%d",type,code);
	m_gamestate->sendMessageResult(type,code);
	/*switch(type)
	{
	default:
		m_gamestate->sendMessageResult(type,code);
		break;
	}*/
}