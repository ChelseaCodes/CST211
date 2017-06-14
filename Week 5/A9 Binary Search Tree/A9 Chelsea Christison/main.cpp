#include"binarysearchtree.h"

typedef void(*functionPointer)(int&); 
typedef bool(*tests)(); 

void output(int & data);
bool test_insert_single_node_empty_tree(); 
bool test_height_is_3();
bool output_inorder();
bool output_postorder();
bool output_preorder();
bool output_breadthfirst();
bool test_delete_node();
bool test_exception_empty_tree(); 

int test_nums[] = { 20,15,25,12,18,11,30 };
functionPointer out = output; 

tests t[] = { test_insert_single_node_empty_tree, test_height_is_3, output_inorder, output_breadthfirst, output_postorder,
				output_preorder, test_delete_node, test_exception_empty_tree};

int main()
{
	for (tests test : t)
	{
		if(test())
			cout << " Passed." << endl;
		else
			cout << " FAILED!!! " << endl; 
	}

	return 0; 
}

bool test_insert_single_node_empty_tree()
{
	bool pass = true; 
	BinarySearchTree<int> bin_tree;
	for (int test_num : test_nums)
	{
		bin_tree.Insert(test_num); 
	}

	cout << "Insert nodes into tree test ";
	return pass; 
}

bool test_height_is_3()
{
	bool pass = false;
	BinarySearchTree<int> bin_tree;

	for (int test_num : test_nums)
	{
		bin_tree.Insert(test_num);
	}

	if (bin_tree.Height() == 3)
		pass = true; 

	cout << "test height of three test "; 

	return pass; 
}

bool output_inorder()
{
	bool pass = false;
	BinarySearchTree<int> bin_tree;

	for (int test_num : test_nums)
	{
		bin_tree.Insert(test_num);
	}

	cout << "In Order:\n";
	bin_tree.TraverseInOrder(out); 
	cout << " "; 

	return true; 
}

bool output_postorder()
{
	bool pass = false;
	BinarySearchTree<int> bin_tree;

	for (int test_num : test_nums)
	{
		bin_tree.Insert(test_num);
	}

	cout << "Post Order:\n";
	bin_tree.TraversePostOrder(out);
	cout << " ";

	return true;
}

bool output_preorder()
{
	bool pass = false;
	BinarySearchTree<int> bin_tree;

	for (int test_num : test_nums)
	{
		bin_tree.Insert(test_num);
	}

	cout << "Pre Order:\n";
	bin_tree.TraversePreOrder(out);
	cout << " ";

	return true;
}

bool output_breadthfirst()
{
	bool pass = false;
	BinarySearchTree<int> bin_tree;

	for (int test_num : test_nums)
	{
		bin_tree.Insert(test_num);
	}

	cout << "Breadth first:\n";
	bin_tree.TraverseBreadthOrder(out);
	cout << " ";

	return true;
}

bool test_delete_node()
{
	bool pass = false;
	BinarySearchTree<int> bin_tree;
	for (int test_num : test_nums)
	{
		bin_tree.Insert(test_num);
	}

	//delete node 12; 
	bin_tree.Delete(12); 

	//then try to delete again, should throw error
	try
	{
		bin_tree.Delete(12); 
	}
	catch (Exception exception)
	{
		pass = true; 
	}

	cout << "Delete node from tree test "; 

	return pass;
}

bool test_exception_empty_tree()
{
	bool pass = false;
	BinarySearchTree<int> bin_tree;

	try
	{
		bin_tree.TraverseInOrder(out); 
	}
	catch(Exception ex)
	{
		pass = true; 
	}

	cout << "Exception test on empty tree "; 

	return pass;
}

//used for the visit problem. 
void output(int & data)
{
	std::cout << data << " "; 
}