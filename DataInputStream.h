#ifndef _COMMON_DATAINPUTSTREAM_H_
#define _COMMON_DATAINPUTSTREAM_H_
#include "SConfig.h"
NAMESPACE_ZJG_BEGIN
class DataInputStream{
public :
	static DataInputStream* openFile(const char* fileName,string mode);		//���ļ�
	static bool				closeFile(DataInputStream* dis);				//�ر��ļ�
	int			readInt();												//��ȡInt
	short		readShort();											//��ȡShort
	float     readFloat();
	char		readByte();												//��ȡcbyte
	string		readString();
	string		readAString();
	void		skip(long num);											//����num�ֽ�
	void		readFully(array1(cbyte)& src);
	void read(array1(cbyte)&data);
	void readunbyte(array1(unbyte)&data);
private :
	DataInputStream();
	~DataInputStream();
	unsigned long fPostion;									//�ļ��α�λ��
	unsigned long bufferSize;								//���ݳ���
	char* pBuffer;									//������
};
NAMESPACE_ZJG_END
#endif