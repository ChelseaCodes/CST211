/************************************************************************
* Class: treeiterator.h
*
* Purpose: This abstract base class derived from AbstractIterator
*	implements a base for iterating through an AVLTree
*
* Manager functions:
* 	TreeIterator()
*		default cursor is nullptr
*	TreeIterator(AVLTree<T> * tree)
*		sets cursor to beginning of data
*	virtual ~TreeIterator()
*
* Methods:
*	virtual void Reset() = 0
*		initialize cursor to first element in data
*	void MoveNext()
*		set cursor to what is next in the queue
*	bool IsDone()
*		true when cursor is nullptr
*	T * GetCurrent()
*		returns data in cursor
*
*************************************************************************/
#ifndef treeiterator_H
#define treeiteraotr_H
#include "abstractiterator.h"
#include  "AVLtree.h"

template<typename T>
class TreeIterator : public AbstractIterator<T>
{
public:
	TreeIterator(); 
	TreeIterator(AVLTree<T> * tree); 
	virtual ~TreeIterator(); 
	virtual void Reset() = 0;
	void MoveNext();
	bool IsDone();
	T * GetCurrent();
protected:
	tree_node<T> * m_cursor; 
	AVLTree<T> * m_tree; 
	LQueue<tree_node<T>*> * m_ordered_output;
};

template <typename T>
TreeIterator<T>::TreeIterator() : AbstractIterator(), m_cursor(nullptr), m_tree(nullptr)
{
	m_ordered_output = new LQueue<tree_node<T>*>(); 
}

template <typename T>
TreeIterator<T>::TreeIterator(AVLTree<T>* tree) : AbstractIterator(), m_cursor(tree->getRoot()), m_tree(tree)
{
	m_ordered_output = new LQueue<tree_node<T>*>(); 
}

template <typename T>
TreeIterator<T>::~TreeIterator()
{
	m_cursor = nullptr; 	
	m_tree = nullptr; 
	delete m_ordered_output; 
}

template <typename T>
void TreeIterator<T>::MoveNext()
{
	m_cursor = m_ordered_output->Dequeue(); 
}

template <typename T>
bool TreeIterator<T>::IsDone()
{
	return m_cursor == nullptr; 
}

template <typename T>
T* TreeIterator<T>::GetCurrent()
{
	return &m_cursor->data; 
}

#endif
