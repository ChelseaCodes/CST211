/*************************************************************
* Author:		Chelsea Christison
* Filename:		main.cpp
* Date Created:	4/24/2017
* Modifications:
*
* Assignment: A5 - Stack ADT Array 
*
* Overview:
*	This program implements a stack using my Array class
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <time.h>
#include <iostream>
#include <iomanip>
using std::cout;
#include "stack.h"
typedef bool(*FunctionPointer)();

bool test_OverflowException_Push();
bool test_UnderflowException_Pop();
bool test_UnderflowException_Peek();

void time_fillANDempty_dynamically(); 
void time_fillANDempty_stack();

FunctionPointer test_functions[] = { test_OverflowException_Push, test_UnderflowException_Pop, test_UnderflowException_Peek };
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));				//seed random generator
	
	for each(FunctionPointer func in test_functions)
	{
		if(func())
			cout << " Passed" << endl; 
		else
			cout << "*******Failed" << endl; 
	}
	
	time_fillANDempty_stack();
	time_fillANDempty_dynamically(); 
	return 0; 
}

bool test_OverflowException_Push()
{
	Stack<int> stack(4); //create a stack of four
	bool exception = false;

	for(int i(0); i < 4; i++)
		stack.Push(i); 
	
	try
	{
		stack.Push(3); 
	}
	catch(Exception ex)
	{
		exception = true;
	}

	cout << "test overflow exception on push";
	return exception; 
}

bool test_UnderflowException_Pop()
{
	Stack<int> stack(4); //create a stack of four
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
	Stack<int> stack(4); //create a stack of four
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

void time_fillANDempty_dynamically()
{
	int random_number = 0;			//integer used to fill array
	Stack<int> stack;

	cout << "\nTiming filling stack with 100,000 numbers - dynamically" << endl;

	clock_t start = clock();
	for (int i = 0; i < 100'000; i++)
	{
		random_number = rand() % 100;
		stack.addOne(); 
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

void time_fillANDempty_stack()
{
	int random_number = 0;			//integer used to fill array
	Stack<int> stack(100'000); 
	
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
