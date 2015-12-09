#ifndef _X_HERO__
#define _X_HERO__
#include "SConfig.h"
NAMESPACE_ZJG_BEGIN
#define HERO_ST_STAND 0//’æ¡¢
#define HERO_ST_DIE 1//À¿Õˆ
class ZHero
{
public:
	ZHero();
	~ZHero();
	void setState(int state);

	void destroy();

	void update(float t);

};
NAMESPACE_ZJG_END
#endif