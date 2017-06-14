/************************************************************************
* Class: inorderiterator.h
*
* Purpose: This Iterator iterates through an AVL tree in order
*
* Manager functions:
* 	InOrderIterator()
*		default cursor is nullptr
*	InOrderIterator(AVLTree<T> * tree)
*	~InOrderIterator()
*
* Methods:
*	void Reset()
*		calls traverseInOrder and queues data in specific order
*	void MoveNext()
*		set cursor to what is next in the queue
*	bool IsDone()
*		true when cursor is nullptr
*	T * GetCurrent()
*		returns data in cursor
*
*************************************************************************/
#ifndef inorderiterator_H
#define inorderiterator_H
#include "treeiterator.h"

template <typename T>
class InOrderIterator : public TreeIterator<T>
{
public: 
	InOrderIterator(); 
	InOrderIterator(AVLTree<T> * tree); 
	~InOrderIterator();

	void Reset();		//initialize cursor to beginning of queue
	void MoveNext();	//traverse to next pointer in queue
	bool IsDone();		//true when past last element
	T * GetCurrent();	//gets data in current node 
private:
	void traverseInOrder(tree_node<T> * parent); 
};

template <typename T>
InOrderIterator<T>::InOrderIterator() : TreeIterator()
{}

template <typename T>
InOrderIterator<T>::InOrderIterator(AVLTree<T>* tree) : TreeIterator(tree)
{}

template <typename T>
InOrderIterator<T>::~InOrderIterator()
{}

template <typename T>
void InOrderIterator<T>::Reset()
{
	AVLTree<T> * tree = TreeIterator<T>::m_tree;
	traverseInOrder(tree->getRoot()); 

	TreeIterator<T>::MoveNext();
}

template <typename T>
void InOrderIterator<T>::MoveNext()
{
	if(IsDone())
	{
		cout << "Reached the end of In Order Iteration, Resetting" << endl; 
		Reset(); 
	}

	TreeIterator<T>::MoveNext(); 
}

template <typename T>
bool InOrderIterator<T>::IsDone()
{
	return TreeIterator<T>::IsDone(); 
}

template <typename T>
T* InOrderIterator<T>::GetCurrent()
{
	if(IsDone())
	{
		cout << "Reached the end of In Order Iteration, Resetting" << endl;
		Reset();
	}

	return TreeIterator<T>::GetCurrent(); 
}

template <typename T>
void InOrderIterator<T>::traverseInOrder(tree_node<T>* parent)
{
	if(parent)
	{
		traverseInOrder(parent->left); 
		LQueue<tree_node<T> *> * queue = TreeIterator<T>::m_ordered_output;
		queue->Enqueue(parent); 
		traverseInOrder(parent->right); 
	}
}

#endif
