/************************************************************************
* Class: breadthfirstiterator.h
*
* Purpose: This Iterator iterates through an AVL tree using Breadth First
*
* Manager functions:
* 	BreadthFirstIterator()
*		default cursor is nullptr
*	BreadthFirstOrderIterator(AVLTree<T> * tree)
*	~BreadthFirstOrderIterator()
*
* Methods:
*	void Reset()
*		calls breadthfirstTraverse and queues data in specific order
*	void MoveNext()
*		set cursor to what is next in the queue
*	bool IsDone()
*		true when cursor is nullptr
*	T * GetCurrent()
*		returns data in cursor
*
*************************************************************************/
#ifndef breadthfirstiterator_h
#define breadthfirstiterator_h

template <typename T>
class BreadthFirstIT : public TreeIterator<T>
{
public:
	BreadthFirstIT(); 
	BreadthFirstIT(AVLTree<T> * tree); 
	~BreadthFirstIT(); 

	void Reset();		//initialize cursor to the root of tree
	void MoveNext();	//traverse to next element
	bool IsDone();		//true when past last element
	T * GetCurrent();	//gets data in current node 
private:
	void breadthfirstTraverse(tree_node<T> * parent); 
};

template <typename T>
BreadthFirstIT<T>::BreadthFirstIT() : TreeIterator()
{}

template <typename T>
BreadthFirstIT<T>::BreadthFirstIT(AVLTree<T>* tree) : TreeIterator(tree)
{}

template <typename T>
BreadthFirstIT<T>::~BreadthFirstIT()
{}

template <typename T>
void BreadthFirstIT<T>::Reset()
{
	AVLTree<T> * tree = TreeIterator<T>::m_tree;
	breadthfirstTraverse(tree->getRoot());

	TreeIterator<T>::MoveNext(); 
}

template <typename T>
void BreadthFirstIT<T>::MoveNext()
{
	if (IsDone())
	{
		cout << "Reached the end of Breadth First Iteration, Resetting" << endl;
		Reset();
	}
	TreeIterator<T>::MoveNext(); 
}

template <typename T>
bool BreadthFirstIT<T>::IsDone()
{
	return TreeIterator<T>::IsDone(); 
}

template <typename T>
T* BreadthFirstIT<T>::GetCurrent()
{
	if (IsDone())
	{
		cout << "Reached the end of Breadth First Iteration, Resetting" << endl;
		Reset();
	}
	return TreeIterator<T>::GetCurrent(); 
}

template <typename T>
void BreadthFirstIT<T>::breadthfirstTraverse(tree_node<T>* parent)
{
	tree_node<T> * current = nullptr;

	LQueue<tree_node<T> * > queue;
	if (parent)
	{
		queue.Enqueue(parent);

		while (!queue.isEmpty())
		{
			current = queue.Dequeue();
			LQueue<tree_node<T>*> * q = TreeIterator<T>::m_ordered_output; 
			q->Enqueue(current); 

			if (current->left)
				queue.Enqueue(current->left);

			if (current->right)
				queue.Enqueue(current->right);
		}
	}
}


#endif
