#ifndef ZACTORCLASS____
#define ZACTORCLASS____
#include "SConfig.h"

NAMESPACE_ZJG_BEGIN
/*
#define AIID_HERO			0//主角AIID

#define AIID_ENEMY		1//敌人
#define AIID_BULLTE		3//子弹
*/


//对应数据编辑器中的数据
#define kDATA_HP				0
#define kDATA_MAXHP				1
#define kDATA_MP				2
#define kDATA_MAXMP				3
#define kDATA_EXP				4
#define kDATA_PHYATK			5
#define kDATA_PHYDEF			6
#define kDATA_MAGICATK			7
#define kDATA_MAGICDEF			8//法术防御
#define kDATA_HITRATE			9//命中率
#define kDATA_JINKRATE			10//闪避率
#define kDATA_CRITRATE			11//暴击率
#define kDATA_CRITDAMAGE		12//暴击伤害
#define kDATA_PARRYRATE			13//格挡率
#define kDATA_PARRYDAMAGE		14//格挡伤害
#define kDATA_DAMAGEREDUCTION	15//伤害减免
#define kDATA_CRITDEF			16//暴击抵抗
#define kDATA_MOVESPEED			17//移动速度

#define kDATA_WEAPON_STAR		18//武器星级
#define kDATA_WEAPON_COLOR		19//武器颜色
#define kDATA_WEAPON_D_COUNT	20//武器副属性个数
#define kDATA_WEAPON_CARDCOUNT	21//武器卡槽
#define kDATA_WEAPON_CHANGE_SUIT 22//武器换装号
#define kDATA_WEAPON_SPARE0		23//备用一
#define kDATA_WEAPON_SPARE1		24//备用二

#define kDATA_DEPUTY_HP			25//副属性HP
#define kDATA_DEPUTY_MP			26//副属性MP
#define kDATA_DEPUTY_ATK		27//副属性ATK
#define kDATA_DEPUTY_DEF		28//副属性DEF
#define kDATA_DEPUTY_MAT		29//副属性MAT
#define kDATA_DEPUTY_MDF		30//副属性MDF
#define kDATA_DEPUTY_HIT		31//副属性命中
#define kDATA_DEPUTY_JINK		32//副属性闪避
#define kDATA_DEPUTY_CRITRATE	33//副属性暴击率
#define kDATA_DEPUTY_CRITDAMAGE	34//副属性暴击伤害
#define kDATA_DEPUTY_PARRYRATE	35//副属性格挡率
#define kDATA_DEPUTY_PARRYDAMAGE 36//副属性格挡伤害
//#define kDATA_DEPUTY_PARRY		37//副属性格挡力
#define kDATA_DEPUTY_REDUCTION	37//副属性伤害减免
#define kDATA_DEPUTY_CRITDEF	38//副属性暴击抵抗
#define kDATA_DEPUTY_ALLATT		39//副属性影响全属性
#define kDATA_DEPUTY_ABSHIT		40//副属性绝对命中
#define kDATA_DEPUTY_ABSJINK	41//副属性绝对闪避
#define kDATA_DEPUTY_BUFF0		42//BUFF0
#define kDATA_DEPUTY_BUFF1		43//BUFF0
#define kDATA_DEPUTY_BUFF2		44//BUFF0
#define kDATA_DEPUTY_BUFF3		45//BUFF0
#define kDATA_WEAPON_RANK		46//武器品阶
#define kDATA_WEAPON_MATT		47//主属性全属性
#define kDATA_MAXCOUNT			48//数据上限

#define kSkillWarning			kDATA_MAGICDEF	//技能提示
#define kSkillSummonCount		kDATA_PHYDEF
#define kSkillSummonInterval	kDATA_MAGICATK
#define kSkillHurtType			kDATA_MAXHP		//技能伤害类型
#define kSkillABSHurt			kDATA_MP		//技能绝对伤害
#define kSkillABSHit			kDATA_MAXMP		//技能绝对命中
#define kSkillEXAdd				kDATA_EXP		//技能基础额外伤害附加



#define kDATA_SKILL_BASE_ICON				0//关联ICON
#define kDATA_SKILL_BASE_LEVEL				1//等级
#define kDATA_SKILL_BASE_PRICE				2//价格
#define kDATA_SKILL_BASE_MP					3//mp
#define kDATA_SKILL_BASE_PROFICIENCY		4//熟练度
#define kDATA_SKILL_BASE_KEEPTIME			5//保持时间
#define kDATA_SKILL_BASE_COOLTIME			6//冷却时间
#define kDATA_SKILL_BASE_EFFSTATERATE		7//影响状态概率
#define kDATA_SKILL_BASE_ADDSTATERATE		8//附加概率
#define kDATA_SKILL_BASE_NEXTLVINDEX		9//下级
#define kDATA_SKILL_BASE_USERANI			10//使用方动画
#define kDATA_SKILL_BASE_TARGETANI			11//对方动画
#define kDATA_SKILL_BASE_TARGET				12//作用对象
#define kDATA_SKILL_BASE_TYPE				13//类型

#define kDATA_GOODS_BASE_ICON				0//关联ICON
#define kDATA_GOODS_BASE_AFFECTTIME			1//影响时间
#define kDATA_GOODS_BASE_PRICE				2//物品价格
#define kDATA_GOODS_BASE_AFFECTOBJ			3//影响对象
#define	kDATA_GOODS_BASE_TYPE				4//物品类型
#define kDATA_GOODS_BASE_MANI				5//使用方动画
#define kDATA_GOODS_BASE_EANI				6//对方动画
NAMESPACE_ZJG_END
#endif