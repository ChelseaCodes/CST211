/*************************************************************
* Author:		Chelsea Christison
* Filename:		node.h
* Date Created:	4.4.2017
*
* Modifications:
*	4.6 - removed T* to data to just be T
* 
*************************
* Class: Node
*
* Purpose: Templated node to encapsulate data to be placed in 
*	a linked list
*
* Manager functions:
*	Node()
*	Node(T data)
*	Node(const Node& copy)
*	~Node()
*
* Methods:
*	Node<T> & operator=(const Node<T> & copy) 
*	T * getData()
*	void setData(T data)
*	Node<T>* getNext()
*	void setNext(Node<T>* next)
*	Node<T>* getPrevious()
*	void setPrevious(Node<T>* previous)
*************************************************************************/
#ifndef node_h
#define node_h
#include <iostream>
using std::cout;
using std::endl; 

//forward declaration 
template <typename T>
class LList; 

template <typename T>
class Node
{
	friend class LList<T>; 
public:
	Node(const Node& copy);
	~Node();
	Node<T> & operator=(const Node<T> & copy); 
	T * getData();
	void setData(T data);
	Node<T>* getNext();
	void setNext(Node<T>* next);
	Node<T>* getPrevious();
	void setPrevious(Node<T>* previous); 
private:
	Node();
	Node(T data);
	T m_data; 
	Node<T> * m_next; 
	Node<T> * m_previous; 	
};
#endif

/*****************************************************************************/
//								        Node<T>								 //
/*****************************************************************************/
template <typename T>
Node<T>::Node() :m_next(nullptr), m_previous(nullptr)
{}

template <typename T>
Node<T>::Node(T data): m_data(data), m_next(nullptr), m_previous(nullptr)
{  }

template <typename T>
Node<T>::Node(const Node& copy): m_data(copy.m_data)
{}

template <typename T>
Node<T>& Node<T>::operator=(const Node& copy)
{
	if(this != & copy)
	{
		m_data = copy.m_data;
		m_next = nullptr; 
		m_previous = nullptr; 
	}
	return *this; 
}

template<typename T>
Node<T>::~Node()
{
	m_next = nullptr;
	m_previous = nullptr;
}

template <typename T>
T* Node<T>::getData()
{ return &m_data; }

template <typename T>
void Node<T>::setData(T data)
{ m_data = data; }

template <typename T>
Node<T>* Node<T>::getNext()
{
	if (!this)
		throw Exception("I am a null node"); 
	return m_next;
}

template <typename T>
void Node<T>::setNext(Node<T>* next)
{
	m_next = next; 
}

template <typename T>
Node<T>* Node<T>::getPrevious()
{
	if (!this)
		throw Exception("I am a null node"); 
	return m_previous;
}

template <typename T>
void Node<T>::setPrevious(Node<T>* previous)
{

	m_previous = previous; 
}