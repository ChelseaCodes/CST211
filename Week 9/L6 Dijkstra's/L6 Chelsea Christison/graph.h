/************************************************************************
* Class: graph.h
*************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H 
#include <queue>
using std::queue;

#include<stack>
using std::stack; 

#include "edge.h"
#include "vertex.h"

template <typename V, typename E>
class Graph
{
public:
	Graph<V, E>();
	Graph<V, E>(const Graph<V, E> & copy); 
	Graph<V, E> & operator=(const Graph<V, E> & rhs); 
	~Graph<V, E>();

	void InsertVertex(V vertex); 
	void DeleteVertex(V vertex); 
	void InsertEdge(V from, V to, E edge, int weight);
	void DeleteEdge(V from, V to);
	bool isEmpty();
	int getCount() const; 
	void BreadthFirst(void (*visit)(V));
	void DepthFirst(void(*visit)(V));
	typename list<Vertex<V, E>>::iterator begin(); 
	typename list<Vertex<V, E>>::iterator end();

	list<Vertex<V, E>>* getVertices(); 
	Vertex<V, E>* getFirstUnprocessed(); 
	Vertex<V, E>* _searchGraph(const V vertex);
	void _resetProcessed();

private:
	list<Vertex<V, E>> m_vertices;
	int m_count; //number of vertices in graph  
	
};

template <typename V, typename E>
Graph<V, E>::Graph():  m_count(0)
{}

template <typename V, typename E>
Graph<V, E>::Graph(const Graph<V, E>& copy): m_count(copy.m_count)
{
	//loop for every vertex in copy
	for(Vertex<V,E> v : copy.m_vertices)
	{
		//if v isn't in the graph insert
		if(!_searchGraph(v.getData()))
			InsertVertex(v.getData());

		//get pointer of inserted, or current node in this
		Vertex<V, E> * inserted = _searchGraph(v.getData());

		//loop for all edges in v - from copy
		for(Edge<V,E> e : *v.getEdges())
		{
			Vertex<V, E> * vTo = e.getDestination();	//get dest ptr 

			Edge<V, E> * check = inserted->searchEdges(vTo);	//search edges in current node

			//if edge isn't existent in edge list
			if (!check)
			{	
				//dest ptr isn't in the graph yet - make it
				if (!_searchGraph(vTo->getData()))
					InsertVertex(vTo->getData());

				//grab destination vertex from this graph
				Vertex<V, E> * made = _searchGraph(vTo->getData());

				//insert the new edge between the two
				InsertEdge(inserted->getData(), made->getData(), e.getData(), e.getWeight());
			}
		}
	}
}

template <typename V, typename E>
Graph<V, E>& Graph<V, E>::operator=(const Graph<V, E>& rhs)
{
	if(this != &rhs)
	{
		m_vertices.clear(); 

		for (Vertex<V, E> v : rhs.m_vertices)
		{
			if (!_searchGraph(v.getData()))
				InsertVertex(v.getData());

			Vertex<V, E> * inserted = _searchGraph(v.getData());
			inserted->setProcessed(true);

			for (Edge<V, E> e : *v.getEdges())
			{
				Vertex<V, E> * vTo = e.getDestination();

				Edge<V, E> * check = inserted->searchEdges(vTo);

				if (!check)
				{
					if (!_searchGraph(vTo->getData()))
						InsertVertex(vTo->getData());

					Vertex<V, E> * made = _searchGraph(vTo->getData());
					made->setProcessed(true);
					vTo->setProcessed(true);

					InsertEdge(inserted->getData(), made->getData(), e.getData(), e.getWeight());
				}
			}
		}
		m_count = rhs.m_count; 
	}
	return *this; 
}

template <typename V, typename E>
Graph<V, E>::~Graph()
{}

/**********************************************************************
* Purpose:
*	This function takes the vertex type passed and inserts into the 
*	list of vertices. 	
* Precondition:
*	vertex - vertex to insert into graph 
* Postcondition:
*	graph is modified
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::InsertVertex(V vertex)
{
	if(!_searchGraph(vertex))
	{
		m_vertices.push_back(Vertex<V, E>(vertex)); //insert into the list of vertices 
		m_count++;
	}
}

/**********************************************************************
* Purpose:
*	This function deletes a vertex from the graph, removing itself from 
*	any edges for any other vertices. 
* Precondition:
*	vertex - vertex to delete
* Postcondition:
*	deletes a vertex from the graph
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::DeleteVertex(V vertex)
{
	Vertex<V, E> * vDelete = _searchGraph(vertex); //search for vertex in graph 

	//if vertex exists in graph
	if (vDelete)
	{
		int i = 0;
		list<Vertex<V, E>>::iterator del; 

		//erase vertex from edges in graph first
		for(list<Vertex<V, E>>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
		{
			Vertex<V, E> * v = &(*it);
			//set del to vertex being deleted
			if (vDelete->getData() == v->getData())	
				del = it; 

			v->DeleteEdge(vDelete);
			i++; 
		}

		m_vertices.erase(del); //erase the actual vertex
	}
}

/**********************************************************************
* Purpose:
*	This function inserts an edge object between two V data specified.
* Precondition:
*	from - type V in graph to insert edge
*	to - type V in graph to insert edge
*	edge - type E in graph that represents edge
*	miles - miles of edge to create edge
* Postcondition:
*	Adds an edge between two vertices. 
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::InsertEdge(V from, V to, E edge, int weight)
{
	Vertex<V, E> * vFrom = _searchGraph(from);
	Vertex<V, E> * vTo = _searchGraph(to); 
	
	//if vFrom and vTo isn't null 
	if(vFrom && vTo)
	{
		//insert edge going to TO (from From)
		vFrom->InsertEdge(Edge<V, E>(edge, weight, vTo));

		//insert edge going to From (from TO)
		vTo->InsertEdge(Edge<V, E>(edge, weight, vFrom));
	}	
}

/**********************************************************************
* Purpose:
*	This function deletes an edge between two V data representing 
*	vertices in graph. *
* Precondition:
*	from - first vertex to delete edge from
*	to - second vertex to delete edge from 
* Postcondition:
*	deletes an edge between two vertices, removing it from their list of
*	Edges. 
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::DeleteEdge(V from, V to)
{
	Vertex<V, E> * vFrom = _searchGraph(from);
	Vertex<V, E> * vTo = _searchGraph(to);

	vFrom->DeleteEdge(vTo); 
	vTo->DeleteEdge(vFrom); 
}

/**********************************************************************
* Purpose:
*	This function returns a boolean representing an empty graph
************************************************************************/
template <typename V, typename E>
bool Graph<V, E>::isEmpty()
{
	return m_vertices.empty() && m_count == 0;		
}

