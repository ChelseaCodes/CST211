/*************************************************************
* Author:		Chelsea Christison
* Filename:		main.cpp
* Date Created:	4/25/2017
* Modifications:
*
* Assignment: A8 - Queue Linked List
*
* Overview:
*	This program implements a queue using linked list and 
*	tests the methods of the queue. 
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::endl; 
#include "LQueue.h"

typedef bool(*FunctionPointer)();

//tests
bool test_underflow();
bool test_dequeue_accuracy();
bool test__dequeue_until_empty();
bool test_front_methd();
bool test_size_accuracy();


FunctionPointer test[] = {  test_underflow, test_dequeue_accuracy,
test__dequeue_until_empty, test_front_methd, test_size_accuracy };

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

bool test_underflow()
{
	LQueue<int> Q; 
	bool pass = false; 

	cout << "Testing underflow error\n";

	try
	{
		Q.Dequeue(); 
	}
	catch(Exception ex)
	{
		cout << "Error:  " << ex.getMessage() << endl; 
		pass = true; 
	}

	cout << "underflow test ";
	return pass; 
}

bool test_dequeue_accuracy()
{
	int test[] = { 0, 1, 2, 3};
	bool pass = true;
	int num_nodes = 4; 

	LQueue<int> Q;

	for (int i = 0; i < num_nodes; i++)
		Q.Enqueue(test[i]);

	for (int i = 0; i < num_nodes; i++)
	{
		if (Q.Dequeue() != test[i])
			pass = false;
	}

	cout << "\nDequeue accuracy test ";
	return pass;
}

bool test__dequeue_until_empty()
{
	int test[] = { 0, 1, 2, 3, 4 };
	bool pass = false;
	int num_nodes = 5; 
	LQueue<int> Q;

	cout << "\nTesting dequeuing till empty\n";

	for (int i = 0; i < num_nodes; i++)
		Q.Enqueue(test[i]);

	try
	{
		for (int i = 0; i < num_nodes + 1; i++)
			Q.Dequeue();
	}
	catch (Exception ex)
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
	int num_nodes = 5; 
	LQueue<int> Q;

	for (int i = 0; i < num_nodes; i++)
		Q.Enqueue(test[i]);

	Q.Front() = 42;

	for (int i = 0; i < num_nodes; i++)
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
	int expected_num = 4; 
	bool pass = false;
	LQueue<int> Q;

	//10
	for (int i = 0; i < total; i++)
		Q.Enqueue(test[i]);

	//8
	for (int i = 0; i < 3; i++)
		Q.Dequeue();

	//10
	for (int i = 12; i < 15; i++)
		Q.Enqueue(i);

	//4
	for (int i = 0; i < 6; i++)
		Q.Dequeue(); 

	if (Q.Size() == expected_num)
		pass = true;

	cout << "\nMove Tail and Head, test size test ";
	return pass;
}
