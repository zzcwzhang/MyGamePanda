#pragma once;

#include "ZConfig.h"
#include "DataInputStream.h"
#include "MRecord.h"

USING_SG_GAME;

class ReadInfo
{
public:
	~ReadInfo();

	static ReadInfo* getInstance();

	array2(int) buildarray;
	array2(int) footmanarray;
	array2(int) demonarray;
	array2(int) equiparray;
	array2(int) equipmentarray;
	array2(int) towerSortForMap;
	array2(int) Runearray;
	array2(int) demonForMap;

	//array2(int) buildarray;
	//array2(int) footmanarray;
	//array2(int) demonarray;
	//array2(int) equiparray;
	//array2(int) equipmentarray;
	//array2(int) towerSortForMap;
	//array2(int) Runearray;
	//array2(int) demonForMap;

	int UserEquiparray[ZC_FOOTMAN_COUNT][ZC_FOOTMAN_EQUIPMENTCOUNT];

private:
	static ReadInfo* instance;
	void ReadData();
	void ReadUserEquipment();
	void ReadArray( const char* path,array2(int)& vec2,int dataCount );

};

