/*************************************************************
* Author:		Chelsea Christison
* Filename:		linkedlist.h
* Date Created:	4.4.2017
*
* Modifications:
*	4.6 - removed T* to data, just T
* 
***************************
* Class: LList
*
* Purpose:	Templated Linked list
*
* Manager functions:
*	LList()
*	~LList()
*	LList(const LList<T>& copy)
*	LList<T>& operator=(const LList<T>& copy)
*
* Methods:
*	Node<T> * getHead() 
*	Node<T> * getTail() 
*	void PrintForwards()
*	void PrintBackwards()
*	T& First() const
*	T& Last() const 
*	void Prepend(T data)
*	void Append(T data)
*	void Purge() 
*	bool isEmpty()
*	bool Extract(T target)
*	void InsertAfter(T data, T target)
*	void InsertBefore(T data, T target)
*****************************************************************/
#ifndef linkedlist_H
#define linkedlist_H
#include<iostream>
using std::cout;
using std::endl; 
#include "exception.h"
#include "node.h"

template <typename T>
class LList
{
public:
	LList();
	~LList();
	LList(const LList<T>& copy);
	LList<T>& operator=(const LList<T>& copy);

	//testing only
	Node<T> * getHead(); 
	Node<T> * getTail(); 
	void PrintForwards();
	void PrintBackwards(); 

	//methods
	T& First() const;
	T& Last() const; 

	void Prepend(T data); 
	void Append(T data); 
	void Purge(); 
	bool isEmpty();
	bool Extract(T target); 
	void InsertAfter(T data, T target); 
	void InsertBefore(T data, T target);

private:
	Node<T> * m_head;
	Node<T> * m_tail;
};
#endif

/****************************************************************************/
//								LList<T>									//
/***************************************************************************/
template <typename T>
LList<T>::LList(): m_head(nullptr), m_tail(nullptr)
{}

template <typename  T>
LList<T>::~LList()
{
	Purge();
}

template <typename T>
LList<T>::LList(const LList<T>& copy)
{
	Node<T> * travel = copy.m_tail;
	m_head = nullptr; 
	m_tail = nullptr; 
	
	while(travel)
	{
		T data = *(travel->getData()); 
		this->Prepend(data);
		travel = travel->getPrevious(); 
	}
}

template <typename T>
LList<T>& LList<T>::operator=(const LList<T>& copy)
{
	if(this != &copy)
	{
		this->Purge(); 
		Node<T> * travel = copy.m_tail;
		while (travel)
		{
			this->Prepend(*(travel->getData()));
			travel = travel->getPrevious();
		}
	}
	return *this; 
}

template <typename T>
Node<T>* LList<T>::getHead()
{
	if (m_head == nullptr)
		throw Exception("Empty List");
	return m_head;
}

template <typename T>
Node<T>* LList<T>::getTail()
{
	if (m_tail == nullptr)
		throw Exception("Empty List"); 
	return m_tail;
}

template <typename T>
void LList<T>::PrintForwards()
{
	Node<T> * travel = m_head; 
	while(travel)
	{
		cout << *(travel->getData()) << " "; 
		travel = travel->getNext(); 
	}
}

template <typename T>
void LList<T>::PrintBackwards()
{
	//cout << "Llist print backwards" << endl; 
	Node<T> * travel = m_tail;
	while(travel)
	{
		cout << *(travel->getData()) << " "; 
		travel = travel->getPrevious(); 
	}
}

template <typename T>
T& LList<T>::First() const
{
	if (m_head == nullptr)
		throw Exception("Empty List");
	
	return *(m_head->getData()); 
}

template <typename T>
T& LList<T>::Last() const
{
	if (m_tail == nullptr)
		throw Exception("Empty List"); 

	return *(m_tail->getData()); 
}

template <typename T>
void LList<T>::Prepend(T data)
{
	Node<T> * new_node = new Node<T>(data);
	Node<T> * travel = nullptr; 
	
	if(m_head)
	{
		new_node->setNext(m_head);
		m_head->setPrevious(new_node);
		m_head = new_node;
	}
	else
	{
		m_head = new_node; 
		m_tail = new_node;
	}
}

template <typename T>
void LList<T>::Append(T data)
{
	Node<T> * new_node = new Node<T>(data); 
	
	new_node->setPrevious(m_tail);
	if(m_tail)
	{
		m_tail->setNext(new_node);
	}
	else
	{
		m_head = new_node;
	}
	m_tail = new_node; 
}

template <typename T>
void LList<T>::Purge()
{
	//cout << "Llist purge" << endl; 
	Node<T> * travel; 
	while(m_head)
	{
		travel = m_head;
		m_head = m_head->getNext();
		delete travel; 
	}
	m_head = nullptr; 
	m_tail = nullptr;
}

template <typename T>
bool LList<T>::isEmpty()
{
	return m_head == nullptr; 
}

template <typename T>
bool LList<T>::Extract(T target)
{
	//cout << "Llist Extract " << endl; 
	Node<T> * del = m_head;
	Node<T> * trail = nullptr;
	bool deleted = false; 
	
	//checks if head
	if (*(del->getData()) == target && m_head)
	{
		m_head = del->getNext(); 
		delete del; 
		deleted = true; 
		if(m_head)
			m_head->setPrevious(nullptr); 
	}
	else
	{
		bool loop = true; 
		trail = m_head; 
		del = del->getNext(); 
		while(del && loop)
		{
			if(*(del->getData()) == target)
			{
				trail->setNext(del->getNext());

				if(del->getNext())
					del->getNext()->setPrevious(trail); 
				else
					m_tail = trail;

				delete del; 
				deleted = true;
				loop = false;
			}
			trail = del;
			del = del->getNext();
		}
	}
	return deleted; 
}

template <typename T>
void LList<T>::InsertAfter(T data, T target)
{
	if (m_head == nullptr)
	{
		throw Exception("Empty List");
	}

	Node<T> * new_node = new Node<T>(data);
	Node<T> * travel = m_head;

	if (*(travel->getData()) == target)
	{
		new_node->setNext(m_head->getNext());
		
		if(m_head->getNext())
			m_head->getNext()->setPrevious(new_node);

		m_head->setNext(new_node); 
		new_node->setPrevious(m_head);
	}
	else
	{
		bool inserted = false;
		travel = travel->getNext();

		while(travel && !inserted)
		{
			if(*(travel->getData()) == target)
			{
				new_node->setNext(travel->getNext()); 

				if (travel->getNext())
					travel->getNext()->setPrevious(new_node);
				else
					m_tail = new_node; 

				travel->setNext(new_node);
				new_node->setPrevious(travel); 				
			}
			travel = travel->getNext(); 
		}
	}
}

template <typename T>
void LList<T>::InsertBefore(T data, T target)
{
	if (m_head == nullptr)
	{
		throw Exception("Empty List");
	}
	
	Node<T> * travel = m_head;

	if (*(travel->getData()) == target)
	{
		this->Prepend(data); 
	}
	else
	{
		Node<T> * new_node = new Node<T>(data);
		bool inserted = false;
		travel = travel->getNext();

		while (travel && !inserted)
		{
			if (*(travel->getData()) == target)
			{
				new_node->setNext(travel);
				new_node->setPrevious(travel->getPrevious()); 
				travel->getPrevious()->setNext(new_node); 
				travel->setPrevious(new_node); 
			}
			travel = travel->getNext();
		}
	}
}

