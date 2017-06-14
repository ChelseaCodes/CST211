/************************************************************************
* Class: backwarditerator.h
*
* Purpose: This Iterator iterates through given linked list from
*	tail to head, reverse iteration 
*
* Manager functions:
* 	BackwardsIterator()
*		default cursor is nullptr
*	BackwardsIterator(T * data)
*		sets cursor to beginning of data
*	~BackwardsIterator()
*
* Methods:
*	void Reset()
*		initialize cursor to tail 
*	void MoveNext()
*		traverse to previous element
*	bool IsDone()
*		true when cursor is nullptr
*	T * GetCurrent()
*		returns data in cursor
*
*************************************************************************/
#ifndef backwardsiterator_h
#define backwardsiterator_h
#include "listiterator.h"

template <typename T>
class BackwardsIterator : public ListIterator<T>
{
public:
	BackwardsIterator();				//no arg c'tor 
	BackwardsIterator(LList<T> * list);		//one arg c'tor, passed linked list with city nodes
	~BackwardsIterator();				//d'tor
	void Reset();		//initialize cursor to the head of the linked list 
	void MoveNext();	//traverse to next element
	bool IsDone();		//true when past last element
	T * GetCurrent();	//gets data in current node 
};

template <typename T>
BackwardsIterator<T>::BackwardsIterator() : ListIterator()
{}

template <typename T>
BackwardsIterator<T>::BackwardsIterator(LList<T> * list) : ListIterator(list)
{
	BackwardsIterator<T>::Reset();
}

template <typename T>
BackwardsIterator<T>::~BackwardsIterator()
{
}

/*
* Purpose: moves ptr current to the beginning of LList
*/
template <typename T>
void BackwardsIterator<T>::Reset()
{
	LList<T> * list = ListIterator<T>::m_list;

	ListIterator<T>::m_cursor = list->getTail();
}

template <typename T>
void BackwardsIterator<T>::MoveNext()
{
	if (IsDone())
	{
		cout << "End of List, resetting to Beginning" << endl;
		Reset();
	}
	Node<T> * c = ListIterator<T>::getCursor();
	ListIterator<T>::m_cursor = c->getPrevious();
}

template <typename T>
bool BackwardsIterator<T>::IsDone()
{
	return ListIterator<T>::IsDone();
}

template <typename T>
T * BackwardsIterator<T>::GetCurrent()
{
	if (IsDone())
	{
		cout << "At end of list, returning to beginning" << endl;
		Reset();
	}
	return ListIterator<T>::GetCurrent();
}
#endif 

