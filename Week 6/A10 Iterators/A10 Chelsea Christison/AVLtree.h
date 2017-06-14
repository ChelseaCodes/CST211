/*************************************************************
* Author:		Chelsea Christison
* Filename:		binarysearchtree.h
* Date Created:	5.07.2017
*
* Modifications:
* *****
* Class: AVLTree
* Canonicals: 
*	AVLTree()
*	~AVLTree()
* Methods:
*	Insert(T data)
*		User calls this function to insert a node into the tree
*	Delete(T data)
*		User call this function to delete a node from the tree
*	TraverseInOrder(void(*_output)(T&)
*		traverse tree in order
*	TraversePreOrder(void(*_output)(T&)
*		traverse tree in pre order
*	TraversePostOrder(void(*_output)(T&)
*		traverse tree in post order
*	TraverseBreadthOrder(void(*_output)(T&)
*		traverse tree in breadth first
*	int Height()
*		finds the height of the tree
*	Insert(T data, tree_node<T> *& root)
*		called from Insert()
*	FindNodeToDelete(T data, tree_node<T> *& root)
*		Finds the node to delete
*	Delete(tree_node<T> *& parent)
*		deletes the node 
*	Purge(tree_node<T>*& root)
*	Height(tree_node<T>* parent)
*	TraverseInOrder(tree_node<T> * parent, void(*visit)(T&))
*	TraversePreOrder(tree_node<T> * parent, void(*visit)(T&))
*	TraversePostOrder(tree_node<T> * parent, void(*visit)(T&))
*	TraverseBreadthOrder(tree_node<T> * parent, void(*_output)(T&))
*************************************************************************/
#ifndef AVLTREE_H
#define AVLTREE_H
#include "exception.h"
#include "LQueue.h"

// enum class to hold balance factors of nodes
enum class balance
{
	LH = 1,
	EH = 0,
	RH = -1
};

// struct for the nodes in tree
// holds data, left/right ptrs and balance factor
template <typename T>
struct tree_node
{
	T data;
	tree_node<T> * left;
	tree_node<T> * right;
	balance bf;
};

template <typename T>
class AVLTree
{
public:
	AVLTree(); 
	~AVLTree(); 
	AVLTree(const AVLTree<T> & copy);
	AVLTree<T> & operator=(const AVLTree<T> & rhs); 

	void Insert(T data);
	void Delete(T data);

	void TraverseInOrder(void(*_output)(T&));
	void TraversePreOrder(void(*_output)(T&));
	void TraversePostOrder(void(*_output)(T&));
	void TraverseBreadthOrder(void(*_output)(T&));

	int Height(); 
	tree_node<T> * getRoot(); 
private:
	tree_node<T> * root;

	void Insert(T data, tree_node<T> *& root, bool & taller);
	void LeftBalance(tree_node<T> *& root, bool & taller); 
	void _LL(tree_node<T> *& root); 
	void _RR(tree_node<T> *& root); 
	void RightBalance(tree_node<T> *& root, bool & taller);

	void FindNodeToDelete(T data, tree_node<T> *& root, bool& shorter, bool& success); 
	void Delete(tree_node<T> *& parent, bool& shorter, bool& success); 
	void delRightBalance(tree_node<T> *& root, bool & shorter);
	void delLefttBalance(tree_node<T> *& root, bool & shorter);
	void Purge(tree_node<T>*& root);
	int Height(tree_node<T>* parent); 

	void TraverseInOrder(tree_node<T> * parent, void(*visit)(T&));
	void TraversePreOrder(tree_node<T> * parent, void(*visit)(T&));
	void TraversePostOrder(tree_node<T> * parent, void(*visit)(T&));
	void TraverseBreadthOrder(tree_node<T> * parent, void(*_output)(T&));
};

template <typename T>
AVLTree<T>::AVLTree(): root(nullptr)
{}

template <typename T>
AVLTree<T>::~AVLTree()
{
	Purge(root); 
}

/**********************************************************************
* Purpose:
*	This function is the copy c'tor for AVLTree class. Makes a copy 
*	buy using a modified breadth first traversal
*
* Precondition:
*	copy - AVLTree to copy from
*
* Postcondition:
*	creates a new object by making a deep copy from copy 
************************************************************************/
template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& copy): root(nullptr)
{
	tree_node<T> * current = copy.root;

	LQueue<tree_node<T> * > queue;
	if (current)
	{
		queue.Enqueue(current);

		while (!queue.isEmpty())
		{
			current = queue.Dequeue();

			this->Insert(current->data); 
			
			if (current->left)
				queue.Enqueue(current->left);

			if (current->right)
				queue.Enqueue(current->right);
		}

	}
}

