/************************************************************************
* Class: edge.h
*************************************************************************/
#ifndef EDGE_H
#define EDGE_H
#include <list>
using std::list;

template <typename V, typename E>
class Vertex; 

template <typename V, typename E>
class Edge
{
public:
	Edge<V, E>();
	Edge<V, E>(E data, int weight, Vertex<V, E> * dest = nullptr);
	Edge<V, E>(const Edge<V, E> & copy); 
	Edge<V, E>& operator=(const Edge<V, E>& rhs); 
	Vertex<V, E> * getDestination(); 
	E getData(); 
	int getWeight(); 
	~Edge<V, E>();

private:
	Vertex<V, E> * m_dest; 
	E m_data;
	int m_weight; 
};

template <typename V, typename E>
Edge<V, E>::Edge(): m_dest(nullptr), m_weight(0)
{}

template <typename V, typename E>
Edge<V, E>::Edge(E data, int weight, Vertex<V, E> * dest = nullptr): m_dest(dest), m_data(data), m_weight(weight)
{}

template <typename V, typename E>
Edge<V, E>::Edge(const Edge<V, E>& copy) : m_dest(copy.m_dest), m_data(copy.m_data), m_weight(copy.m_weight)
{}

template <typename V, typename E>
Edge<V, E>& Edge<V, E>::operator=(const Edge<V, E>& rhs)
{
	if(this != &rhs)
	{
		m_dest = nullptr; 
		*m_dest = *rhs.m_dest; 
		m_data = rhs.m_data; 
		m_weight = rhs.m_weight; 
	}
	return *this; 
}

template <typename V, typename E>
Vertex<V, E>* Edge<V, E>::getDestination()
{
	return m_dest; 
}

template <typename V, typename E>
E Edge<V, E>::getData()
{
	return m_data; 
}

template <typename V, typename E>
int Edge<V, E>::getWeight()
{
	return m_weight; 
}

template <typename V, typename E>
Edge<V, E>::~Edge()
{}

#endif
