/*************************************************************
* Author:		Chelsea Christison
* Filename:		main.cpp
* Date Created:	4/25/2017
* Modifications:
*
* Assignment: A7 - Circular Queue Array ADT
*
* Overview:
*	This program implements  circular queue using my array
*	class 
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::endl; 
#include"circular queue.h"

typedef bool(*FunctionPointer)();

//tests
bool test_overflow(); 
bool test_dequeue_accuracy(); 
bool test_dequeue_underflow(); 
bool test__dequeue_until_empty(); 
bool test_front_methd();
bool test_size_accuracy();


FunctionPointer test[] = { test_overflow, test_dequeue_accuracy, test_dequeue_underflow,
							test__dequeue_until_empty, test_front_methd, test_size_accuracy};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	for each(FunctionPointer func in test)
	{
		if (func())
			cout << " Passed" << endl;
		else
			cout << "*******Failed" << endl;
	}

	return 0; 
}

bool test_overflow()
{
	CQueue<int> queue(4); //four element queue
	bool pass = false; 

	cout << "Testing circular queue overflow error\n"; 

	try
	{
		for (int i = 0; i < 5; i++)
			queue.Enqueue(i); 
	}
	catch(Exception ex)
	{
		cout << ex.getMessage() << endl; 
		pass = true; 
	}

	cout << "Overflow queue error test "; 
	return pass; 
}

bool test_dequeue_accuracy()
{
	int test[] = { 0, 1, 2, 3, 4 };
	bool pass = true; 
	CQueue<int> Q(5); 

	for (int i = 0; i < 5; i++)
		Q.Enqueue(test[i]); 

	for(int i = 0; i < 5; i++)
	{
		if (Q.Dequeue() != test[i])
			pass = false; 
	}

	cout << "\nDequeue accuracy test "; 
	return pass; 
}

bool test_dequeue_underflow()
{
	CQueue<int> Q; 
	bool pass = false; 

	cout << "\nTesting dequeue underflow error\n"; 
	try
	{
		Q.Dequeue(); 
		Q.Dequeue(); 
	}
	catch(Exception ex)
	{
		cout << ex.getMessage() << endl; 
		pass = true; 
	}

	cout << "Underflow queue error test "; 
	return pass; 
}

bool test__dequeue_until_empty()
{
	int test[] = { 0, 1, 2, 3, 4 };
	bool pass = false;
	CQueue<int> Q(5);

	cout << "\nTesting dequeuing till empty\n";

	for (int i = 0; i < 5; i++)
		Q.Enqueue(test[i]);

	try
	{
		for (int i = 0; i < 6; i++)
			Q.Dequeue(); 	
	}
	catch(Exception ex)
	{
		cout << ex.getMessage() << endl; 
		pass = true; 
	}

	cout << "Underflow after emptying test "; 
	return pass; 
}

bool test_front_methd()
{
	int test[] = { 0, 1, 2, 3, 4 };
	int expected[] = { 42, 1, 2, 3, 4 };
	bool pass = true;
	CQueue<int> Q(5);

	for (int i = 0; i < 5; i++)
		Q.Enqueue(test[i]);

	Q.Front() = 42; 

	for (int i = 0; i < 5; i++)
	{
		if (Q.Dequeue() != expected[i])
			pass = false;
	}

	cout << "Front is expected value test ";
	return pass; 
}

bool test_size_accuracy()
{
	int test[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int total = 10; 
	bool pass = false;
	CQueue<int> Q(total);

	//10
	for (int i = 0; i < total; i++)
		Q.Enqueue(test[i]);

	//8
	for (int i = 0; i < 3; i++)
		Q.Dequeue(); 
	
	//10
	for (int i = 12; i < 15; i++)
		Q.Enqueue(i);

	if (Q.Size() == total)
		pass = true;

	cout << "\nMove Tail and Head, test size test "; 
	return pass;
}
