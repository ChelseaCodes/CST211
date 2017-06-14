/************************************************************************
* Class: vertex.h
*************************************************************************/
#ifndef VERTEX_H
#define VERTEX_H

template <typename V, typename E>
class Edge; 

template <typename V, typename E>
class Vertex
{
public:
	Vertex<V, E>(); 
	Vertex<V, E>(V data); 
	Vertex<V, E>(const Vertex<V, E> & copy); 
	Vertex<V, E> & operator=(const Vertex<V, E> & rhs); 
	~Vertex<V, E>();

	V getData(); 
	//list<Edge<V, E>> * getEdges(); 
	typename list<Edge<V, E>>::iterator begin(); 
	typename list<Edge<V, E>>::iterator end(); 
	bool isProcessed() const; 
	void setProcessed(bool set); 
	void InsertEdge(Edge<V, E> edge);
	void DeleteEdge(Vertex<V, E>* dest);
	Edge<V, E> * searchEdges(Vertex<V, E>* dest);
	void testEdgesOp(); 
private:
	list<Edge<V, E>> m_edges; 
	V m_data; 
	bool m_processed; 
	int m_degree; //number of edges connected 
};

template <typename V, typename E>
Vertex<V, E>::Vertex(): m_edges(0), m_processed(false), m_degree(0)
{}

template <typename V, typename E>
Vertex<V, E>::Vertex(V data) : m_edges(0), m_data(data), m_processed(false), m_degree(0)
{}

template <typename V, typename E>
Vertex<V, E>::Vertex(const Vertex<V, E>& copy) : m_edges(copy.m_edges), m_data(copy.m_data), 
	m_processed(copy.m_processed), m_degree(copy.m_degree)
{}

template <typename V, typename E>
Vertex<V, E>& Vertex<V, E>::operator=(const Vertex<V, E>& rhs)
{
	if(this != & rhs)
	{
		for (Edge<V,E> e : rhs.m_edges)
		{
			m_edges.push_back(e);
		}

		m_data = rhs.m_data; 
		m_processed = rhs.m_processed; 
		m_degree = rhs.m_degree; 
	}
	return *this; 
}

template <typename V, typename E>
V Vertex<V, E>::getData()
{
	return m_data; 
}

template <typename V, typename E>
typename list<Edge<V, E>>::iterator Vertex<V, E>::begin()
{
	return m_edges.begin(); 
}

template <typename V, typename E>
typename list<Edge<V, E>>::iterator Vertex<V, E>::end()
{
	return m_edges.end(); 
}

template <typename V, typename E>
bool Vertex<V, E>::isProcessed() const
{
	return m_processed; 
}

template <typename V, typename E>
void Vertex<V, E>::setProcessed(bool set)
{
	m_processed = set; 
}

/**********************************************************************
* Purpose:
*	This function inserts an edge to the list of edges
************************************************************************/
template <typename V, typename E>
void Vertex<V, E>::InsertEdge(Edge<V, E> edge)
{
	m_edges.push_back(edge); 
	m_degree++;
}

/**********************************************************************
* Purpose:
*	This function removes edge from list that has matching destination
*	vertex of the one passed. 
* Precondition:
*	dest - vertex pointer that is going to be deleted
* Postcondition:
*	removes edges from list
************************************************************************/
template <typename V, typename E>
void Vertex<V, E>::DeleteEdge(Vertex<V, E>* dest)
{
	list<Edge<V, E>>::iterator it = m_edges.begin();
	int num = m_edges.size();	//original size of list
	bool erased = false; 

	//search all edges for the destination to delete 
	for(int i = 0; i < num && ! erased ; i++)
	{
		Edge<V, E> * e = &(*it);
		if (e->getDestination() == dest)
		{
			m_edges.erase(it);
			num = m_edges.size();	//update size of list 
			erased = true;
		}
		else
			++it;
	}
}

template <typename V, typename E>
Edge<V, E>* Vertex<V, E>::searchEdges(Vertex<V, E>* dest)
{
	bool found = false;
	Edge<V, E> * e = nullptr;

	for (list<Edge<V, E>>::iterator it = m_edges.begin(); it != m_edges.end() && !found; ++it)
	{
		e = &(*it);
		if (e->getDestination()->getData() == dest->getData())
		{
			found = true;
		}
	}
	if (!found)
		e = nullptr; 
	return e;
}

template <typename V, typename E>
void Vertex<V, E>::testEdgesOp()
{
	Edge<V, E> e = m_edges.front(); 
	Edge<V, E> l = e; 
}

template <typename V, typename E>
Vertex<V, E>::~Vertex()
{}

#endif
