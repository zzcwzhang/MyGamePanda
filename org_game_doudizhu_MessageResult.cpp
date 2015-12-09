#include "org_game_doudizhu_MessageResult.h"
#include "InfoToJava.h"
JNIEXPORT void JNICALL Java_org_game_doudizhu_ZJSMS_onSendMessageResult
	(JNIEnv *, jclass, jint type,jint code)
{
		CCLOG("ACCEPT_%d_%d",type,code);
	m_sendor->infoFramAndroid(type,code);
}