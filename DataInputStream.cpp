#include "DataInputStream.h"
NAMESPACE_ZJG_BEGIN
DataInputStream::DataInputStream()
:fPostion(0),
bufferSize(0),
pBuffer(NULL)
{

}

DataInputStream::~DataInputStream()
{

}

//************************************
// 方法名:    openFile
// 权  限:    public static 
// 参数  :    const char * fileName,输入流文件名
// 参数  :    string mode		   ,文件操作模式
// 返回值:    DataInputStream*		
//************************************
DataInputStream* DataInputStream::openFile(const char* fileName,string mode)
{
	string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	DataInputStream* dis = new DataInputStream();
	dis->pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), mode.c_str(), &dis->bufferSize);
	if(!dis->pBuffer)
	{
		CC_SAFE_DELETE(dis);
		return NULL;
	}
	return dis;
}


//************************************
// 方法名:    closeFile
// 权  限:    public 
// 返回值:    bool
//************************************
bool DataInputStream::closeFile(DataInputStream* dis)
{
	if(NULL==dis) return true;
	dis->fPostion = 0;
	dis->bufferSize = 0;
	CC_SAFE_DELETE(dis->pBuffer);
	CC_SAFE_DELETE(dis);
	return true;
}


////************************************
//// 方法名:    readInt
//// 权  限:    public 
//// 返回值:    int
////************************************
//int DataInputStream::readInt()
//{
//	//超出文件流尾，返回-1
//	if(fPostion >= bufferSize)		return -1;
//	int iValue = 0;
//	iValue = ((pBuffer[fPostion]<<24)&0xFF)|((pBuffer[fPostion + 1]<<16)&0xFF)|((pBuffer[fPostion + 2]<<8)&0xFF)|pBuffer[fPostion + 3];
//	fPostion +=4;
//	return iValue;
//}
//
////************************************
//// 方法名:    readShort
//// 权  限:    public 
//// 返回值:    short
////************************************
//short DataInputStream::readShort()
//{
//	//超出文件流尾，返回-1
//	if(fPostion >= bufferSize)		return -1;
//	short sValue = 0;
//	sValue = ((pBuffer[fPostion]<<8)&0xFF)|(pBuffer[fPostion + 1]&0xFF);
//	fPostion += 2;
//	return sValue;
//}
//
////************************************
//// 方法名:    readByte
//// 权  限:    public 
//// 返回值:    cbyte
////************************************
//char DataInputStream::readByte()
//{
//	//超出文件流尾，返回-1
//	if(fPostion >= bufferSize) return -1;
//	char bValue = 0;
//
//	bValue = pBuffer[fPostion];
//	fPostion++;
//	return bValue;
//}
//
//
char DataInputStream::readByte()
{
	char ch = pBuffer[fPostion]&0xFF;
	fPostion++;
	return ch;
}

short DataInputStream::readShort()
{
	short ch1 =  (short)(readByte()&0xff);
	short ch2 =  (short)(readByte()&0xff);
	return ((ch1<<8)|ch2)&0xffff;
}
float  DataInputStream:: readFloat()
{
	string s = readString();
	return atof(s.c_str());
}

int DataInputStream::readInt()
{
	short ch1 =  (short)(readByte()&0xff);
	short ch2 =  (short)(readByte()&0xff);
	short ch3 =  (short)(readByte()&0xff);
	short ch4 =  (short)(readByte()&0xff);
	return ((ch1<<24)|(ch2<<16)|(ch3<<8)|ch4)&0xffffffff;
}

//************************************
// 方法名:    readString
// 权  限:    public 
// 返回值:    char*		读取字符串，需要手动释放内存
//************************************
string DataInputStream::readString()
{
	int len = readInt();
	char* ch = new char[len + 1];
	memset(ch,0,(len+1)*sizeof(char));
	for(int i = 0;i < len;i++)
	{
		ch[i] = readByte();
	}
	string str(ch);
	delete[] ch;
	return str;	
}

string DataInputStream::readAString()
{
	int len = readShort();
	char* ch = new char[len + 1];
	memset(ch,0,(len+1)*sizeof(char));
	for(int i = 0;i < len;i++)
	{
		ch[i] = readByte();
	}
	string str(ch);
	delete[] ch;
	return str;	
}

//************************************
// 方法名:    readFully
// 权  限:    public 
// 参数  :    Vector1(cbyte)&src
// 返回值:    void
//************************************
void DataInputStream::readFully(array1(cbyte)&src)
{
	long num = src.size();
	if(fPostion > bufferSize||fPostion + num > bufferSize) return;
	src.assign(&pBuffer[fPostion],&pBuffer[fPostion] + num);
	src.resize(num);
	fPostion += num;
}
void DataInputStream::read(array1(cbyte)&src){
	long num =readInt();
	if(fPostion > bufferSize||fPostion + num > bufferSize) return;
	src.assign(&pBuffer[fPostion],&pBuffer[fPostion] + num);
	src.resize(num);
	fPostion += num;
}
void DataInputStream::readunbyte(array1(unbyte)&data)
{
	long num =readInt();
	if(fPostion > bufferSize||fPostion + num > bufferSize) return;
	data.assign(&pBuffer[fPostion],&pBuffer[fPostion] + num);
	data.resize(num);
	fPostion += num;
}
//************************************
// 方法名:    skip
// 权  限:    public 
// 参数  :    long num		跳过文件流字节数
// 返回值:    void
//************************************
void DataInputStream::skip(long num)						//跳过num字节
{
	if(fPostion >= bufferSize) return;
		fPostion +=num;
}
NAMESPACE_ZJG_END