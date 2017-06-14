/*************************************************************
* Author:		Chelsea Christison
* Filename:		array2D.h
* Date Created:	4.7.2017
*
* Modifications:
* *****
* Class: Array2D
*
* Purpose: creates a 2 dimensional dynamic array - Templated
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
#include "array.h"
#include "row.h"


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
	void setRow(int rows); 
	int getRow() const; 
	void setColumn(int columns); 
	int getColumn() const; 
protected:
	Array<T> m_array;
	int m_rows;
	int m_columns;
};


template <typename T>
Array2D<T>::Array2D(): m_rows(0), m_columns(0)
{}

template <typename T>
Array2D<T>::Array2D(int row, int column) : m_rows(row), m_columns(column)
{
	if (row <= 0)
		throw Exception("Negative or no row specified");
	else if (column <= 0)
		throw Exception("Negative or no column specified");

	m_array = Array<T>(row * column); 
}

template <typename T>
Array2D<T>::~Array2D()
{
	m_rows = 0; 
	m_columns = 0; 
}

template <typename T>
Array2D<T>::Array2D(const Array2D<T>& copy): m_rows(copy.m_rows), m_columns(copy.m_columns), m_array(copy.m_array)
{}

template <typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D<T>& copy)
{
	if(this != &copy)
	{
		m_array = copy.m_array; 
		m_rows = copy.m_rows;
		m_columns = copy.m_columns;
	}
	return *this; 
}

template <typename T>
T& Array2D<T>::Select(int row, int column)
{
	return m_array[row * m_columns + column]; 
}

template <typename T>
const T& Array2D<T>::Select(int row, int column) const
{
	
	return m_array[row * m_columns + column];
}

template <typename T>
const Row<T> Array2D<T>::operator[](int row) const 
{
	if(row >= m_rows || row < 0)
		throw Exception("row access violation");

	return Row<T>(*this, row);
}

template <typename T>
Row<T> Array2D<T>::operator[](int row)
{
	if (row >= m_rows || row < 0)
		throw Exception("row access violation");

	return Row<T>(*this, row); 
}

template <typename T>
void Array2D<T>::setRow(int rows)
{
	if (rows < 0)
		throw Exception("Negative row value specified"); 
	
	m_array.setLength(rows * m_columns);
	m_rows = rows; 
}

template <typename T>
int Array2D<T>::getRow() const
{
	return m_rows; 
}

template <typename T>
void Array2D<T>::setColumn(int columns)
{
	if (columns < 0)
		throw Exception("Negative column specified"); 

	Array<T> new_array(m_rows * columns);
	
	/*if(columns < m_columns)
	{
		int index_old_array = 0; 
		for(int i(0); i < new_array.getLength(); i++)
		{
			new_array[i] = m_array[index_old_array++]; 

			if( index_old_array % m_columns == columns)
			{
				index_old_array += (m_columns - columns); 
			}
		}
	}
	else
	{
		int index_new_array = 0; 
		for(int i(0); i < m_array.getLength(); i++)
		{
			new_array[index_new_array++] = m_array[i];

			if (index_new_array % columns == m_columns)
			{
				index_new_array += (columns - m_columns);
			}
		}
	}
	m_array = new_array; 
	m_columns = columns; */

	int min = m_columns < columns ? m_columns : columns; 

	//Array<T> * temp = new T[m_rows * columns]; 
	Array<T> temp(m_rows * columns);

	for(int i = 0; i < m_rows; i++)
	{
		for(int j = 0; j < min; j++)
		{
			temp[i * columns + j] = m_array[i * m_columns + j];
		}
	}

	m_array = temp; 
	m_columns = columns; 
}

template <typename T>
int Array2D<T>::getColumn() const
{
	return m_columns; 
}
#endif