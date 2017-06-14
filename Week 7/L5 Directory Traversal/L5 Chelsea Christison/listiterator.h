/************************************************************************
* Class: listiterator.h
*
* Purpose: This abstract base class derived from AbstractIterator
*	implements an iterator for a linked list
*
* Manager functions:
* 	ListIterator()
*		default cursor is nullptr
*	ListIterator(LList<T> * list)
*		sets cursor to beginning of list
*	virtual ~ListIterator()
*
* Methods:
*	virtual void Reset() = 0
*	virtual void MoveNext() = 0
*	bool IsDone()
*		true when past last element
*	T * GetCurrent()
*		returns data in cursor
*
*************************************************************************/
#ifndef listiterator_h
#define listiterator_h
#include "abstractiterator.h"

template <typename T>
class ListIterator : public AbstractIterator<T> 
{
public:
	ListIterator();					//no arg c'tor 
	ListIterator(LList<T> * list);	//one arg c'tor, passed pointer to linked list 
	virtual ~ListIterator();		// d'tor
	virtual void Reset() = 0;	
	virtual void MoveNext() = 0;	
	bool IsDone();
	T * GetCurrent();

protected:
	Node<T> * m_cursor;				//cursor is node inside LList<T>
	LList<T> * m_list;
	Node<T> * getCursor(); 
	LList<T> * getList(); 
};

template <typename T>
ListIterator<T>::ListIterator() : AbstractIterator() , m_cursor(nullptr), m_list(nullptr)
{}

template <typename T>
ListIterator<T>::ListIterator(LList<T> * list) : AbstractIterator() , m_cursor(list->getHead()), m_list(list)
{}

template <typename T>
ListIterator<T>::~ListIterator()
{
}

template <typename T>
bool ListIterator<T>::IsDone()
{
	return m_cursor == nullptr; 
}

template <typename T>
T* ListIterator<T>::GetCurrent()
{
	return m_cursor->getData();
}

template <typename T>
Node<T>* ListIterator<T>::getCursor()
{
	return m_cursor; 
}

template <typename T>
LList<T>* ListIterator<T>::getList()
{
	return m_list; 
}
#endif 
