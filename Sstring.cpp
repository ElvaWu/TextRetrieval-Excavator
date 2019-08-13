#include"Sstring.h"
#include <iostream>


CharString::CharString(char * str, int length) :m_string(str), m_length(length)
{
	m_string = new char[m_length+1];
	for (int i = 0; i < m_length; i++)
	{
		m_string[i] = str[i];
	}
	m_string[m_length]='\0';
}


bool CharString::operator == (CharString str)
{
	if(m_length!=str.getLength())
		return 0;
	for(int i=0;i<m_length;i++)
	{
		if(m_string[i]!=str.getString()[i])
			return 0;
	}
	return 1;

}
CharString CharString::substring(int start, int length)
{
	CharString str2=CharString("\0",0);
	if (start > m_length || start + length > m_length)
		return str2;
	for(int i=0;i<m_length;i++)
	{
		if(m_string[i]=='\n'||m_string[i]=='\r')
			m_string[i]=' ';
	}
	str2=CharString(&m_string[start], length);
	return str2;
}

CharString CharString::concat(CharString back)
{
	CharString result;
	char *a=new char[m_length+back.getLength()+1];
	int i=0;
	for (i = 0; i < m_length; i++)
	{
		 a[i] = m_string[i];
	}
	int j=0;
	if (back.getLength()>0)
	{
		for (j = 0; j < back.getLength(); j++)
		{
			a[m_length + j] = back.getString()[j];
		}
	}
	result=CharString(a,m_length+back.getLength());
	return result;
}

char * CharString::getString()
{
	return m_string;
}

int CharString::getLength()
{
	return m_length;
}

int CharString::indexOf(int start, CharString str)
{
	if (start < 0 || start>m_length - 1)
		return -1;
	int length1 = m_length;
	int length2 = str.getLength();
	if (length2 <= 0 || length1 <= 0)
		return -1;
	int i = start;
	int j = 0;
	while (i < length1 && j < length2)
	{
		if (m_string[i] == str.getString()[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= length2)
		return i - length2;
	else
		return -1;

}

int CharString::indexOfChar(int start, char c)
{
	if (m_length <= 0||start>=m_length)
		return -1;
	int i = start;
	while (i < m_length)
	{
		if (m_string[i] == c)
			break;
		i++;
	}
	return i;
}

int CharString::compare(CharString s)
{
	int len=m_length;
	if(s.getLength()<m_length)
		len=s.getLength();
	for(int i=0;i<len;i++)
	{
		if(m_string[i]<s.getString()[i])
			return -1;
		else if(m_string[i]>s.getString()[i])
			return 1;
	}
	if(s.getLength()<m_length)
		return 1;
	else if(s.getLength()>m_length)
		return -1;
	else
		return 0;
}



void CharString::assign(CharString str)
{
	if (m_string)
		delete [] m_string;
	if (!str.getLength())
	{
		m_string = nullptr;
		m_length = 0;
	}
	else
	{
		int i = 0;
		m_string = new char[str.getLength()];
		while (i < str.getLength())
		{
			m_string[i] = str.getString()[i];
			i++;
		}
		m_length = str.getLength();
	}
}

void CharString::outputChStr(std::ofstream &outputStream)
{
	for (int i = 0;i < m_length; i++)
	{
		outputStream << m_string[i];
	}
}
