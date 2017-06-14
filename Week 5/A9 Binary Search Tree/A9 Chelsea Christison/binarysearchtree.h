/*************************************************************
* Author:		Chelsea Christison
* Filename:		binarysearchtree.h
* Date Created:	5.07.2017
*
* Modifications:
* *****
* Class: BinarySearchTree
* Canonicals: 
*	BinarySearchTree()
*	~BinarySearchTree()
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
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "exception.h"
#include "LQueue.h"

template <typename T>
struct tree_node
{
	T data;
	tree_node * left;
	tree_node * right;
};

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree(); 
	~BinarySearchTree(); 
	void Insert(T data); 
	void Delete(T data);

	void TraverseInOrder(void(*_output)(T&));
	void TraversePreOrder(void(*_output)(T&));
	void TraversePostOrder(void(*_output)(T&));
	void TraverseBreadthOrder(void(*_output)(T&));

	int Height(); 
private:
	tree_node<T> * root; 
	void Insert(T data, tree_node<T> *& root);
	void FindNodeToDelete(T data, tree_node<T> *& root); 
	void Delete(tree_node<T> *& parent); 
	void Purge(tree_node<T>*& root);
	int Height(tree_node<T>* parent); 

	void TraverseInOrder(tree_node<T> * parent, void(*visit)(T&));
	void TraversePreOrder(tree_node<T> * parent, void(*visit)(T&));
	void TraversePostOrder(tree_node<T> * parent, void(*visit)(T&));
	void TraverseBreadthOrder(tree_node<T> * parent, void(*_output)(T&));
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(): root(nullptr)
{}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	Purge(root); 
}

template <typename T>
void BinarySearchTree<T>::Insert(T data)
{ 
	Insert(data, root); 
}

template <typename T>
void BinarySearchTree<T>::Delete(T data)
{
	FindNodeToDelete(data, root);
}

template <typename T>
void BinarySearchTree<T>::TraverseInOrder(void(*_output)(T&))
{
	if (!root)
		throw Exception("Empty tree"); 

	TraverseInOrder(root, _output); 
}

template <typename T>
void BinarySearchTree<T>::TraversePreOrder(void(* _output)(T&))
{
	if (!root)
		throw Exception("Empty tree");

	TraversePreOrder(root, _output); 
}

template <typename T>
void BinarySearchTree<T>::TraversePostOrder(void(* _output)(T&))
{
	if (!root)
		throw Exception("Empty tree");

	TraversePostOrder(root, _output); 
}

template <typename T>
void BinarySearchTree<T>::TraverseBreadthOrder(void(* _output)(T&))
{
	if (!root)
		throw Exception("Empty tree");

	TraverseBreadthOrder(root, _output); 
}

template <typename T>
int BinarySearchTree<T>::Height()
{
	return Height(root); 
}

template <typename T>
void BinarySearchTree<T>::Insert(T data, tree_node<T> *& root)
{
	if(root == nullptr)
	{
		tree_node<T> * nn = new tree_node<T>; 
		nn->data = data; 
		nn->left = nn->right = nullptr; 
		root = nn; 
	}
	else
	{
		if (data < root->data)
			Insert(data, root->left); 
		else
			Insert(data, root->right);
	}
}

template <typename T>
void BinarySearchTree<T>::FindNodeToDelete(T data, tree_node<T> *& root)
{
	bool found = false;

	if (root == nullptr)
		throw Exception("Empty Tree"); 

	if (data < root->data)
	{
		FindNodeToDelete(data, root->left);
	}
	else if (data > root->data)
	{
		FindNodeToDelete(data, root->right);
	}
	else  //equal 
	{
		Delete(root);
	}
}

template <typename T>
void BinarySearchTree<T>::Delete(tree_node<T> *& parent)
{
	tree_node<T> * current = parent;
	tree_node<T> * previous = nullptr; 

	//leaf node		
	if (!current->left && !current->right)
		parent = nullptr;

	//empty left subtree
	else if (!current->left && current->right)
		parent = current->right;

	//empty right subtree 
	else if (current->left && !current->right)
		parent = current->left; 

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
	}

	delete current; 
	current = nullptr; 
}

template <typename T>
void BinarySearchTree<T>::Purge(tree_node<T> *& root)
{
	/*if (!root)
		throw Exception("Empty tree");*/
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

template <typename T>
int BinarySearchTree<T>::Height(tree_node<T>* parent)
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

template <typename T>
void BinarySearchTree<T>::TraverseInOrder(tree_node<T>* parent, void(*visit)(T&))
{
	if(parent)
	{
		TraverseInOrder(parent->left, visit); 
		visit(parent->data); 
		TraverseInOrder(parent->right, visit); 
	}
}

template <typename T>
void BinarySearchTree<T>::TraversePreOrder(tree_node<T>* parent, void(* visit)(T&))
{
	if(parent)
	{
		visit(parent->data); 
		TraversePreOrder(parent->left, visit); 
		TraversePreOrder(parent->right, visit); 
	}
}

template <typename T>
void BinarySearchTree<T>::TraversePostOrder(tree_node<T>* parent, void(* visit)(T&))
{
	if(parent)
	{
		TraversePostOrder(parent->left, visit); 
		TraversePostOrder(parent->right, visit);
		visit(parent->data); 
	}
}

template <typename T>
void BinarySearchTree<T>::TraverseBreadthOrder(tree_node<T>* parent, void(* _output)(T&))
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
