#pragma once;

#include "SConfig.h"
#include "DataInputStream.h"
#include "MRecord.h"


//基础信息;
#define VIEW_HEIGHT 1280
#define VIEW_WIDTH 720
//最大行数;
#define ROW_MAX 16
//最大列数;
#define COLUMN_MAX 9
//每个格子的边长;
#define ZC_RECTSIZE 80.0
//所有可攻击对象;
#define ALLOBJECTARRY Mytarget::targetArray
//======================
//   塔类型;
//======================

//仆从数量;
#define ZC_FOOTMAN_COUNT (14)
//仆从装备数量;
#define ZC_FOOTMAN_EQUIPMENTCOUNT (4)


enum
{
	CORNUCOPIA = -5,	//地图识别:聚宝盆;
	FOURTOWER,			//地图识别:四格奖励;
	EMPTY,				//地图识别:空奖励;
	BOMB,				//地图识别:炸弹;
	RANDOM,				//地图识别:随机奖励;
	TOWER0,
	TOWER1,
	TOWER2,
	TOWER3,
	TOWER4,
	TOWER5,
	TOWER6,
	TOWER7,
	TOWER8,
	TOWER9
};

//======================
//   伤害类型;
//======================
enum
{
	KHARTSTYLE_AD,  //物理伤害;
	KHARTSTYLE_AP,  //魔法伤害;
	KHARTSTYLE_CHAOS,	//混乱伤害;
	KHARTSTYLE_SACRED,	//神圣伤害;
};


//======================
//   子弹类型;
//======================


#define BULLET_0    "bullet0.png"
#define BULLET_1_0  "tced1.png"
#define BULLET_1_1  "tceb1.png" 
#define BULLET_1_2  "tceb3.png"
#define BULLET_2_0  "bullet2.png"
#define BULLET_2_1  "bullet21.png"
#define BULLET_2_2  "bullet22.png"
#define BULLET_3_1  "star_01.png"
#define BULLET_3_2  "star_02.png"
#define BULLET_3_3  "star_03.png"
#define BULLET_3_4  "star_04.png"
#define BULLET_3_5  "star_05.png"
#define BULLET_3_6  "star_06.png"
#define BULLET_4    "fire.png"
#define BULLET_5	"spine.png"
#define BULLET_6_0  "fanwei.png"
//需要新资源;
#define BULLET_7_0  "tced1.png"
#define BULLET_7_1  "tceb1.png" 
#define BULLET_7_2  "tceb3.png"

#define BULLET_8    "skill1.png"
#define BULLET_9    "line.png"


//子弹反馈;
#define FEEDBACK_0 "fankui01.png"
#define FEEDBACK_1 "fankui02.png"
#define FEEDBACK_FIRE_0 "fire_fankui0.png"
#define FEEDBACK_FIRE_1 "fire_fankui1.png"


//======================
//  强化类型;
//======================
enum Intensify
{
	kIntensifySort_Tower0,
	kIntensifySort_Tower1,
	kIntensifySort_Tower2,
	kIntensifySort_Tower3,
	kIntensifySort_Tower4,
	kIntensifySort_Tower5,
	kIntensifySort_Tower6,
	kIntensifySort_Tower7,
	kIntensifySort_Tower8,
	kIntensifySort_Tower9,
};

#define PI 3.14159265
#define BUTARRAY BulletBasic::BulletArray
#define REMOVE_SELF CCRemoveSelf::create()

enum FeedBack
{
	FB_NORAML,
	FB_FIRE,
};

enum
{
	BULLET0,
	BULLET1,
	BULLET2,
	BULLET3,
	BULLET4,
	BULLET5,
	BULLET6,
	BULLET7,
	BULLET8,
	BULLET9
};
enum 
{
	OrientationShot,//定向射击;
	GoalShot,		//目标射击;
	Particle,		//粒子子弹;
};

//======================
//   障碍物和怪物类型;
//======================

//所有怪物和建筑的锚点;
#define ZC_ATKABLE_ANCHOR ccp(0.5,0)

//对象的种类 怪物/建筑/特殊;
enum objType
{
	OBJ_MONSTER,
	OBJ_OBSTACLE,
	OBJ_SPECIAL,

};

//怪物的Debuff
enum MONSTER_STATUS
{
	STATUS_NORMAL = 0,	// 正常;
	STATUS_ICE ,		// 冰冻;
	STATUS_MUCUS ,		// 青蛙粘液;

	//……;
};


#define Slush_0 "tce0.png"
#define Slush_1 "tce1.png"
#define IceBox  "ice.png"


//======================
//   地图;
//======================
#define BGImage1 "tmx/bg12.png"
#define	BGImage2 "tmx/bg2.png"
#define	BGImage3 "tmx/bg3.png"
#define	BGImage4 "tmx/bg4.png"


//======================
//   工具;
//======================

#define FLog(a) CCLog(#a##":%f",a);
#define ILog(a) CCLog(#a##":%d",a);
#define ELog(a) CCLog(#a##"is error");
#define FUNELog CCLog("%s",__FUNCTION__);
#define PLog(pot) CCLog(#pot##"(%f,%f)",pot.x,pot.y);

//======================
//   数据;
//======================

//信息路径;
#define DPATH_BUILD "data/Bulidings.bin"
#define DPATH_FOOTMAN "data/Footman.bin"
#define DPATH_DEMON "data/demo.bin"
#define DPATH_EQUIP "data/Equip.bin"
#define DPATH_EQUIPMENT "data/Equipment.bin"
#define DPATH_TOWERFORMAP "data/towerSort.bin"
#define DPATH_RUNE "data/Rune.bin"
#define DPATH_DEMONFORMAP "data/DemonForLevel.bin"

//拐点的最大数量;
#define MAX_GUAIDIAN (50)

//信息数据行数;
#define DCOUNT_BUILD (3)
#define DCOUNT_FOOTMAN (8)
#define DCOUNT_DEMON (6)
#define DCOUNT_EQUIP (5)
#define DCOUNT_EQUIPMENT (10)
#define DCOUNT_TOWERFORMAP (9)
#define DCOUNT_RUNE (4)
#define DCOUNT_DEMONFORMAP (6)