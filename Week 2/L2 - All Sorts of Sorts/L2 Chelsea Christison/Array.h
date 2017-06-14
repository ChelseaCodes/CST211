/*************************************************************
* Author:		Chelsea Christison
* Filename:		Array.h
* Date Created:	4.1.2017
* 
* Modifications:	
*	4.2 - Adding in exception throws 
*	4.3 - Changed op[] to check value of index 
* *****
* Class: Array 
*
* Purpose: creates a single dimensional dynamic array - Templated
*
* Manager functions:
*	Array()
*	Array(int length, int start_index = 0)
*	Array(const Array& copy)
*	~Array()
*	Array& operator=(const Array& copy)
*
* Methods:
*	T& operator[](int index)
*		overloaded [] for ability to access specific elements
*	int getStartIndex() const
*		retrieves the start index, checking if out of bounds
*	int getLength() const
*		const method returning the length
*	void setStartIndex(int start_index)
*		sets the start index of array
*	void setLength(int length)
*		sets the length of the array 
*	
*************************************************************************/
#ifndef  Array_H
#define Array_H
#include <iostream>
#include "exception.h"
const int MAX_LENGTH(10); 

template <typename T>
class Array
{
public:
	Array();
	Array(int length, int start_index = 0); 
	Array(const Array<T> & copy);
	~Array();
	Array<T> & operator=(const Array<T> & copy); 

	T& operator[](int index); 
	int getStartIndex() const;
	int getLength() const; 
	void setStartIndex(int start_index); 
	void setLength(int length); 
private:
	T * m_array;
	int m_length;
	int m_start_index; 
};
#endif 

//default c'tor 
template<typename T> 
Array<T>::Array() : m_array(nullptr), m_length(0), m_start_index(0)
{}

//one / two arg c'tor
template<typename T>
Array<T>::Array(int length, int start_index = 0) : m_length(length), m_start_index(start_index)
{
	if (length < 0)
		throw(Exception("Array length can't be a negative value")); 
	else if (start_index >= length)
		throw(Exception("Starting index out of bounds")); 

	m_array = new T[length];
}

//copy constructor
template <typename T>
Array<T>::Array(const Array<T>& copy): m_length(copy.m_length), m_start_index(copy.m_start_index)
{
	m_array = new T[copy.m_length]; 
	for(int i(0); i < copy.m_length; i++)
	{
		m_array[i] = copy.m_array[i];
	}
}

//destructor
template <typename T>
Array<T>::~Array()
{
	delete[] m_array; 
	m_length = 0;
	m_start_index = 0; 
	m_array = nullptr; 
}

//operator ='s
template <typename T>
Array<T>& Array<T>::operator=(const Array<T> & copy)
{
	if(this != &copy)
	{
		if(m_length != copy.m_length)
		{
			delete[] m_array;

			m_array = new T[copy.m_length];
			m_length = copy.m_length;
		}

		//copy data over
		for (int i(0); i < copy.m_length; i++)
		{
			m_array[i] = copy.m_array[i];
		}
		m_start_index = copy.m_start_index;
	}
	return *this;
}

/**********************************************************************
* Purpose: This function allows user to access their array using brackets.
*	Checks the value of the index passed to ensure user is not 
*	going out of bounds of their array. Even if starting index is a 
*	negative number, positive or zero. 	
*
* Precondition:
*     index - element of the array user wishes to access
*
* Postcondition:
*      returns reference to data
*      modifies the object's start index
************************************************************************/
template <typename T>
T& Array<T>::operator[](int index)
{
	int this_index = index - m_start_index;

	if (this_index >= m_length || index < m_start_index)
		throw(Exception("Index out of bounds"));

	return m_array[this_index];
}

//get array start index
template <typename T>
int Array<T>::getStartIndex() const
{
	return m_start_index;
}

//get array length
template <typename T>
int Array<T>::getLength() const
{
	return m_length;
}

/**********************************************************************
* Purpose: This function allows user to set the start index of 
*	array. It checks to ensure validity of the start index specified,
*	as to not go out of bounds of array. 
*
* Precondition:
*     start_index -	index user would like to start at
*
* Postcondition:
*      no returns. 
*      modifies the object's start index
************************************************************************/
template <typename T>
void Array<T>::setStartIndex(int start_index)
{
	m_start_index = start_index; 
}

/**********************************************************************
* Purpose: This function allows user to set the length of their array,
*	bigger or smaller (which can result in loss of data). Checks given
*	length to ensure a positive length. Creates a new array with the 
*	given length, and copies data accordingly. 
*
* Precondition:
*     length -	length user wishes to set array to 
*
* Postcondition:
*      no returns.
*      modifies the object's length
************************************************************************/
template <typename T>
void Array<T>::setLength(int length)
{
	if (length < 0)
		throw(Exception("Array length can't be a negative number")); 

	//create new array
	T * new_array = new T[length];  
		 
	for(int i(0); i < m_length; i++)
	{
		if (i < length)
			
			new_array[i] = m_array[i];
	}

	//delete old array
	delete[] m_array; 
	//set pointers 
	this->m_array = new_array;
	//update to the new length 
	this->m_length = length;
}