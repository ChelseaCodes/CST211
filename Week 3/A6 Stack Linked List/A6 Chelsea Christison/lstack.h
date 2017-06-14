/*************************************************************
* Author:		Chelsea Christison
* Filename:		stack.h
* Date Created:	4/24/2017
* Modifications:
*
* Class: LStack
**************************************************************/
#ifndef LSTACK_H
#define LSTACK_H

#include "linkedlist.h"

template<typename T>
class LStack
{
public:
	LStack();
	LStack(const LStack<T>& copy);
	LStack<T>& operator=(const LStack<T>& rhs);
	~LStack();

	void Push(T data);
	T Pop();
	T Peek();
	int Size() const;
	bool isEmpty() const;
private:
	LList<T> m_stack;
	int m_size;
};

template <typename T>
LStack<T>::LStack() : m_size(0)
{}

template <typename T>
LStack<T>::LStack(const LStack<T>& copy) : m_stack(copy.m_stack), m_size(copy.m_size)
{}

template <typename T>
LStack<T>& LStack<T>::operator=(const LStack<T>& rhs)
{
	if (this != &rhs)
	{
		m_stack = rhs.m_stack;
		m_size = rhs.m_size;
	}
	return *this;
}

template <typename T>
LStack<T>::~LStack()
{
	m_size = 0;
}

template <typename T>
void LStack<T>::Push(T data)
{
	++m_size; 
	m_stack.Prepend(data); 
}

template <typename T>
T LStack<T>::Pop()
{
	if (isEmpty())
		throw Exception("Underflow Exception");

	
	T data = m_stack.First();
	m_stack.Extract(data); 	
	--m_size; 
	return data; 
}

template <typename T>
T LStack<T>::Peek()
{
	if (isEmpty())
		throw Exception("Underflow Exception");

	return m_stack.First();
}

template <typename T>
int LStack<T>::Size() const
{
	return m_size;
}

template <typename T>
bool LStack<T>::isEmpty() const
{
	return  m_size == 0;
}

#endif
