/*************************************************************
* Author:		Chelsea Christison
* Filename:		Dijkstra's.h
* Date Created:	6.6.2017
*
**************************************************************/
#pragma once
#include <vector>
#include <iomanip>
using std::vector; 

#include "graph.h"

/************************************************************************
* Purpose:
*	This function runs is the algorithm for Dijkstras. It fills two 
*	vectors with the information needed to get from A to B with the 
*	shortest path possible
* Pre-Conditions:
*	g - pointer to graph
*	begin - place to begin at 
*	end - place to stop at
*************************************************************************/
template<typename V, typename E>
void Dijkstra(Graph<V, E> * g, V begin, V end)
{
	//two vector arrays distance, and predecessor
	vector<double> distance(g->getCount());
	vector<Vertex<V, E>*> predecessor(g->getCount());
	Vertex<V, E> * current = g->_searchGraph(begin);

	//set all values in distance to infinity 
	for (int i = 0; i < g->getCount(); i++)
		distance[i] = std::numeric_limits<double>::infinity();

	//set distance at begin vertex to 0
	distance[index(g, current)] = 0;
	int total = 0;
	for (int loop = 0; loop < g->getCount() - 1; loop++)
	{
		//consider all neighbors and update distance 
		for (Edge<V, E> e : *current)
		{
			Vertex<V, E> * nxt = e.getDestination();

			if (!nxt->isProcessed())
			{
				//calculate distance between current and nxt
				int dis = distance[index(g, current)] + e.getWeight();

				if (dis < distance[index(g, nxt)])
				{
					//update distance in vector
					distance[index(g, nxt)] = dis;
					//update predecessor vector with index
					predecessor[index(g, nxt)] = current;
				}
			}
		}

		//mark current as processed 
		current->setProcessed(true);

		int min = 100'000;

		//search distance array for the shortest unprocessed path
		for (int i = 0; i < g->getCount(); i++)
		{
			if (distance[i] < min)
			{
				Vertex<V, E> * v = atIndex(g, i);
				if (!v->isProcessed())
				{
					current = v;
					min = distance[i];
				}
			}
		}
		total += min;
	}

	printResults(distance, predecessor, g, begin, end); 
	g->_resetProcessed(); 
}

/************************************************************************
* Purpose:
*	This function prints the path from A to B
* Pre-Conditions:
*	distance - vector of distances
*	predecessor - vector of predecessor pointers 
*	g - pointer to graph
*	begin - place to begin
*	end - place to end 
*************************************************************************/
template<typename V, typename E>
void printResults(vector<double> distance, vector<Vertex<V, E>*> predecessor, Graph<V, E> * g, V begin, V end)
{
	stack<Vertex<V, E>*> stk;
	int finish = index(g, g->_searchGraph(end));
	
	Vertex<V, E> * v = g->_searchGraph(end);
	
	while (v != nullptr)
	{
		stk.push(v);

		//grab destination *
		v = predecessor[finish]; 

		//get the next destination index
		if(v)
			finish = index(g, v);

	} 
	double time = getTime(stk); 
	int miles = getWeight(stk); 

	cout << "BEGIN: "; 
	//display path from begin to end
	while(!stk.empty())
	{
		//pop first two 
		Vertex<V, E> * first = stk.top(); stk.pop(); 

		//output the first
		cout << first->getData() << " -> "; 
	}
	cout << " END " << endl << "Hours: "<< std::setprecision(2)<< std::fixed << time << endl; 
	cout << "Miles: " << miles << endl; 
}

/************************************************************************
* Purpose:
*	returns the time in hours taken to get from point A to B
* Pre-Conditions:
*	stk - stack with path from A to B
*************************************************************************/
template<typename V, typename E>
double getTime(stack<Vertex<V,E>*> stk)
{
	double time = 0.0f; 
	while (!stk.empty())
	{
		//pop
		Vertex<V, E> * first = stk.top(); stk.pop();
		
		if (!stk.empty())
		{
			Edge<V, E> * e = first->searchEdges(stk.top());
			if (e->getData() == "I-5")
				time += ((double)e->getWeight() / 65.00);
			else
				time += ((double)e->getWeight() / 55.00); 
		}
	}

	return time; 
}

/************************************************************************
* Purpose:
*	this function returns the total weight of the path from the stack
*	passed
* Pre-Conditions:
*	stk - stack with path from point A to B
*************************************************************************/
template<typename V, typename E>
int getWeight(stack<Vertex<V, E>*> stk)
{
	int weight = 0;
	while (!stk.empty())
	{
		//pop
		Vertex<V, E> * first = stk.top(); stk.pop();

		if (!stk.empty())
		{
			Edge<V, E> * e = first->searchEdges(stk.top());
			weight += e->getWeight(); 
		}
	}

	return weight;
}

/************************************************************************
* Purpose:
*	This function returns an integer of where in the graph the vertex ptr
*	is.
* Pre-Conditions:
*	g - pointer to graph
*	begin - vertex pointer to search for
*************************************************************************/
template<typename V, typename E>
int index(Graph<V, E> * g, Vertex<V, E> * begin)
{
	int i = 0;
	for (Vertex<V, E> v : *g)
	{
		if (v.getData() == begin->getData())
			break;

		i++;
	}
	return i; 
}

/************************************************************************
* Purpose:
*	This function returns a vertex ptr at the index given
*	
* Pre-Conditions:
*	g - pointer to graph
*	i - number of times to iterate
*************************************************************************/
template<typename V, typename E>
Vertex<V,E > * atIndex(Graph<V,E> * g, int i)
{
	Vertex<V, E> * ver = nullptr; 
	if(i < g->getCount())
	{
		int j = 0; 
		for (list<Vertex<V, E>>::iterator it = g->begin(); it != g->end(); ++it)
		{
			if(j == i)
			{
				ver = &(*it); 
			}
			j++;
		}
	}
	return ver; 
}

