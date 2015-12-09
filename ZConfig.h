#pragma once;

#include "SConfig.h"
#include "DataInputStream.h"
#include "MRecord.h"


//������Ϣ;
#define VIEW_HEIGHT 1280
#define VIEW_WIDTH 720
//�������;
#define ROW_MAX 16
//�������;
#define COLUMN_MAX 9
//ÿ�����ӵı߳�;
#define ZC_RECTSIZE 80.0
//���пɹ�������;
#define ALLOBJECTARRY Mytarget::targetArray
//======================
//   ������;
//======================

//�ʹ�����;
#define ZC_FOOTMAN_COUNT (14)
//�ʹ�װ������;
#define ZC_FOOTMAN_EQUIPMENTCOUNT (4)


enum
{
	CORNUCOPIA = -5,	//��ͼʶ��:�۱���;
	FOURTOWER,			//��ͼʶ��:�ĸ���;
	EMPTY,				//��ͼʶ��:�ս���;
	BOMB,				//��ͼʶ��:ը��;
	RANDOM,				//��ͼʶ��:�������;
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
//   �˺�����;
//======================
enum
{
	KHARTSTYLE_AD,  //�����˺�;
	KHARTSTYLE_AP,  //ħ���˺�;
	KHARTSTYLE_CHAOS,	//�����˺�;
	KHARTSTYLE_SACRED,	//��ʥ�˺�;
};


//======================
//   �ӵ�����;
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
//��Ҫ����Դ;
#define BULLET_7_0  "tced1.png"
#define BULLET_7_1  "tceb1.png" 
#define BULLET_7_2  "tceb3.png"

#define BULLET_8    "skill1.png"
#define BULLET_9    "line.png"


//�ӵ�����;
#define FEEDBACK_0 "fankui01.png"
#define FEEDBACK_1 "fankui02.png"
#define FEEDBACK_FIRE_0 "fire_fankui0.png"
#define FEEDBACK_FIRE_1 "fire_fankui1.png"


//======================
//  ǿ������;
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
	OrientationShot,//�������;
	GoalShot,		//Ŀ�����;
	Particle,		//�����ӵ�;
};

//======================
//   �ϰ���͹�������;
//======================

//���й���ͽ�����ê��;
#define ZC_ATKABLE_ANCHOR ccp(0.5,0)

//��������� ����/����/����;
enum objType
{
	OBJ_MONSTER,
	OBJ_OBSTACLE,
	OBJ_SPECIAL,

};

//�����Debuff
enum MONSTER_STATUS
{
	STATUS_NORMAL = 0,	// ����;
	STATUS_ICE ,		// ����;
	STATUS_MUCUS ,		// ����ճҺ;

	//����;
};


#define Slush_0 "tce0.png"
#define Slush_1 "tce1.png"
#define IceBox  "ice.png"


//======================
//   ��ͼ;
//======================
#define BGImage1 "tmx/bg12.png"
#define	BGImage2 "tmx/bg2.png"
#define	BGImage3 "tmx/bg3.png"
#define	BGImage4 "tmx/bg4.png"


//======================
//   ����;
//======================

#define FLog(a) CCLog(#a##":%f",a);
#define ILog(a) CCLog(#a##":%d",a);
#define ELog(a) CCLog(#a##"is error");
#define FUNELog CCLog("%s",__FUNCTION__);
#define PLog(pot) CCLog(#pot##"(%f,%f)",pot.x,pot.y);

//======================
//   ����;
//======================

//��Ϣ·��;
#define DPATH_BUILD "data/Bulidings.bin"
#define DPATH_FOOTMAN "data/Footman.bin"
#define DPATH_DEMON "data/demo.bin"
#define DPATH_EQUIP "data/Equip.bin"
#define DPATH_EQUIPMENT "data/Equipment.bin"
#define DPATH_TOWERFORMAP "data/towerSort.bin"
#define DPATH_RUNE "data/Rune.bin"
#define DPATH_DEMONFORMAP "data/DemonForLevel.bin"

//�յ���������;
#define MAX_GUAIDIAN (50)

//��Ϣ��������;
#define DCOUNT_BUILD (3)
#define DCOUNT_FOOTMAN (8)
#define DCOUNT_DEMON (6)
#define DCOUNT_EQUIP (5)
#define DCOUNT_EQUIPMENT (10)
#define DCOUNT_TOWERFORMAP (9)
#define DCOUNT_RUNE (4)
#define DCOUNT_DEMONFORMAP (6)