#ifndef CHARSTRLINK_H
#define CHARSTRLINK_H

#include"Sstring.h"
class CharStrLink
{
public:
	CharStrLink();
	~CharStrLink();
	void addStr(CharString s);
	void removeStr(CharString s);
	int searchStr(CharString s);
private:
	struct m_node
	{
		CharString str;
		m_node * next;
		m_node(CharString s) :str(s), next(nullptr) {}
	};
	m_node* m_head;
	int m_length;
};

#endif
#pragma once
