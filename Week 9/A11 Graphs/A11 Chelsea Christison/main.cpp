/*************************************************************
* Author:			Chelsea Christison
* Date Created:		5.31.2017
*
* Lab/Assignment: 11 - Graphs
*
* Overview:
*	This program 
*
* Input:
*	
*
* Output:
*	
*
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "graph.h"
#include <string>
#include <iostream>
using std::string; 



struct Hwy
{
	int number; 
};

struct City
{
	string name; 
	int population; 
};

inline bool operator==(const City & lhs, const City & rhs)
{
	return lhs.name == rhs.name && lhs.population == rhs.population; 
}

inline bool operator==(const Hwy & lhs, const Hwy & rhs)
{
	return lhs.number == rhs.number; 
}

typedef void(*out)(City);
void output(City data); 
Graph<City, Hwy>& GetGraph();

/* Tests 
 *	- insert node
 *	- delete node 
 *	- insert arcs
 *	- delete arcs
 *	- Displays 
 */

bool InsertVertexTest();
void InsertEdgeTest(); 
bool DeleteVertexTest(); 
void DeleteEdgeTest(); 


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InsertEdgeTest(); 
	DeleteEdgeTest(); 
	if (InsertVertexTest())
		std::cout << "Insert Vertex Test Pass" << std::endl;
	else
		std::cout << "Insert Vertex Test FAILED" << std::endl; 

	if(DeleteVertexTest())
		std::cout << "Delete Vertex Test Pass" << std::endl;
	else
		std::cout << "Delete Vertex Test FAILED" << std::endl;

	return 0; 
}
void output(City data)
{
	std::cout << data.name << "\nPopulation: " << data.population << std::endl; 
}

bool InsertVertexTest()
{
	Graph<City, Hwy> graph; 
	bool pass = false;

	/* city to insert */
	City G;
	G.name = "Groton";
	G.population = 13'000;

	graph.InsertVertex(G); 
	
	if (graph.getCount() > 0)
		pass = true; 

	return pass; 
}

void InsertEdgeTest()
{
	Graph<City, Hwy> graph; 
	bool pass = false; 

	/* Cites to insert */
	City G;
	G.name = "Groton";
	G.population = 13'000;
	City NH;
	NH.name = "New Haven";
	NH.population = 13'000;

	graph.InsertVertex(G); 
	graph.InsertVertex(NH); 

	/* Highway to insert */
	Hwy one;
	one.number = 1;

	/* adding edge */
	graph.InsertEdge(G, NH, one, 14); 
	
	/* output number of edges (degree) of each city */
	std::cout << "Insert Edge:\nDegree: Groton == 1, New Haven == 1" << std::endl; 
	graph.displayDegreeCount(output); 
	std::cout << "-----------------------------------------------\n"; 
	//check output to have number 1
}

bool DeleteVertexTest()
{
	Graph<City, Hwy> graph;
	bool pass = false;

	/* Cites to insert */
	City G;
	G.name = "Groton";
	G.population = 13'000;
	City NH;
	NH.name = "New Haven";
	NH.population = 13'000;
	City M;
	M.name = "Mystic";
	M.population = 10'000;

	graph.InsertVertex(G);
	graph.InsertVertex(NH);
	graph.InsertVertex(M); 

	/* Highway to insert */
	Hwy one;
	one.number = 1;
	Hwy two;
	two.number = 2; 

	/* adding edge */
	graph.InsertEdge(G, NH, one, 14); //Hwy1 from Groton to New Haven
	graph.InsertEdge(NH, M, two, 30); //Hwy2 from New Haven to Mystic
	
	/* delete new Haven */
	graph.DeleteVertex(NH); 
	if (graph.getCount() == 2)
		pass = true; 
	
	return pass; 
}

void DeleteEdgeTest()
{
	Graph<City, Hwy> graph;
	bool pass = false;

	/* Cites to insert */
	City G;
	G.name = "Groton";
	G.population = 13'000;
	City NH;
	NH.name = "New Haven";
	NH.population = 13'000;
	City M;
	M.name = "Mystic";
	M.population = 10'000;

	graph.InsertVertex(G);
	graph.InsertVertex(NH);
	graph.InsertVertex(M);

	/* Highway to insert */
	Hwy one;
	one.number = 1;
	Hwy two;
	two.number = 2;

	/* adding edge */
	graph.InsertEdge(G, NH, one, 14); //Hwy1 from Groton to New Haven
	graph.InsertEdge(NH, M, two, 30); //Hwy2 from New Haven to Mystic

	/* delete edge from New Haven to Mystic */
	std::cout << "Delete Edge: \n"; 
	graph.DeleteEdge(NH, M); 

	std::cout << "Degree count: New Haven == 1, Mystic == 0\n"; 
	graph.displayDegreeCount(output); 
	std::cout << "--------------------------------------------\n"; 
	//ensure degree count from NH == 1, and M == 0; 
}

Graph<City, Hwy>& GetGraph()
{
	/* Highways to insert */
	Hwy one;
	one.number = 1;

	Hwy two;
	two.number = 2;

	Hwy three;
	three.number = 3;

	/* Cities to insert */
	City G;
	G.name = "Groton";
	G.population = 13'000;

	City NL;
	NL.name = "New London";
	NL.population = 12'000;

	City M;
	M.name = "Mystic";
	M.population = 10'000;

	City NH;
	NH.name = "New Haven";
	NH.population = 13'000;

	City N;
	N.name = "Newport";
	N.population = 1'300;

	/* Create Vertices */
	Graph<City, Hwy> Con;
	Con.InsertVertex(G);
	Con.InsertVertex(NL);
	Con.InsertVertex(M);
	Con.InsertVertex(NH);
	Con.InsertVertex(N);
	
	/* Add edges (highways) */
	Con.InsertEdge(G, NL, one, 15);		//Highway from Groton to New London named "one" that is 15mi
	Con.InsertEdge(NL, M, two, 20);		//Hwy from New London to Mystic named "two" that is 20mi
	Con.InsertEdge(G, M, three, 5);
	Con.InsertEdge(G, NH, two, 30);
	Con.InsertEdge(G, N, three, 16);


	return Con;
}
