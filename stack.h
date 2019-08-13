#ifndef STACK_H
#define STACK_H
#include<iostream>

#define MAX_STACKSIZE 2000
#define INCREMENT 1000

template <class T>
class Stack
{
private:
	T *m_base;
	T *m_top;
	int m_size;//ջ�Ĵ�С

public:
	Stack(int size = 0);
	~Stack();
	//���ջ��Ԫ��
	bool clear();
	//�ж�ջ�Ƿ�Ϊ��
	bool empty();
	//��ȡջ��Ԫ��
	T top();
	//��ջ
	bool push(const T &elem);
	//��ջ��Ԫ�س�ջ
	const T pop();
};

template<class T>
Stack<T>::Stack(int size)
{
	if (0 > m_size)
	{
		m_size = 0;
	}
}

//��������
template <class T>
Stack<T>::~Stack()
{
	clear();
	free(this);
}

template<class T>
bool Stack<T>::clear()
{
	delete [] m_base;
	return true;
}

template<class T>
bool Stack<T>::empty()
{
	if (!m_size)
		return true;
	else
		return false;
}

template<class T>
T Stack<T>::top()
{
	T e;
	if (!m_top)
		return e;
	else
	{
		e = *m_top;
		return e;
	}
}

template<class T>
bool Stack<T>::push(const T & elem)
{
	if (!m_size)
	{
		m_base = new T[MAX_STACKSIZE];
		m_top = m_base;
	}
	if (m_top - m_base >= m_size-1)
	{
		T *a = new T[m_size+INCREMENT];
		for (int i = 0; i < m_size; i++)
		{
			a[i] = m_base[i];
		}
		delete []m_base;
		m_base = NULL;
		m_base = a;
		m_top = &a[m_size - 1];
	}
	m_top=&m_base[m_size];
	m_base[m_size]= elem;
	m_size++;
	return true;
}

template<class T>
const T Stack<T>::pop()
{
	T e;
	if (!m_size) return e;
	e=*m_top;
	m_top = &m_base[m_size - 2];
	m_size--;
	return e;
}


#endif
#pragma once
