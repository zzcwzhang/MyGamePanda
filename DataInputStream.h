#ifndef _COMMON_DATAINPUTSTREAM_H_
#define _COMMON_DATAINPUTSTREAM_H_
#include "SConfig.h"
NAMESPACE_ZJG_BEGIN
class DataInputStream{
public :
	static DataInputStream* openFile(const char* fileName,string mode);		//打开文件
	static bool				closeFile(DataInputStream* dis);				//关闭文件
	int			readInt();												//读取Int
	short		readShort();											//读取Short
	float     readFloat();
	char		readByte();												//读取cbyte
	string		readString();
	string		readAString();
	void		skip(long num);											//跳过num字节
	void		readFully(array1(cbyte)& src);
	void read(array1(cbyte)&data);
	void readunbyte(array1(unbyte)&data);
private :
	DataInputStream();
	~DataInputStream();
	unsigned long fPostion;									//文件游标位置
	unsigned long bufferSize;								//数据长度
	char* pBuffer;									//数据流
};
NAMESPACE_ZJG_END
#endif