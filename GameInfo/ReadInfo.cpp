#include "GameInfo/ReadInfo.h"

ReadInfo* ReadInfo::instance = new ReadInfo();
ReadInfo* ReadInfo::getInstance()
{
	//if (instance == NULL)
	//{
	//	instance = new ReadInfo;

	//	instance->ReadData();
	//	instance->ReadUserEquipment();
	//}
	instance->ReadData();
	instance->ReadUserEquipment();

	return instance;
}

void ReadInfo::ReadData()
{


	//建筑信息;
	ReadArray(DPATH_BUILD,buildarray,DCOUNT_BUILD);

	ReadArray(DPATH_FOOTMAN,footmanarray,DCOUNT_FOOTMAN);

	//ReadArray(DPATH)
	do 
	{
		//读取恶魔信息;
		DataInputStream* dis = DataInputStream::openFile("data/demo.bin","rb");
		int count = dis->readShort();
		demonarray.resize(count);
		for (int i = 0; i < count; ++i)
		{
			dis->readAString();
			demonarray[i].resize(DCOUNT_DEMON);
			for (int j = 0; j < demonarray[i].size(); j++)
			{
				demonarray[i][j]	= dis->readInt()/100;
			}
			//for (int j = 0;j<DCOUNT_DEMON;j++)
			//{
			//	
			//	int un = (int)demonarray[i][j];
			//	CCLog("un %d",un);
			//}
		}
		DataInputStream::closeFile(dis);
	} while (0);

	do 
	{
		//读取装备配置信息;
		DataInputStream* dis = DataInputStream::openFile("data/Equip.bin","rb");
		int count = dis->readShort();
		equiparray.resize(count);
		for (int i = 0; i < count; ++i)
		{
			dis->readAString();
			equiparray[i].resize(DCOUNT_EQUIP);
			for (int j = 0; j < equiparray[i].size(); j++)
			{
				equiparray[i][j]	= dis->readInt()/100;
			}

		}
		DataInputStream::closeFile(dis);
	} while (0);

	do 
	{
		//读取装备信息;
		DataInputStream* dis = DataInputStream::openFile("data/Equipment.bin","rb");
		int count = dis->readShort();
		equipmentarray.resize(count);
		for (int i = 0; i < count; ++i)
		{
			dis->readAString();
			equipmentarray[i].resize(DCOUNT_EQUIPMENT);
			for (int j = 0; j < equipmentarray[i].size(); j++)
			{
				equipmentarray[i][j]	= dis->readInt()/100;
			}
			//for (int j = 0;j<DCOUNT_EQUIPMENT;j++)
			//{
			//	ILog(equipmentarray[i][j]);
			//}

		}
		DataInputStream::closeFile(dis);
	} while (0);


	//读取关卡配置信息;
	ReadArray(DPATH_TOWERFORMAP,towerSortForMap,DCOUNT_TOWERFORMAP);
	//读取符文信息;
	ReadArray(DPATH_RUNE,Runearray,DCOUNT_RUNE);

	//读取怪物关卡配置;
	ReadArray(DPATH_DEMONFORMAP,demonForMap,DCOUNT_DEMONFORMAP);
}

void ReadInfo::ReadUserEquipment()
{
	int id;
	for (id= 0;id<ZC_FOOTMAN_COUNT;id++)
	{
		for (int i = 0 ;i<ZC_FOOTMAN_EQUIPMENTCOUNT;i++ )
		{
			char str[256];
			sprintf(str,"footman_%d_%d",id+1,i);
			//CCLog(str);
			UserEquiparray[id][i] = CCUserDefault::sharedUserDefault()->getIntegerForKey(str);
		}
	}
}

void ReadInfo::ReadArray( const char* path,array2(int)& vec2,int dataCount )
{
	do 
	{
		//读取装备信息;
		DataInputStream* dis = DataInputStream::openFile(path,"rb");
		int count = dis->readShort();
		vec2.resize(count);
		for (int i = 0; i < count; ++i)
		{
			dis->readAString();
			vec2[i].resize(dataCount);
			for (int j = 0; j < vec2[i].size(); j++)
			{
				vec2[i][j]	= dis->readInt()/100;
			}

			//打印信息;
			//for (int j = 0;j<dataCount;j++)
			//{
			//	ILog(vec2[i][j]);
			//}

		}
		DataInputStream::closeFile(dis);
	} while (0);
}

ReadInfo::~ReadInfo()
{
}