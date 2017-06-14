/*************************************************************
* Author:		Chelsea Christison
* Filename:		directory.h
* Date Created:	5.17.2017
*
* Modifications:
*
*************************
* Class: Directory
*
* Purpose:	
*	Data structure for holding contents of a directory from users computer.
*	Implements a node struct with a linked list of subdirectories (if 
*	applicable), a file name and path. 
*
* Manager functions:
*	Directory()
*	Directory(string rootdirectory)
*	Directory(const Directory& copy)
*	Directory& operator=(const Directory& rhs)
*	~Directory()
*
* Methods:
*	fillDirectory(char* dir, node & directory)
*		fills the directory starting with dir 
*	directoryExists(string dir)
*		finds if a directory exists inside the structure
*	listDirectory(string dir, bool recursive, string extension)
*	listDirectory(string dir, bool recursive)
*	listDirectory(string lookfor)
*	_recursiveSearch(string dir, node& directory, bool & found)
*	_recursiveSearch(string keyword, node & directory)
*	_iterateAll(node & directory)
*	_iterateAll(node & directory, string ext)
*	_iterateRecursive(node & directory, bool& subdir)
*	_iterateRecursive(node & directory, bool & subdir, string ext)
*	
*************************************************************************/
#ifndef directory_h
#define directory_h
#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::left; 
using std::right; 
using std::setfill;

#include "IO.h"


#include <string.h>
using std::string; 

#include "linkedlist.h"
#include "forwarditerator.h"


struct node
{
	LList<node> subdirectories;
	string filename;
	string path; 
};


class Directory
{
public:
	Directory(); 
	Directory(string rootdirectory); 
	Directory(const Directory& copy); 
	Directory& operator=(const Directory& rhs); 
	~Directory(); 

	void fillDirectory(char* dir, node & directory);
	bool directoryExists(string dir); 
	void listDirectory(string dir, bool recursive, string extension); 
	void listDirectory(string dir, bool recursive); 
	void listDirectory(string lookfor);
	
private:
	node m_root;
	ForwardIterator<node> traverse;
	node* _recursiveSearch(string dir, node& directory, bool & found); 
	void _recursiveSearch(string keyword, node & directory); 
	void _iterateAll(node & directory); 
	void _iterateAll(node & directory, string ext); 
	void _iterateRecursive(node & directory, bool& subdir);
	void _iterateRecursive(node & directory, bool & subdir, string ext); 
};
	
#endif