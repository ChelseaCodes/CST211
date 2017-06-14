/*************************************************************
* Author:		Chelsea Christison
* Filename:		stack.h
* Date Created:	4/24/2017
* Modifications:
*
* Class: Stack
**************************************************************/
#ifndef STACK_H
#define STACK_H
#include "Array.h"

template<typename T>
class Stack
{
public:
	Stack(); 
	Stack(int size); 
	Stack(const Stack<T>& copy);
	Stack<T>& operator=(const Stack<T>& rhs); 
	~Stack(); 

	void Push(T data); 
	T Pop();
	T Peek(); 
	int Size() const; 
	bool isEmpty() const; 
	bool isFull(); 
	void addOne(); 
private:
	Array<T> m_stack; 
	int m_size; 
};

template <typename T>
Stack<T>::Stack() : m_stack(1), m_size(0)
{}

template <typename T>
Stack<T>::Stack(int size) : m_stack(size), m_size(0)
{}

template <typename T>
Stack<T>::Stack(const Stack<T>& copy): m_stack(copy.m_stack), m_size(copy.m_size)
{}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
	if(this != &rhs)
	{
		m_stack = rhs.m_stack; 
		m_size = rhs.m_size; 
	}
	return *this; 
}

template <typename T>
Stack<T>::~Stack()
{
	m_size = 0; 
}

template <typename T>
void Stack<T>::Push(T data)
{
	if (isFull())
		throw Exception("Overflow Exception"); 

	m_stack[m_size++] = data; 

}

template <typename T>
T Stack<T>::Pop()
{
	if (isEmpty())
		throw Exception("Underflow Exception");
	
	return  m_stack[--m_size]; 
}

template <typename T>
T Stack<T>::Peek()
{
	if (isEmpty())
		throw Exception("Underflow Exception");
	
	return m_stack[m_size]; 
}

template <typename T>
int Stack<T>::Size() const
{
	return m_size; 
}

template <typename T>
bool Stack<T>::isEmpty() const
{
	return  m_size == 0; 
}

template <typename T>
bool Stack<T>::isFull()
{
	return m_size == m_stack.getLength(); 
}

template <typename T>
void Stack<T>::addOne()
{
	m_stack.setLength(m_stack.getLength() + 1);
}
#endif