/**********************************************************************
* Purpose:
*	This is the operator equal for the AVLTree class. copies by using 
*	a modified breadth first traversal of the rhs. 
*
* Precondition:
*	rhs - AVLTree to copy from 
*
* Postcondition:
*	performs a deep copy and modifies this. 
************************************************************************/
template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& rhs)
{
	if (this != &rhs)
	{
		tree_node<T> * current = rhs.root;

		LQueue<tree_node<T> * > queue;

		this->Purge(this->root);

		if (current)
		{
			queue.Enqueue(current);

			while (!queue.isEmpty())
			{
				current = queue.Dequeue();

				this->Insert(current->data);

				if (current->left)
					queue.Enqueue(current->left);

				if (current->right)
					queue.Enqueue(current->right);
			}
		}
	}
	return *this; 
}

/**********************************************************************
* Purpose:
*	This function calls insert and passes the data to be inserted, 
*	as well as root, and a boolean indicating if the AVL tree grew in 
*	height. 
*
* Precondition:
*	data - of type T that is to be inserted into the AVL
*	
* Postcondition:
*	modifies the AVL tree by inserting the data. Insert calls another 
*	insert inaccessible to caller. 
************************************************************************/
template <typename T>
void AVLTree<T>::Insert(T data)
{ 
	bool taller = false; 
	Insert(data, root, taller); 
}

