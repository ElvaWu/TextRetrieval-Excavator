#include "charStrLink.h"

CharStrLink::CharStrLink()
{
	m_head =nullptr;
	m_length = 0;
}

CharStrLink::~CharStrLink()
{
	if (!m_head)
		return;
	else
	{
		m_node *p = m_head;
		while (p)
		{
			m_node * q = p->next;
			delete p;
			p = nullptr;
            p = q;
		}
		m_length = 0;
	}
}

void CharStrLink::addStr(CharString s)
{
	if (!m_head)
		m_head = new m_node(s);
	else
	{
		m_node *p = m_head;
		while (p)
		{
			p = p->next;
		}
		m_node *newNode = new m_node(s);
		newNode->next = nullptr;
		p = newNode;
	}
	m_length++;
}

void CharStrLink::removeStr(CharString s)
{
	if (!m_head)
		return;
	else
	{
		m_node *p = m_head;
		m_node *q = p;
		while (p)
		{
			if (p->str.compare(s))
			{
				if (p == m_head)
				{
					delete m_head;
					m_head = nullptr;
					m_length--;
				}
				else 
				{
					q->next = p->next;
					delete p;
					m_length--;
				}
			}
			q = p;
			p = p->next;
		}
	}
}

int CharStrLink::searchStr(CharString s)
{
	if (!m_head)
		return 0;
	else
	{
		m_node *p = m_head;
		while (p)
		{
			if (p->str.compare(s))
				return 1;
		}
	}
	return 0;
}
