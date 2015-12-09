#ifndef __INFOTOJAVA__
#define __INFOTOJAVA__
#include "SConfig.h"
#define RCODE_OK 1
#define RCODE_ERROR  2
class InfoToJava
{
public:

	InfoToJava(void);
	~InfoToJava(void);
	static InfoToJava* sender;
	static InfoToJava* sharedSender();
	void chargeCallBack(int valueS);//短信发送完成后回调
	void sendInfo(int v);
	void onBackKeyDown(int v);
	void infoFramAndroid(int type,int code);
	bool isNewDay;
	bool musicOn;
};
#define m_sendor InfoToJava::sharedSender()
#endif
