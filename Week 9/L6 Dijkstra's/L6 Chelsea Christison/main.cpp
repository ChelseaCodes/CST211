/*************************************************************
* Author:			Chelsea Christison
* Date Created:		6.6.2017
*
* Lab/Assignment: Lab 6 - Dijkstra's Path
*
* Overview:
*	This program reads in a txt file to a graph structure
*	and finds the shortest path from A to B. 
*
* Input:
*	The input is a txt file in the format of 
*	begin spot/ end spot/ highway/ miles
*	ex.
*		Lakeside,Reedsport,Hwy 101,11
*		Roseburg,Sutherlin,I-5,11
*		Sutherlin,Elkton,Hwy 138,27
*
* Output:
*	The output of this program is the shortest path from 
*	point A to point B
*
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include<iostream>
using std::cout; 
using std::cin; 
using std::endl; 

#include <string>
using std::string; 

#include <fstream>
using std::ifstream; 

#include "Dijkstra's.h"

struct Spot
{
	string name; 
};

struct Hwy
{
	string name; 
	int miles; 
};


/* overloaded operators for structs */
inline bool operator==(const Spot & a, const Spot & b)
{
	return a.name == b.name; 
}

inline bool operator==(const Hwy & a, const Hwy & b)
{
	return a.name == b.name; 
}
inline bool operator==(const Hwy & a, const string b)
{
	return a.name == b; 
}

inline std::ostream& operator<<(std::ostream & o, Spot & s)
{
	return	o << s.name;
}

/* functions */
void Read(Graph<Spot, Hwy> * graph);
void output(Spot sp); 
string getInput(); 
void processDijkstra(Graph<Spot, Hwy> * graph);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<Spot, Hwy> graph; 

	Read(&graph); 

	processDijkstra(&graph); 

	return 0; 
}

/************************************************************************
* Purpose:
*	This function reads the text file into the graph structure
* Pre-Conditions:
*	graph - graph to fill with information from file
* Post-Conditions:
*	graph is filled with vertices 
*************************************************************************/
void Read(Graph<Spot, Hwy> * graph)
{
	ifstream read("lab06.txt"); 

	while(read.is_open())
	{
		while(read.good())
		{
			while (!read.eof())
			{
				Spot sp1;
				Spot sp2;
				Hwy hwy;
				char buff1[100] = {'\0'};
				char buff2[100] = { '\0' };
				char buff3[100] = { '\0' };

				read.getline(buff1, 100, ','); 
				read.getline(buff2, 100, ','); 
				read.getline(buff3, 100, ','); 
				read >> hwy.miles; 

				sp1.name = buff1; 
				sp2.name = buff2; 
				hwy.name = buff3; 
				
				if (sp1.name.find_first_of('\n') != string::npos)
					sp1.name = sp1.name.substr(1); 

				/* insert the two locations */
				graph->InsertVertex(sp1); 
				graph->InsertVertex(sp2); 
				graph->InsertEdge(sp1, sp2, hwy, hwy.miles); 
			}
		}

		read.close(); 
	}
}

void output(Spot sp)
{
	cout << sp.name << endl; 
}

string getInput()
{
	string input;
	char s[100] = {'\0'};

	cin.ignore(cin.rdbuf()->in_avail()); 
	cin.getline(s, 100);
	cin.clear(); 
	cin.ignore(cin.rdbuf()->in_avail());

	input = s; 
	cout << endl; 
	return input; 
}

void processDijkstra(Graph<Spot, Hwy> * graph)
{	
	char in; 
	do
	{
		cout << "From: ";
		string frm = getInput();
		cout << "To: ";
		string to = getInput();

		Spot s1, s2;
		s1.name = frm;
		s2.name = to;

		if (graph->_searchGraph(s1) && graph->_searchGraph(s2))
		{
			Dijkstra(graph, s1, s2);
			cout << "continue? (y/n)";
			cin >> in;
		}
		else
		{
			cout << "Spot doesn't exist - try again\n" << endl; 
			in = 'Y'; 
		}
		
	} while (in != 'n');
}
