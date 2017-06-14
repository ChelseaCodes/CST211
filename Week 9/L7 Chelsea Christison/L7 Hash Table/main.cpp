/*************************************************************
* Author:			Chelsea Christison
* Date Created:		6.9.2017
*
* Lab/Assignment: Lab 7 - Hash Table 
* Overview:
*	This program implements a Hash Table, tested with a 
*	Book structure. 
* Input:
*	Book struct information, with ISBN number as the key
* Output:
*	Traversal of the Hash Table 
************************************************************/
#include <iostream> 
using std::cout;
using std::cin; 
using std::endl; 
#include <string>
using std::string; 

#include "hashtable.h"
#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define FIRSTH 37 /* also prime */

/* struct for Book */
struct Book
{
	string m_title; 
	string m_author; 
	int m_pages; 
};
/* function pointers */
typedef int(*hash)(string);
typedef void(*out)(Book);

/* functions */
int hashFunction(string ISBN);
int primehashFunction(string ISBN);
void output(Book b);

/* set function pointers */
hash h = hashFunction;
hash y = primehashFunction;
out o = output; 

const int size = 5; 
int main()
{
	HashTable<string, Book> table(h, size); 

	/* books to insert */
	Book temp = { "C++: Active", "Randal Albert", 633 };
	table.Insert("0763757233", temp); 
	Book temp2 = { "Rodeo for DumDums", "Calvin Caldwell", 1 };
	table.Insert("7063757233", temp2);
	Book temp3 = { "and That n There", "Ralph Carestia", 23 }; 
	table.Insert("7063757234", temp3); 

	/* output the original Table */
	cout << "   /* Original Table */" << endl; 
	table.Traverse(o); 

	/* reset the hash algorithm, and output again */
	table.setHash(y); 
	cout << "_____________________" << endl; 
	cout << "\n /*  Reset Hash  */ " << endl; 
	table.Traverse(o); 


	/* test op[] */
	cout << "Testing op[]\n" << table["7063757234"].m_pages << endl; 


	/* test delete */
	table.Delete("7063757234"); 

	return 0; 
}

void output(Book b)
{
	cout << "Author: " << b.m_author << "\nTitle: " << b.m_title << "\nPages: "
		<< b.m_pages << endl; 
}

int hashFunction(string ISBN)
{
	int hash = 0; 

	for(char a : ISBN)
		hash += static_cast<int>(a);
	
	return hash % size;;
}

int primehashFunction(string ISBN)
{
	int hash = FIRSTH;
	for(char a : ISBN)
		hash = ( hash * A) ^ (a * B);

	return abs(hash % size);
}