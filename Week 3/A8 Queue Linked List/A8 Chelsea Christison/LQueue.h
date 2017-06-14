/*************************************************************
* Author:		Chelsea Christison
* Filename:		LQueue.h
* Date Created:	4/25/2017
* Modifications:
*
* Class: LQueue
*
* Purpose:  Creates a queue that is linked list based 
*
* Manager Functions:
*	LQueue()
*	LQueue(const LQueue& copy)
*	LQueue& operator=(const LQueue& rhs)
*	~LQueue()
*
* Methods:
*	void Enqueue(T data)
*		places the data where the tail is at (append)
*	T Dequeue()
*		returns data at head, and moves head up
*	T& Front()
*		returns data at head, doesn't move the head
*	int Size() const
*		returns how many elements have data
*	bool isEmpty() const
*		returns a boolean on if the queue is empty
***************************************************************/
#ifndef LQUEUE_H
#define LQUEUE_H
#include "linkedlist.h"

template <typename T>
class LQueue
{
public:
	//canonical functions
	LQueue();
	LQueue(const LQueue& copy);
	LQueue& operator=(const LQueue& rhs);
	~LQueue();

	//methods
	void Enqueue(T data);
	T Dequeue();
	T& Front() const;
	int Size() const;
	bool isEmpty() const;

private:
	LList<T> * m_queue;
};

template <typename T>
LQueue<T>::LQueue()
{
	m_queue = new LList<T>(); 
}

template <typename T>
LQueue<T>::LQueue(const LQueue& copy)
{
	*m_queue = *(copy.m_queue);
}

template <typename T>
LQueue<T>& LQueue<T>::operator=(const LQueue& rhs)
{
	if(this != &rhs)
	{
		*m_queue = *rhs.m_queue; 
	}
	return *this; 
}

template <typename T>
LQueue<T>::~LQueue()
{
	delete m_queue;
}

/**********************************************************************
* Purpose: 
*	This function places the data item at the tail of the queue by
*	appending to the end of the list
*	
* Precondition:
*	data - data to be placed in the queue of type T
* Postcondition:
*   inserts data into the queue and changes tail
************************************************************************/
template <typename T>
void LQueue<T>::Enqueue(T data)
{
	m_queue->Append(data); 
}

/**********************************************************************
* Purpose: 
*	This function removes and returns the data item at the head of the 
*	queue by calling the linked lists First() - which returns data in
*	the head of the list. After storing the data, node is deleted and
*	moved. 
* Precondition:
*	none
* Postcondition:
*	changes head
************************************************************************/
template <typename T>
T LQueue<T>::Dequeue()
{
	if (isEmpty())
		throw Exception("Underflow error - Queue is empty");
	
	T data = m_queue->First();
	m_queue->Extract(data);

	return data; 
}

/**********************************************************************
* Purpose:
*	This function returns a reference to the beginning of the
*	queue. Throws exception if queue is empty
*
* Precondition:
*	none
* Postcondition:
*	returns a reference to data in head, can be modified
************************************************************************/
template <typename T>
T& LQueue<T>::Front() const
{
	if (isEmpty())
		throw Exception("Empty Queue"); 

	return m_queue->First(); 
}

/**********************************************************************
* Purpose:
*	This function returns the number of nodes in the queue. Having no
*	set set this function begins at head and counts until nullptr;
*
* Precondition:
*	none
* Postcondition:
*	returns a constant boolean
************************************************************************/
template <typename T>
int LQueue<T>::Size() const
{
	int count = 0; 
	Node<T> * travel = m_queue->getHead();

	while(travel)
	{
		count++; 
		travel = travel->getNext(); 
	}

	return count; 
}

/**********************************************************************
* Purpose:
*	This function returns a bool for if the queue is empty. Calls 
*	linked list isEmpty();
*
* Precondition:
*	none
* Postcondition:
*	returns a constant boolean
************************************************************************/
template <typename T>
bool LQueue<T>::isEmpty() const
{
	return m_queue->isEmpty(); 
}

#endif
