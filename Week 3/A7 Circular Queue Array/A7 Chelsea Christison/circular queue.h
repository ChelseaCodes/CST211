/*************************************************************
* Author:		Chelsea Christison
* Filename:		circular queue.h
* Date Created:	4/25/2017
* Modifications:
*
* Class: CQueue
* 
* Purpose:  Creates a circular queue that is array based
* 
* Manager Functions: 
*	CQueue()
*	CQueue(int max_size)
*	CQueue(const CQueue& copy)
*	CQueue& operator=(const CQueue& rhs)
*	~CQueue()
*	
* Methods: 
*	void Enqueue(T data)
*		places the data where the tail is at
*	T Dequeue()
*		returns data at head, and moves head up
*	T& Front() 
*		returns data at head, doesn't move the head
*	int Size() const
*		returns how many elements have data 
*	bool isEmpty() const
*		returns a boolean on if the queue is empty
*	bool isFull() const 
*		returns a boolean on if the queue is full
***************************************************************/
#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H
#include "Array.h"
template <typename T>
class CQueue
{
public:
	//canonical functions
	CQueue(); 
	CQueue(int max_size); 
	CQueue(const CQueue& copy); 
	CQueue& operator=(const CQueue& rhs); 
	~CQueue(); 

	//methods
	void Enqueue(T data); 
	T Dequeue(); 
	T& Front() const; 
	int Size() const; 
	bool isEmpty() const;
	bool isFull() const; 

private:
	Array<T> m_queue;
	const int m_size; 
	int m_head; 
	int m_tail; 
};

template <typename T>
CQueue<T>::CQueue() : m_queue(1), m_size(1), m_head(-1), m_tail(-1)
{}

template <typename T>
CQueue<T>::CQueue(int max_size) : m_queue(max_size), m_size(max_size), m_head(-1), m_tail(-1)
{}

template <typename T>
CQueue<T>::CQueue(const CQueue& copy) :m_queue(copy.m_queue), m_size(copy.m_size), m_head(copy.m_head), m_tail(copy.m_tail)
{}

template <typename T>
CQueue<T>& CQueue<T>::operator=(const CQueue& rhs)
{
	if( this != & rhs)
	{
		m_queue = rhs.m_queue; 
		m_size = rhs.m_size; 
		m_head = rhs.m_head; 
		m_tail = rhs.m_tail; 
	}
	return *this; 
}

template <typename T>
CQueue<T>::~CQueue()
{
	m_head = -1; 
	m_tail = -1; 

}

/**********************************************************************
* Purpose: This function places the data item at the tail of the queue
*	If overflow occurs, throw an error. Otherwise if the head 
*	isn't zero, insert at tail after incrementing. And empty queue 
*	begins at -1, so it will insert at 0. If the tail IS at max
*	then it will reset to -1 as long as head isn't 0. If the head is 
*	still set to it's original value -1, set to point to element 0. 
*	
* Precondition:
*	data - data to be placed in the queue of type T
* Postcondition:
*   inserts data into the queue and changes tail
************************************************************************/
template <typename T>
void CQueue<T>::Enqueue(T data)
{
	if (isFull())
		throw Exception("Overflow error - Queue is Full"); 


	if (m_head == -1)
	{
		m_head = m_tail = 0;
	}
	else 
	{
		if (m_tail == m_size - 1)
			m_tail = 0;
		else
			m_tail++; 
	}
	
	m_queue[m_tail] = data;
}

/**********************************************************************
* Purpose: This function removes and returns the data item at the front
*	of the queue. If the head moves past the end of the array, it 
*	resets to zero. but if the the head and tail were the same before
*	the Dequeue then the last element was removed and both restart 
*	at -1. 
*	
* Precondition:
*	none
* Postcondition:
*	changes head
************************************************************************/
template <typename T>
T CQueue<T>::Dequeue()
{
	if (isEmpty())
		throw Exception("Underflow error - Queue is empty");

	T temp = m_queue[m_head];

	if (m_head == m_tail)
	{
		m_head = m_tail = -1;
	}
	else
	{
		if (m_head == m_size - 1)
			m_head = 0;
		else
			m_head++;
	}

	return temp; 
}

/**********************************************************************
* Purpose: 
*	This function returns a reference to the beginning of the
*	queue. Throws exception if queue is empty
*
* Precondition:
*	none
* Postcondition:
*	returns a reference to T, can be modified
************************************************************************/
template <typename T>
T& CQueue<T>::Front() const
{
	if(isEmpty())
		throw Exception("Queue is empty");

	return m_queue[m_head]; 
}

template <typename T>
int CQueue<T>::Size() const
{
	return m_head > m_tail ? (m_size - m_head + m_tail + 1) : (m_tail - m_head + 1);
}

/**********************************************************************
* Purpose: 
*	This function returns a bool for if the queue is empty. If 
*	both are -1, then they are empty. 
*
* Precondition:
*	none
* Postcondition:
*	returns a constant boolean
************************************************************************/
template <typename T>
bool CQueue<T>::isEmpty() const
{
	return m_tail == -1 || m_head == -1;
}

/**********************************************************************
* Purpose: 
*	This function returns a bool for if the queue is full 
*	If the head is 0 while the tail is at the last element the queue
*	is full. Also, if the head is equal to the tail + 1 the queue is 
*	full. 
*	
* Precondition:
*	none
* Postcondition:
*	returns a constant boolean
************************************************************************/
template <typename T>
bool CQueue<T>::isFull() const
{
	return (m_head == m_tail + 1 || m_head == 0 && m_tail == m_size - 1);
}


#endif
