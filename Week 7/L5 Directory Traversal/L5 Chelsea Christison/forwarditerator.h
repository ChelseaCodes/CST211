/************************************************************************
* Class: forwarditerator.h
*
* Purpose: This Iterator iterates through given linked list from
*	head to tail, forward iteration
*
* Manager functions:
* 	ForwardIterator()
*		default cursor is nullptr
*	ForwardIterator(LList<T> * list)
*		sets cursor to beginning of data
*	~ForwardIterator()
*
* Methods:
*	void Reset()
*		initialize cursor to head
*	void MoveNext()
*		traverse to next element
*	bool IsDone()
*		true when cursor is nullptr
*	T * GetCurrent()
*		returns data in cursor
*
*************************************************************************/
#ifndef forwarditerator_h
#define forwarditerator_h
#include "listiterator.h"

template <typename T>
class ForwardIterator : public ListIterator<T>
{
public:
	ForwardIterator();				//no arg c'tor 
	ForwardIterator(LList<T> * list);		//one arg c'tor, passed linked list nodes
	~ForwardIterator();				//d'tor
	void Reset();		//initialize cursor to the head of the linked list 
	void MoveNext();	//traverse to next element
	bool IsDone();		//true when past last element
	T * GetCurrent();	//gets data in current node 
};

template <typename T>
ForwardIterator<T>::ForwardIterator() : ListIterator()
{}

template <typename T>
ForwardIterator<T>::ForwardIterator(LList<T> * list) : ListIterator(list)
{
	ForwardIterator<T>::Reset();
}

template <typename T>
ForwardIterator<T>::~ForwardIterator()
{}

/*
* Purpose: moves ptr current to the beginning of LList
*/
template <typename T>
void ForwardIterator<T>::Reset()
{
	LList<T> * list = ListIterator<T>::m_list;

	ListIterator<T>::m_cursor = list->getHead();
}

template <typename T>
void ForwardIterator<T>::MoveNext()
{
	if (IsDone())
	{
		cout << "End of List, resetting to Beginning" << endl;
		Reset();
	}

	Node<T> * c = ListIterator<T>::getCursor();
	ListIterator<T>::m_cursor = c->getNext();
}

template <typename T>
bool ForwardIterator<T>::IsDone()
{
	return ListIterator<T>::IsDone();
}

template <typename T>
T * ForwardIterator<T>::GetCurrent()
{
	if (IsDone())
	{
		cout << "At end of list, returning to beginning" << endl;
		Reset();
	}
	return ListIterator<T>::GetCurrent(); 
}
#endif 
