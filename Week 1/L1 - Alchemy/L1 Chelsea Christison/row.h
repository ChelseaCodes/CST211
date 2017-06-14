/*************************************************************
* Author:		Chelsea Christison
* Filename:		row.h
* Date Created:	4.7.2017
*
* Modifications:
* *****
* Class: Row
*
* Purpose: Helper class to access Array2D via [][]
*
* Manager functions:
*	Row()
*	Row(Array2D<T>& array, int row)
*	Row(const Array2D<T>& array, int row)
*	~Row()
*
* Methods:
*	const T& operator [](int column) const
*		calls Arry2D obj's Select() function to return selected element, const
*	T& operator [](int column)
*		calls Array2D obj's Select() func to return selected element
*************************************************************************/
#ifndef ROW_H
#define ROW_H

template <typename T>
class Row
{
public:
	Row(); 
	Row(Array2D<T>& array, int row); 
	Row(const Array2D<T>& array, int row); 
	const T& operator [](int column) const;
	T& operator [](int column); 
	~Row(); 
private:
	Array2D<T>& m_array2D; 
	int m_row;
};
#endif

template <typename T>
Row<T>::Row(): m_row(0)
{}
template <typename T>
Row<T>::Row(Array2D<T>& array, int row) : m_array2D(array), m_row(row)
{}

template <typename T>
Row<T>::Row(const Array2D<T>& array, int row):m_array2D(const_cast<Array2D<T>&>(array)), m_row(row)
{}

template <typename T>
const T& Row<T>::operator[](int column) const
{
	return m_array2D.Select(m_row, column); 
}

template <typename T>
T& Row<T>::operator[](int column)
{
	return m_array2D.Select(m_row, column);
}

template <typename T>
Row<T>::~Row()
{
	m_row = 0; 
}