template <typename V, typename E>
int Graph<V, E>::getCount() const
{
	return m_count; 
}

/**********************************************************************
* Purpose:
*	This function traverses graph using breadth first traversal, and
*	outputs vertices to console.
* Precondition:
*	visit - function pointer to output function
* Postcondition:
*	Outputs vertices to console. Resets processed boolean in vertices
*	to false after.
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::BreadthFirst(void(* visit)(V))
{
	_resetProcessed(); 
	queue<Vertex<V, E> *> Q; 
	Vertex<V, E> * v = nullptr; 
	list<Vertex<V, E>>::iterator it = m_vertices.begin();
	
	Q.push(&(*it)); 

	while(!Q.empty() && it != m_vertices.end())
	{
		v = Q.front(); 
		Q.pop(); 
		if(!v->isProcessed())
			visit(v->getData()); 

		v->setProcessed(true); 

		for(list<Edge<V, E>>::iterator eIt = v->getEdges()->begin(); eIt != v->getEdges()->end(); ++eIt)
		{
			Edge<V, E> * e = &(*eIt); 
			Q.push(e->getDestination()); 
		}
		++it; 
	}
	_resetProcessed(); 
}

/**********************************************************************
* Purpose:
*	This function traverses the graph using depth first traversal to 
*	output vertices. 
* Precondition:
*	visit - function pointer to output function
* Postcondition:
*	Outputs vertices to console. Resets processed boolean in vertices 
*	to false after. 
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::DepthFirst(void(* visit)(V))
{
	_resetProcessed();
	stack<Vertex<V, E> *> Stk; 
	Vertex<V, E> * v = nullptr; 
	list<Vertex<V, E>>::iterator it = m_vertices.begin(); 

	Stk.push(&(*it));	//push vertex on the stack 
	while (!Stk.empty())
	{
		v = Stk.top(); 
		Stk.pop(); 

		if (!v->isProcessed())
			visit(v->getData()); 

		v->setProcessed(true); 

		for (list<Edge<V, E>>::iterator eIt = v->begin(); eIt != v->end(); ++eIt)
		{
			Edge<V, E> * e = &(*eIt); 
			if(!e->getDestination()->isProcessed())	//push non processed vertices 
				Stk.push(e->getDestination()); 
		}
	}
	_resetProcessed(); 
}

template <typename V, typename E>
typename list<Vertex<V, E>>::iterator Graph<V, E>::begin()
{
	return m_vertices.begin();
}

template <typename V, typename E>
typename list<Vertex<V, E>>::iterator Graph<V, E>::end()
{
	return m_vertices.end(); 
}

template <typename V, typename E>
list<Vertex<V, E>>* Graph<V, E>::getVertices()
{
	return &m_vertices; 
}

template <typename V, typename E>
Vertex<V, E>* Graph<V, E>::getFirstUnprocessed()
{
	for(Vertex<V,E> e: m_vertices.begin())
	{
		if (!e.isProcessed())
			return e; 
	}
	return  nullptr; 
	 
}

/**********************************************************************
* Purpose:
*	This function searches graph linearly beginning with the first 
*	vertex. returns a pointer to the vertex found
* Precondition:
*	vertex - vertex data to search for in graph
* Postcondition:
*	returns pointer to vertex in graph, or nullptr if vertex isn't found
************************************************************************/
template <typename V, typename E>
Vertex<V, E>* Graph<V, E>::_searchGraph(const V vertex)
{
	bool found = false; 
	Vertex<V, E> * v = nullptr; 

	for(list<Vertex<V, E>>::iterator it = m_vertices.begin(); it != m_vertices.end() && !found; ++it)
	{
		v = &(*it); 
		if (v->getData() == vertex)
			found = true; 
	}
	if (!found)
		v = nullptr; 

	return v; 
}

/**********************************************************************
* Purpose:
*	This function resets the processed data member of every vertices 
*	to false.
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::_resetProcessed()
{
	Vertex<V, E> * v = nullptr;

	for (list<Vertex<V, E>>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		v = &(*it); 
		v->setProcessed(false); 
	}
}
#endif
