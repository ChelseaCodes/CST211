/*************************************************************
* Author:		Chelsea Christison
* Filename:		main.cpp
* Date Created:	4/24/2017
* Modifications:
*
* Assignment: A56- Stack ADT Linked List
*
* Overview:
*	This program implements a stack using my linked list 
*	class. 
*
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <time.h>
#include <iostream>
#include <iomanip>
using std::cout;

#include "lstack.h"

typedef bool(*FunctionPointer)();

bool test_UnderflowException_Pop();
bool test_UnderflowException_Peek();
void time_fillANDempty_liststack();

FunctionPointer test_functions[] = {  test_UnderflowException_Pop, test_UnderflowException_Peek };
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));				//seed random generator

	for each(FunctionPointer func in test_functions)
	{
		if (func())
			cout << " Passed" << endl;
		else
			cout << "*******Failed" << endl;
	}

	time_fillANDempty_liststack();

	return 0;
}


bool test_UnderflowException_Pop()
{
	LStack<int> stack; //create a stack of four
	bool exception = false;

	try
	{
		stack.Pop();
	}
	catch (Exception ex)
	{
		exception = true;
	}

	cout << "test underflow exception on pop";
	return exception;
}

bool test_UnderflowException_Peek()
{
	LStack<int> stack; //create a stack of four
	bool exception = false;

	try
	{
		stack.Peek();
	}
	catch (Exception ex)
	{
		exception = true;
	}

	cout << "test underflow exception on peek";
	return exception;
}

void time_fillANDempty_liststack()
{
	int random_number = 0;			//integer used to fill array
	LStack<int> stack;

	cout << "\nTiming filling stack with 100,000 numbers" << endl;

	clock_t start = clock();
	for (int i = 0; i < 100'000; i++)
	{
		random_number = rand() % 100;
		stack.Push(random_number);
	}
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;

	cout << "Time Elapsed: " << std::setprecision(4)
		<< std::fixed << elapsed << " seconds" << endl;
	cout << "Stack size: " << stack.Size() << endl;

	cout << "\nTiming emptying same stack" << endl;
	start = clock();
	for (int i = 0; i < 100'000; i++)
	{
		stack.Pop();
	}
	stop = clock();

	//determine duration
	elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;

	cout << "Time Elapsed: " << std::setprecision(4)
		<< std::fixed << elapsed << " seconds" << endl;
	cout << "Stack size: " << stack.Size() << endl;

}
