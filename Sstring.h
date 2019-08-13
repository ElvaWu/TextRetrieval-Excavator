#ifndef SSTRING
#define SSTRING

#include<fstream>

class CharString
{
public:
	CharString(char*str, int length) ;
	CharString(){}
	~CharString() {}
protected:
	char * m_string;
	int m_length;
public:
	CharString substring(int start, int length);//��ȡ��start+1���ַ��󳤶�Ϊlength���Ӵ�
	CharString concat(CharString back);//�������Ӻ���´�
	char* getString();
	int getLength();
	int indexOf(int start,CharString str);//����str�ڵ�ǰ������start��λ�ú�ĵ�һ��λ�ã��������ڣ�����-1
	int indexOfChar(int start, char c);
	int compare(CharString s);
	void assign(CharString str);//str������ǰ��
	void outputChStr(std::ofstream &outputStream);
	bool operator == ( CharString str);
};
#endif
#pragma once
