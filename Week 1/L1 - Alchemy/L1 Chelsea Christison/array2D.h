/*************************************************************
* Author:		Chelsea Christison
* Filename:		array2D.h
* Date Created:	4.10.2017
*
* Modifications:
*	4.11 - setting m_array to nullptr in default c'tor 
* *****
* Class: Array2D
*
* Purpose: creates a 2 dimensional dynamic array - Templated
*	implemented with a double star
*
* Manager functions:
*	Array2D()
*	Array2D(int row, int column)
*	~Array2D()
*	Array2D(const Array2D<T> & copy)
*	Array2D& operator=(const Array2D& copy)
*
* Methods:
*	T& Select(int row, int column)
*		selects index at given row and column
*	const T& Select(int row, int column) const
*		selects index at given row and column, const 
*	const Row<T> operator[](int row) const
*		op[] returning a Row object given row const
*	Row<T> operator[](int row)
*		op[] returning a Row obj given row
*	void setRow(int row)
*	int getRow() const
*	void setColumn(int column)
*	int getColumn() const
*	Array<T> getArray() const
*
*************************************************************************/
#ifndef ARRAY2D_H
#define ARRAY2D_H
#include "exception.h"

template<typename T>
class Row; 

template<typename T>
class Array2D
{
public:
	Array2D(); 
	Array2D(int row, int column);
	~Array2D();
	Array2D(const Array2D<T> & copy);
	Array2D<T>& operator=(const Array2D<T> & copy);
	T& Select(int row, int column);
	const T& Select(int row, int column) const; 
	const Row<T> operator[](int row) const;
	Row<T> operator[](int row);
	void setRow(int row); 
	int getRow() const; 
	void setColumn(int column); 
	int getColumn() const; 
	T ** getArray() const; 
protected:
	T ** m_array;
	int m_rows;
	int m_columns;
};
#endif

template <typename T>
Array2D<T>::Array2D(): m_array(nullptr), m_rows(0), m_columns(0)
{}

template <typename T>
Array2D<T>::Array2D(int row, int column) : m_rows(row), m_columns(column)
{
	if (row <= 0)
		throw Exception("Negative or no row specified");
	else if (column <= 0)
		throw Exception("Negative or no column specified");

	//allocated memory accordingly 
	m_array = new T *[row]; 
	for (int r = 0; r < row; r++)
	{
		m_array[r] = new T[column]; 
	}
}

template <typename T>
Array2D<T>::~Array2D()
{
	for(int r = 0; r < m_rows; r++)
	{
		delete[] m_array[r]; 
	}
	delete[] m_array; 

	m_array = nullptr; 
	m_rows = 0; 
	m_columns = 0; 
}

template <typename T>
Array2D<T>::Array2D(const Array2D<T>& copy): m_rows(copy.m_rows), m_columns(copy.m_columns)
{
	//dynamically allocate memory for new object 
	m_array = new T *[copy.m_rows];
	for(int r = 0; r < copy.m_rows; r++)
	{
		m_array[r] = new T[copy.m_columns];
	}
	
	for(int r = 0; r < copy.m_rows; r++)
	{
		for(int c = 0; c < copy.m_columns; c++)
		{
			m_array[r][c] = copy.m_array[r][c]; 
		}
	}
}

template <typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D<T>& copy)
{
	if(this != &copy)
	{
		//if there's a difference in either 
		if(m_rows != copy.m_rows || m_columns != copy.m_columns)
		{	
			//delete memory
			for(int r = 0; r < m_rows; r++)
			{
				delete[] m_array[r]; 
			}
			delete[] m_array; 
			
			//allocate memory to new specs 
			m_array = new T*[copy.m_rows]; 
			for(int r = 0; r < copy.m_rows; r++)
			{
				m_array[r] = new T[copy.m_columns]; 
			}
		}
		//copy data over
		for(int r = 0; r < copy.m_rows; r++)
		{
			for( int c = 0; c < copy.m_columns; c++)
			{
				m_array[r][c] = copy.m_array[r][c]; 
			}
		}
		m_columns = copy.m_columns; 
		m_rows = copy.m_rows; 
	}
	return *this; 
}

template <typename T>
T& Array2D<T>::Select(int row, int column)
{
	if (row >= m_rows || row < 0)
		throw Exception("row access violation");
	else if (column >= m_columns || column < 0)
		throw Exception("column access violation");

	return m_array[row][column]; 
}

template <typename T>
const T& Array2D<T>::Select(int row, int column) const
{
	if (row >= m_rows || row < 0)
		throw Exception("row access violation");
	else if (column >= m_columns || row < 0)
		throw Exception("column access violation");

	return m_array[row][column];
}

template <typename T>
const Row<T> Array2D<T>::operator[](int row) const 
{
	return Row<T>(*this, row);
}

template <typename T>
Row<T> Array2D<T>::operator[](int row)
{
	return Row<T>(*this, row); 
}

template <typename T>
void Array2D<T>::setRow(int row)
{
	if (row < 0)
		throw Exception("Negative row value specified"); 
	
	//create T ** with row specified
	T ** new_ra = new T *[row]; 
	for (int r = 0; r < row; r++)
		new_ra[r] = new T[m_columns]; 

	//copy data into new ra 
	for(int r = 0; r < m_rows; r++)
	{
		for(int c = 0; c < m_columns; c++)
		{
			if(r < row)
				new_ra[r][c] = m_array[r][c]; 
		}
	}

	//delete old array
	for (int r = 0; r < m_rows; r++)
		delete[] m_array[r];
	delete[] m_array; 

	m_array = new_ra; 
	m_rows = row; 
}

template <typename T>
int Array2D<T>::getRow() const
{
	return m_rows; 
}

template <typename T>
void Array2D<T>::setColumn(int column)
{
	if (column < 0)
		throw Exception("Negative column specified"); 

	//create new array to specs
	T ** ra = new T*[m_rows]; 
	for (int r = 0; r < m_rows; r++)
		ra[r] = new T[column];
	
	//copy data over
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_columns; c++)
		{
			if (c < column)
				ra[r][c] = m_array[r][c];
		}
	}

	//delete old array
	for (int r = 0; r < m_rows; r++)
		delete[] m_array[r];
	delete[] m_array; 

	//set pointers 
	m_array = ra;
	m_columns = column; 
}

template <typename T>
int Array2D<T>::getColumn() const
{
	return m_columns; 
}

template <typename T>
T** Array2D<T>::getArray() const
{
	return m_array; 
}
