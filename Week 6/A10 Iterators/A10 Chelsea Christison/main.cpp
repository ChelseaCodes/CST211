/*************************************************************
* Author:			Chelsea Christison
* Date Created:		5.14.2017
*
* Lab/Assignment: Assignment 10 - Iterators 
*
* Overview:
*	This program tests the following Iterator types:
*		- LinkedList Forward Iterator
*		- LinkedList Backwards Iterator
*		- AVLTree In Order Iterator
*		- AVLTree Pre Order Iterator
*		- AVLTree Post Order Iterator
*		- AVLTree Breadth First Iterator
*
* Input:
*	The input consists of predefined integer arrays for
*	testing each of the iterators.
*
* Output:
*	The output of this program is simply the test results, 
*	Pass or Fail 
*
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "forwarditerator.h"
#include "backwardsiterator.h"
#include "inorderiterator.h"
#include "preorderiterator.h"
#include "postorderiterator.h"
#include "breadthfirstiterator.h"

typedef bool(*tests)(); 

const int num_test_ints = 11; 
const int test_ints[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
const int AVL_nums[] = { 8, 9, 10, 2, 1, 5, 3, 6, 4, 7, 11 };
const int inorder_ans[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
const int preorder_ans[] = { 5, 3, 2, 1, 4, 8, 6, 7, 10, 9, 11 };
const int postorder_ans[] = { 1, 2, 4, 3, 7, 6, 9, 11, 10, 8, 5};
const int breadth_ans[] = { 5, 3, 8, 2, 4, 6, 10, 1, 7, 9, 11 };

//Tests for linked list
bool forward_iterator_test();
bool backward_iterator_test(); 

//Tests for AVL Tree
bool inorder_iterator_test(); 
bool preorder_iterator_test(); 
bool postorder_iterator_test(); 
bool breadthfirst_iterator_test(); 


tests t[] = { forward_iterator_test, backward_iterator_test, inorder_iterator_test, preorder_iterator_test, postorder_iterator_test, breadthfirst_iterator_test }; 

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	for(tests test : t)
	{
		if (test())
		{
			cout << " PASSED! " << endl;
		}
		else
			cout << " FAILED*******" << endl; 
	}

	return 0;
}
bool forward_iterator_test()
{
	bool pass = true; 
	LList<int> * list = new LList<int>();

	for (int i : test_ints)
		list->Append(i);

	ForwardIterator<int> forward(list);
	int i = 0; 

	cout << "Using Forward Iterator: ";
	for (forward.Reset(); !forward.IsDone(); forward.MoveNext())
	{
		cout << *forward.GetCurrent() << ' ';
		if (*forward.GetCurrent() != test_ints[i++])
			pass = false; 
	}
	delete list; 
	return pass; 
}

bool backward_iterator_test()
{
	bool pass = true; 
	LList<int> * list = new LList<int>();

	for (int i : test_ints)
		list->Append(i);

	BackwardsIterator<int> back(list);
	int i = num_test_ints - 1; 

	cout << endl << "Using Backwards Iterator: ";
	for (back.Reset(); !back.IsDone(); back.MoveNext())
	{
		cout << *back.GetCurrent() << ' ';
		if (*back.GetCurrent() != test_ints[i--])
			pass = false; 
	}
	delete list;
	return pass; 
}

bool inorder_iterator_test()
{
	bool pass = true; 
	AVLTree<int> * tree = new AVLTree<int>(); 

	for (int i : AVL_nums)
		tree->Insert(i); 

	InOrderIterator<int> inorder(tree); 
	int i = 0; 

	cout << endl << "Using InOrder Iterator AVLTREE: ";
	for(inorder.Reset(); !inorder.IsDone(); inorder.MoveNext())
	{
		cout << *inorder.GetCurrent() << ' '; 
		if (*inorder.GetCurrent() != inorder_ans[i++])
			pass = false; 
	}
	delete tree; 
	return pass; 
}

bool preorder_iterator_test()
{
	bool pass = true;
	AVLTree<int> * tree = new AVLTree<int>();

	for (int i : AVL_nums)
		tree->Insert(i);

	PreOrderIterator<int> preorder(tree);
	int i = 0;

	cout << endl << "Using PreOrder Iterator AVLTREE: ";
	for (preorder.Reset(); !preorder.IsDone(); preorder.MoveNext())
	{
		cout << *preorder.GetCurrent() << ' ';
		if (*preorder.GetCurrent() != preorder_ans[i++])
			pass = false;
	}
	delete tree;
	return pass;
}

bool postorder_iterator_test()
{
	bool pass = true;
	AVLTree<int> * tree = new AVLTree<int>();

	for (int i : AVL_nums)
		tree->Insert(i);

	PostOrderIterator<int> postorder(tree);
	int i = 0;

	cout << endl << "Using PostOrder Iterator AVLTREE: ";
	for (postorder.Reset(); !postorder.IsDone(); postorder.MoveNext())
	{
		cout << *postorder.GetCurrent() << ' ';
		if (*postorder.GetCurrent() != postorder_ans[i++])
			pass = false;
	}
	delete tree;
	return pass;
}

bool breadthfirst_iterator_test()
{
	bool pass = true;
	AVLTree<int> * tree = new AVLTree<int>();

	for (int i : AVL_nums)
		tree->Insert(i);

	BreadthFirstIT<int> bread(tree);
	int i = 0;

	cout << endl << "Using Breadth First Iterator AVLTREE: ";
	for (bread.Reset(); !bread.IsDone(); bread.MoveNext())
	{
		cout << *bread.GetCurrent() << ' ';
		if (*bread.GetCurrent() != breadth_ans[i++])
			pass = false;
	}
	delete tree;
	return pass;
}
