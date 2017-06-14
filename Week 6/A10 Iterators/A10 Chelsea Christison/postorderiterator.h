/************************************************************************
* Class: postorderiterator.h
*
* Purpose: This Iterator iterates through an AVL tree in Post Order
*
* Manager functions:
* 	PostOrderIterator()
*		default cursor is nullptr
*	PostOrderIterator(AVLTree<T> * tree)
*	~PostOrderIterator()
*
* Methods:
*	void Reset()
*		calls traversePostOrder and queues data in specific order
*	void MoveNext()
*		set cursor to what is next in the queue
*	bool IsDone()
*		true when cursor is nullptr
*	T * GetCurrent()
*		returns data in cursor
*
*************************************************************************/
#ifndef postorderiterator_h
#define postorderiterator_h
//#include "treeiterator.h"

template <typename T>
class PostOrderIterator : public TreeIterator<T>
{
public:
	PostOrderIterator(); 
	PostOrderIterator(AVLTree<T> * tree); 
	~PostOrderIterator(); 
	void Reset(); 
	void MoveNext(); 
	bool IsDone();
	T * GetCurrent(); 
private:
	void traversePostOrder(tree_node<T> * parent); 
};

template <typename T>
PostOrderIterator<T>::PostOrderIterator() : TreeIterator()
{}

template <typename T>
PostOrderIterator<T>::PostOrderIterator(AVLTree<T>* tree) : TreeIterator(tree)
{}

template <typename T>
PostOrderIterator<T>::~PostOrderIterator()
{}

template <typename T>
void PostOrderIterator<T>::Reset()
{
	AVLTree<T> * tree = TreeIterator<T>::m_tree; 
	traversePostOrder(tree->getRoot()); 

	TreeIterator<T>::MoveNext(); 
}

template <typename T>
void PostOrderIterator<T>::MoveNext()
{
	if (IsDone())
	{
		cout << "Reached the end of Post Order Iteration, Resetting" << endl;
		Reset();
	}
	TreeIterator<T>::MoveNext();
}

template <typename T>
bool PostOrderIterator<T>::IsDone()
{
	return TreeIterator<T>::IsDone(); 
}

template <typename T>
T* PostOrderIterator<T>::GetCurrent()
{
	if (IsDone())
	{
		cout << "Reached the end of Post Order Iteration, Resetting" << endl;
		Reset();
	}
	return TreeIterator<T>::GetCurrent();
}

template <typename T>
void PostOrderIterator<T>::traversePostOrder(tree_node<T>* parent)
{
	if (parent)
	{
		traversePostOrder(parent->left);
		traversePostOrder(parent->right);
		LQueue<tree_node<T> *> * queue = TreeIterator<T>::m_ordered_output;
		queue->Enqueue(parent);
	}
}
#endif
