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
// ������:    openFile
// Ȩ  ��:    public static 
// ����  :    const char * fileName,�������ļ���
// ����  :    string mode		   ,�ļ�����ģʽ
// ����ֵ:    DataInputStream*		
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
// ������:    closeFile
// Ȩ  ��:    public 
// ����ֵ:    bool
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
//// ������:    readInt
//// Ȩ  ��:    public 
//// ����ֵ:    int
////************************************
//int DataInputStream::readInt()
//{
//	//�����ļ���β������-1
//	if(fPostion >= bufferSize)		return -1;
//	int iValue = 0;
//	iValue = ((pBuffer[fPostion]<<24)&0xFF)|((pBuffer[fPostion + 1]<<16)&0xFF)|((pBuffer[fPostion + 2]<<8)&0xFF)|pBuffer[fPostion + 3];
//	fPostion +=4;
//	return iValue;
//}
//
////************************************
//// ������:    readShort
//// Ȩ  ��:    public 
//// ����ֵ:    short
////************************************
//short DataInputStream::readShort()
//{
//	//�����ļ���β������-1
//	if(fPostion >= bufferSize)		return -1;
//	short sValue = 0;
//	sValue = ((pBuffer[fPostion]<<8)&0xFF)|(pBuffer[fPostion + 1]&0xFF);
//	fPostion += 2;
//	return sValue;
//}
//
////************************************
//// ������:    readByte
//// Ȩ  ��:    public 
//// ����ֵ:    cbyte
////************************************
//char DataInputStream::readByte()
//{
//	//�����ļ���β������-1
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
// ������:    readString
// Ȩ  ��:    public 
// ����ֵ:    char*		��ȡ�ַ�������Ҫ�ֶ��ͷ��ڴ�
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
// ������:    readFully
// Ȩ  ��:    public 
// ����  :    Vector1(cbyte)&src
// ����ֵ:    void
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
// ������:    skip
// Ȩ  ��:    public 
// ����  :    long num		�����ļ����ֽ���
// ����ֵ:    void
//************************************
void DataInputStream::skip(long num)						//����num�ֽ�
{
	if(fPostion >= bufferSize) return;
		fPostion +=num;
}
NAMESPACE_ZJG_END