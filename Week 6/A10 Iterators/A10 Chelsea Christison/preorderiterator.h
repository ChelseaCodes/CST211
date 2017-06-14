/************************************************************************
* Class: preorderiterator.h
*
* Purpose: This Iterator iterates through an AVL tree in Pre Order
*
* Manager functions:
* 	PreOrderIterator()
*		default cursor is nullptr
*	PreOrderIterator(AVLTree<T> * tree)
*	~PreOrderIterator()
*
* Methods:
*	void Reset()
*		calls traversePreOrder and queues data in specific order
*	void MoveNext()
*		set cursor to what is next in the queue
*	bool IsDone()
*		true when cursor is nullptr
*	T * GetCurrent()
*		returns data in cursor
*
*************************************************************************/
#ifndef preorderiterator_h
#define preorderiterator_h

template <typename T>
class PreOrderIterator : public TreeIterator<T>
{
public:
	PreOrderIterator();
	PreOrderIterator(AVLTree<T> * tree);
	~PreOrderIterator();

	void Reset();		//initialize cursor to the root of tree
	void MoveNext();	//traverse to next element
	bool IsDone();		//true when past last element
	T * GetCurrent();	//gets data in current node 
private:
	void traversePreOrder(tree_node<T> * parent);
};

template <typename T>
PreOrderIterator<T>::PreOrderIterator() : TreeIterator()
{}

template <typename T>
PreOrderIterator<T>::PreOrderIterator(AVLTree<T>* tree) : TreeIterator(tree)
{}

template <typename T>
PreOrderIterator<T>::~PreOrderIterator()
{}

template <typename T>
void PreOrderIterator<T>::Reset()
{
	AVLTree<T> * tree = TreeIterator<T>::m_tree;
	traversePreOrder(tree->getRoot());

	TreeIterator<T>::MoveNext();
}

template <typename T>
void PreOrderIterator<T>::MoveNext()
{
	if (IsDone())
	{
		cout << "Reached the end of Pre Order Iteration, Resetting" << endl;
		Reset();
	}
	TreeIterator<T>::MoveNext();
}

template <typename T>
bool PreOrderIterator<T>::IsDone()
{
	return TreeIterator<T>::IsDone();
}

template <typename T>
T* PreOrderIterator<T>::GetCurrent()
{
	if (IsDone())
	{
		cout << "Reached the end of Pre Order Iteration, Resetting" << endl;
		Reset();
	}
	return TreeIterator<T>::GetCurrent();
}

template <typename T>
void PreOrderIterator<T>::traversePreOrder(tree_node<T>* parent)
{
	if (parent)
	{
		LQueue<tree_node<T> *> * queue = TreeIterator<T>::m_ordered_output;
		queue->Enqueue(parent);
		traversePreOrder(parent->left);
		traversePreOrder(parent->right);
	}
}
#endif