#ifndef ZACTORCLASS____
#define ZACTORCLASS____
#include "SConfig.h"

NAMESPACE_ZJG_BEGIN
/*
#define AIID_HERO			0//����AIID

#define AIID_ENEMY		1//����
#define AIID_BULLTE		3//�ӵ�
*/


//��Ӧ���ݱ༭���е�����
#define kDATA_HP				0
#define kDATA_MAXHP				1
#define kDATA_MP				2
#define kDATA_MAXMP				3
#define kDATA_EXP				4
#define kDATA_PHYATK			5
#define kDATA_PHYDEF			6
#define kDATA_MAGICATK			7
#define kDATA_MAGICDEF			8//��������
#define kDATA_HITRATE			9//������
#define kDATA_JINKRATE			10//������
#define kDATA_CRITRATE			11//������
#define kDATA_CRITDAMAGE		12//�����˺�
#define kDATA_PARRYRATE			13//����
#define kDATA_PARRYDAMAGE		14//���˺�
#define kDATA_DAMAGEREDUCTION	15//�˺�����
#define kDATA_CRITDEF			16//�����ֿ�
#define kDATA_MOVESPEED			17//�ƶ��ٶ�

#define kDATA_WEAPON_STAR		18//�����Ǽ�
#define kDATA_WEAPON_COLOR		19//������ɫ
#define kDATA_WEAPON_D_COUNT	20//���������Ը���
#define kDATA_WEAPON_CARDCOUNT	21//��������
#define kDATA_WEAPON_CHANGE_SUIT 22//������װ��
#define kDATA_WEAPON_SPARE0		23//����һ
#define kDATA_WEAPON_SPARE1		24//���ö�

#define kDATA_DEPUTY_HP			25//������HP
#define kDATA_DEPUTY_MP			26//������MP
#define kDATA_DEPUTY_ATK		27//������ATK
#define kDATA_DEPUTY_DEF		28//������DEF
#define kDATA_DEPUTY_MAT		29//������MAT
#define kDATA_DEPUTY_MDF		30//������MDF
#define kDATA_DEPUTY_HIT		31//����������
#define kDATA_DEPUTY_JINK		32//����������
#define kDATA_DEPUTY_CRITRATE	33//�����Ա�����
#define kDATA_DEPUTY_CRITDAMAGE	34//�����Ա����˺�
#define kDATA_DEPUTY_PARRYRATE	35//�����Ը���
#define kDATA_DEPUTY_PARRYDAMAGE 36//�����Ը��˺�
//#define kDATA_DEPUTY_PARRY		37//�����Ը���
#define kDATA_DEPUTY_REDUCTION	37//�������˺�����
#define kDATA_DEPUTY_CRITDEF	38//�����Ա����ֿ�
#define kDATA_DEPUTY_ALLATT		39//������Ӱ��ȫ����
#define kDATA_DEPUTY_ABSHIT		40//�����Ծ�������
#define kDATA_DEPUTY_ABSJINK	41//�����Ծ�������
#define kDATA_DEPUTY_BUFF0		42//BUFF0
#define kDATA_DEPUTY_BUFF1		43//BUFF0
#define kDATA_DEPUTY_BUFF2		44//BUFF0
#define kDATA_DEPUTY_BUFF3		45//BUFF0
#define kDATA_WEAPON_RANK		46//����Ʒ��
#define kDATA_WEAPON_MATT		47//������ȫ����
#define kDATA_MAXCOUNT			48//��������

#define kSkillWarning			kDATA_MAGICDEF	//������ʾ
#define kSkillSummonCount		kDATA_PHYDEF
#define kSkillSummonInterval	kDATA_MAGICATK
#define kSkillHurtType			kDATA_MAXHP		//�����˺�����
#define kSkillABSHurt			kDATA_MP		//���ܾ����˺�
#define kSkillABSHit			kDATA_MAXMP		//���ܾ�������
#define kSkillEXAdd				kDATA_EXP		//���ܻ��������˺�����



#define kDATA_SKILL_BASE_ICON				0//����ICON
#define kDATA_SKILL_BASE_LEVEL				1//�ȼ�
#define kDATA_SKILL_BASE_PRICE				2//�۸�
#define kDATA_SKILL_BASE_MP					3//mp
#define kDATA_SKILL_BASE_PROFICIENCY		4//������
#define kDATA_SKILL_BASE_KEEPTIME			5//����ʱ��
#define kDATA_SKILL_BASE_COOLTIME			6//��ȴʱ��
#define kDATA_SKILL_BASE_EFFSTATERATE		7//Ӱ��״̬����
#define kDATA_SKILL_BASE_ADDSTATERATE		8//���Ӹ���
#define kDATA_SKILL_BASE_NEXTLVINDEX		9//�¼�
#define kDATA_SKILL_BASE_USERANI			10//ʹ�÷�����
#define kDATA_SKILL_BASE_TARGETANI			11//�Է�����
#define kDATA_SKILL_BASE_TARGET				12//���ö���
#define kDATA_SKILL_BASE_TYPE				13//����

#define kDATA_GOODS_BASE_ICON				0//����ICON
#define kDATA_GOODS_BASE_AFFECTTIME			1//Ӱ��ʱ��
#define kDATA_GOODS_BASE_PRICE				2//��Ʒ�۸�
#define kDATA_GOODS_BASE_AFFECTOBJ			3//Ӱ�����
#define	kDATA_GOODS_BASE_TYPE				4//��Ʒ����
#define kDATA_GOODS_BASE_MANI				5//ʹ�÷�����
#define kDATA_GOODS_BASE_EANI				6//�Է�����
NAMESPACE_ZJG_END
#endif