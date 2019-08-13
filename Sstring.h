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
	CharString substring(int start, int length);//截取第start+1个字符后长度为length的子串
	CharString concat(CharString back);//返回连接后的新串
	char* getString();
	int getLength();
	int indexOf(int start,CharString str);//返回str在当前主串第start个位置后的第一个位置，若不存在，返回-1
	int indexOfChar(int start, char c);
	int compare(CharString s);
	void assign(CharString str);//str赋给当前串
	void outputChStr(std::ofstream &outputStream);
	bool operator == ( CharString str);
};
#endif
#pragma once