/**********************************************************************
* Purpose:
*	This function is the beginning to delete the data passed from the AVL
*	tree. 
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::Delete(T data)
{
	bool shorter = false;
	bool success = false; 
	FindNodeToDelete(data, root, shorter, success);
}

/**********************************************************************
* Purpose:
*	This function traverses the AVL tree in order, from left most node
*	to right. 
*
* Precondition:
*	_output - a function pointer to a function that handles display of
*				node.
* Postcondition:
*	outputs the AVL tree "in order"
************************************************************************/
template <typename T>
void AVLTree<T>::TraverseInOrder(void(*_output)(T&))
{
	if (!root)
		throw Exception("Empty tree"); 

	TraverseInOrder(root, _output); 
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::TraversePreOrder(void(* _output)(T&))
{
	if (!root)
		throw Exception("Empty tree");

	TraversePreOrder(root, _output); 
}

template <typename T>
void AVLTree<T>::TraversePostOrder(void(* _output)(T&))
{
	if (!root)
		throw Exception("Empty tree");

	TraversePostOrder(root, _output); 
}

template <typename T>
void AVLTree<T>::TraverseBreadthOrder(void(* _output)(T&))
{
	if (!root)
		throw Exception("Empty tree");

	TraverseBreadthOrder(root, _output); 
}

/**********************************************************************
* Purpose:
*	This function is called from user, and it returns the height of
*	the AVL tree
************************************************************************/
template <typename T>
int AVLTree<T>::Height()
{
	return Height(root); 
}

template <typename T>
tree_node<T>* AVLTree<T>::getRoot()
{
	return root; 
}

/**********************************************************************
* Purpose:
*	This function recursively inserts data into the AVL tree. Finds
*	where in the tree to insert data then creates the node to insert. 
*
* Precondition:
*	data - data of type T to be inserted into AVL
*	root - current root, passed by *& to make changed
*	taller - boolean to trigger rebalancing tree
* Postcondition:
*	Inserts data into AVL and rebalances nodes on the way back up 
*	the call stack. 
************************************************************************/
template <typename T>
void AVLTree<T>::Insert(T data, tree_node<T> *& root, bool & taller)
{
	/* if root is nullptr */
	if(!root)
	{
		//create a new node and set values 
		tree_node<T> * nn = new tree_node<T>; 
		nn->data = data; 
		nn->left = nn->right = nullptr; 
		nn->bf = balance::EH; 
		taller = true; 
		root = nn; //set root to new node 
	}
	/* if data goes on the left side of AVL */
	else if (data < root->data)		
	{
		Insert(data, root->left, taller);

		if(taller)
		{
			//switch on roots balance factor
			switch (root->bf)
			{
				case balance::LH:
					LeftBalance(root, taller);	//out of balance
					break;
				case balance::EH:
					root->bf = balance::LH; 
					break;
				case balance::RH:
					root->bf = balance::EH; 
					taller = false;		//tree did not grow 
					break;
				default:;
			}
		}
		
	}
	/* else data goes into the right side of AVL */
	else
	{
		Insert(data, root->right, taller);

		if(taller)
		{
			//switch on the root's balancing factor
			switch (root->bf)
			{
				case balance::LH:
					root->bf = balance::EH; 
					taller = false;			//equal heavy, tree is not taller. 
					break;
				case balance::EH:
					root->bf = balance::RH; 
					break;
				case balance::RH:
					RightBalance(root, taller); 
					break;
				default:;
			}
		}
	}
}

/**********************************************************************
* Purpose:
*	This function handles rebalancing on a left heavy AVL tree at the 
*	root given. Either performs a LL rotation or a LR rotation. 
*
* Precondition:
*	root - the root of the problem which has its left child
*	taller - boolean if tree is taller
*	
* Postcondition:
*	rebalances the AVL tree with an LL or LR rotation. 
************************************************************************/
template <typename T>
void AVLTree<T>::LeftBalance(tree_node<T> *& root, bool& taller)
{
	// root of the problem's left child
	tree_node<T> * left_child = root->left;	

	/* switch on the balance factor of left child  */
	switch (left_child->bf)
	{
		/* Node placed in Left Child's LEFT Subtree (LL) */
		case balance::LH:
			left_child->bf = root->bf = balance::EH;
			_LL(root); 
			taller = false; 
			break;

		/* Node placed in Left Child's RIGHT Subtree (LR) */
		case balance::RH:
		{
			//now to look at the left child's right child. 
			tree_node<T> * right_child = left_child->right;

			/* switch on balance factor of right child to determine 
			 * the balance factor of root and left child after LR rotation */
			switch (right_child->bf)
			{	
				case balance::LH:
					root->bf = balance::RH;	
					left_child->bf = balance::EH;
					break;
				case balance::EH:
					root->bf = left_child->bf = balance::EH;
					break;
				case balance::RH:
					root->bf = balance::EH;
					left_child->bf = balance::LH;
					break;
				default:;
			}

			right_child->bf = balance::EH;

			//RR on the root of the problem's left subtree
			_RR(root->left);

			//LL on the left subtree. 
			_LL(root);
			taller = false;
			break;	//end RH case
		}
		default:
			throw Exception("Error");
	}
}

/**********************************************************************
* Purpose:
*	This function performs a left rotation on the root passed
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::_LL(tree_node<T>*& root)
{
	tree_node<T> * old_root = root;
	tree_node<T> * old_child = root->left;
	tree_node<T> * t2 = old_child->right;

	root = old_child; 
	old_child->right = old_root; 
	old_root->left = t2; 
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::_RR(tree_node<T>*& root)
{
	tree_node<T> * old_root = root;
	tree_node<T> * old_child = root->right;
	tree_node<T> * t2 = old_child->left;

	root = old_child;
	old_child->left = old_root;
	old_root->right= t2;
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::RightBalance(tree_node<T>*& root, bool& taller)
{
	tree_node<T> * right_child = root->right;		//focus on right subtree
	switch (right_child->bf)
	{
		/* Right Child's Left Subtree */
		case balance::LH:
		{
			tree_node<T> * left_child = right_child->left;

			switch (left_child->bf)
			{
			case balance::LH:
				root->bf = balance::EH;
				right_child->bf = balance::RH;
				break;
			case balance::EH:
				root->bf = right_child->bf = balance::EH;
				break;
			case balance::RH:
				root->bf = balance::LH;
				right_child->bf = balance::EH;
				break;
			default:;
			}

			left_child->bf = balance::EH;

			//RR on the root of the problem's left subtree
			_LL(root->right);

			//LL on the left subtree. 
			_RR(root);
			taller = false;
			break;	//end LH case
		}

		/*  Right Child's Right Subtree */
		case balance::RH:
			root->bf = right_child->bf = balance::EH;
			_RR(root); 
			taller = false; 
			break; 
		
		default:
			throw Exception("Error");
	}
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::FindNodeToDelete(T data, tree_node<T> *& root, bool& shorter, bool& success)
{
	if (!root)
		throw Exception("Empty Tree");

	//looking down left subtree
	if (data < root->data)
	{
		FindNodeToDelete(data, root->left,shorter, success);
		// if deleted out of the left
		if(shorter)
		{
			//then right balance based on delete 
			delRightBalance(root, shorter); 
		}
	}
	//looking down right subtree
	else if (data > root->data)
	{
		FindNodeToDelete(data, root->right, shorter, success);
		//deleted out of right 
		if(shorter)
		{
			delLefttBalance(root, shorter); 
		}
	}
	else  //equal 
	{
		Delete(root, shorter, success);
	}
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::Delete(tree_node<T> *& parent, bool& shorter, bool& success)
{
	tree_node<T> * current = parent;
	tree_node<T> * previous = nullptr; 

	//leaf node		
	if (!current->left && !current->right)
	{
		parent = nullptr;
		shorter = success = true; 
	}
	//empty left subtree
	else if (!current->left && current->right)
	{
		parent = current->right;
		success = shorter = true; 
	}
	//empty right subtree 
	else if (current->left && !current->right)
	{
		parent = current->left;
		success = shorter = true; 
	}
	//two children 
	else
	{
		current = parent->left; 
		while (current->right)
		{
			previous = current; 
			current = current->right; 
		}

		parent->data = current->data; 

		if (previous == nullptr)
			parent->left = current->left;
		else
			previous->right = current->left;

		success = shorter = true; 

		if (shorter)
			delRightBalance(root, shorter);

	}

	delete current; 
	current = nullptr; 
}

/**********************************************************************
* Purpose:
*	This function balances the right side of root after a delete
*
* Precondition:
*	root - 
*	shorter - 
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::delRightBalance(tree_node<T> *& root, bool & shorter)
{
	tree_node<T> * right_child = root->right;

	switch (root->bf)
	{
		/* deleted from left, */
		case balance::EH:
			root->bf = balance::RH;
			shorter = false;
			break;
		case balance::LH:
			root->bf = balance::EH;
			break;
		case balance::RH:
		{
			if(right_child->bf == balance::LH)
			{
				tree_node<T> * left_child = right_child->left; 
				switch (left_child->bf)
				{
				case balance::LH:
					root->bf = balance::EH;
					right_child->bf = balance::RH;
					break;
				case balance::EH:
					root->bf = right_child->bf = balance::EH;
					break;
				case balance::RH:
					right_child->bf = balance::EH;
					root->bf = balance::LH;
					break;
				}
				left_child->bf = balance::EH;

				_LL(root->right); 
				_RR(root); 
			}
			else
			{
				switch (right_child->bf)
				{
					case balance::LH:
					case balance::RH: 
						root->bf = right_child->bf = balance::EH;
						break;
					case balance::EH:
						root->bf = balance::RH;
						right_child->bf = balance::LH;
						shorter = false;
						break;
				}
				_RR(root);
			}
		}
	}
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::delLefttBalance(tree_node<T>*& root, bool& shorter)
{
	tree_node<T> * left_child = root->left;
	switch (root->bf)
	{
	case balance::EH:
		root->bf = balance::LH;
		break;

	case balance::RH:
		root->bf = balance::EH;
		shorter = false; 
		break;
	case balance::LH:
	{
		if (left_child->bf == balance::RH)
		{
			tree_node<T> * right_child = left_child->right;
			switch (right_child->bf)
			{
			case balance::LH:
				root->bf = balance::RH;
				left_child->bf = balance::EH;
				break;
			case balance::EH:
				root->bf = left_child->bf = balance::EH;
				break;
			case balance::RH:
				left_child->bf = balance::EH;
				root->bf = balance::RH;
				break;
			}

			right_child->bf = balance::EH;

			_RR(root->left);
			_LL(root);
		}
		else
		{
			switch (left_child->bf)
			{
			case balance::RH:
			case balance::LH:
				root->bf = left_child->bf = balance::EH;
				break;
			case balance::EH:
				root->bf = balance::LH;
				left_child->bf = balance::RH;
				shorter = false;
				break;
			}
			_LL(root);
		}
	}
	}
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::Purge(tree_node<T> *& root)
{
	if (!root)
		return; //throw Exception("Empty tree");
	while (root)
	{
		//purge left side
		if (root->left)
			Purge(root->left);

		//purge right side
		if (root->right)
			Purge(root->right);

		delete root;
		root = nullptr;

	}
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
int AVLTree<T>::Height(tree_node<T>* parent)
{
	int left; 
	int right;
	
	//no node 0
	if (!parent) return 0; 
	//leaf 
	if (!parent->left && !parent->right) return 0; 
	
	//get height of left subtree
	left = Height(parent->left); 

	//get height of right subtree
	right = Height(parent->right); 

	return left >= right ? left + 1 : right + 1; 
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::TraverseInOrder(tree_node<T>* parent, void(*visit)(T&))
{
	if(parent)
	{
		TraverseInOrder(parent->left, visit); 
		visit(parent->data); 
		TraverseInOrder(parent->right, visit); 
	}
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::TraversePreOrder(tree_node<T>* parent, void(* visit)(T&))
{
	if(parent)
	{
		visit(parent->data); 
		TraversePreOrder(parent->left, visit); 
		TraversePreOrder(parent->right, visit); 
	}
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::TraversePostOrder(tree_node<T>* parent, void(* visit)(T&))
{
	if(parent)
	{
		TraversePostOrder(parent->left, visit); 
		TraversePostOrder(parent->right, visit);
		visit(parent->data); 
	}
}

/**********************************************************************
* Purpose:
*	This function
*
* Precondition:
* Postcondition:
************************************************************************/
template <typename T>
void AVLTree<T>::TraverseBreadthOrder(tree_node<T>* parent, void(* _output)(T&))
{
	tree_node<T> * current = nullptr; 

	LQueue<tree_node<T> * > queue; 
	if(parent)
	{
		queue.Enqueue(parent); 

		while (!queue.isEmpty())
		{
			current = queue.Dequeue();
			_output(current->data);

			if (current->left)
				queue.Enqueue(current->left); 
			
			if (current->right)
				queue.Enqueue(current->right); 
		}
		
	}

}
#endif
