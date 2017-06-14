/*************************************************************
* Author:			Chelsea Christison
* Date Created:		5.09.2017
*
* Lab/Assignment: Lab 5 – AVL Tree 
*
* Overview:
*	This program tests my AVLTree class. It tests all insertions
*	with each rotation necessary. It also tests deletion 
*	of a node in all cases. 
*
* Input:
*	The input consists of predefined integer arrays for 
*	testing. And the entry from console if the array 
*	matches the answer array given. 
*
* Output:
*	The output of this program is simply the test results
*
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
using std::cout; 
using std::cin; 

#include"AVLtree.h"

typedef bool(*FunctionPointer)(); 
typedef void(*out)(int&); 

//arrays for rotations
const int num_result = 3;	//number of results in array 
const int test_nums[] = { 8, 9, 10, 2, 1, 5, 3, 6, 4, 7, 11 }; 
const int test_LL[] = { 50, 10, 9 };
const int test_RR[] = { 50, 60, 61 }; 
const int test_LR[] = { 50, 10, 20 }; 
const int test_RL[] = { 50, 60, 55 }; 

//answers after rotation is implemented
const int nums_result[] = { 5, 3, 8, 2, 4, 6, 10, 1, 7, 9, 11 };
const int LL_result[] = { 10, 9, 50 };
const int RR_result[] = { 60, 50, 61 };
const int LR_result[] = { 20, 10, 50 };
const int RL_result[] = { 55, 50, 60 };

// RightDelete (RD)  test values  ALWAYS DELETE 11
// syntax: RD _ head->bf _ leftchild->bf _ leftchild->rightchild->bf
const int RD_DELETE = 11;	//number delete in each instance 
const int RD_LH_LH[] = {10, 9, 11, 8};
const int RD_LH_EH[] = {10, 8, 11, 7, 9};
const int RD_LH_RH_RH[] = {10, 6, 11, 5, 12, 8, 9};
const int RD_LH_RH_LH[] = {10, 6, 11, 5, 8, 12, 7};
const int RD_LH_RH_EH[] = { 10, 8, 11, 9 };
const int RD_EH[] = { 10, 9, 11 };
const int RD_RH[] = { 10, 8, 11, 13 };

// RightDelete results after rotations
const int RESULT_LH_LH[] = { 9, 8, 10};
const int RESULT_LH_EH[] = { 8, 7, 10, 9 };
const int RESULT_LH_RH_RH[] = { 8, 6, 10, 5, 9, 12};
const int RESULT_LH_RH_LH[] = { 8, 6, 10, 5, 7, 12 };
const int RESULT_LH_RH_EH[] = { 9, 8, 10 };
const int RESULT_EH[] = { 10, 9};
const int RESULT_RH[] = { 10, 8, 13};

//LeftDelete(LD) 
const int LD_DELETE = 9;
const int LD_LH[] = { 10, 9, 11, 8 };
const int LD_EH[] = { 10, 9, 11 };
const int LD_RH_LH_LH[] = { 10, 9, 15, 8, 14, 16, 13 };
const int LD_RH_LH_RH[] = { 10, 9, 15, 8, 12, 16, 13 };
const int LD_RH_LH_EH[] = { 12, 9, 10, 15, 8, 11, 13, 16 };
const int LD_RH_EH[] = { 10, 9, 15, 12, 16 };
const int LD_RH_RH[] = { 10, 9, 15, 16 };

//LeftDelete results after rotations
const int RESULT_LD_LH[] = { 10, 8, 11 };
const int RESULT_LD_EH[] = { 10, 11 };
const int RESULT_LD_RH_LH_LH[] = { 14, 10, 15, 8, 13, 16 };
const int RESULT_LD_RH_LH_RH[] = { 12, 10, 15, 8, 13, 16 };
const int RESULT_LD_RH_LH_EH[] = { 12, 10, 15, 8 ,11, 13, 16 };
const int RESULT_LD_RH_EH[] = {15, 10, 16, 12};
const int RESULT_LD_RH_RH[] = { 15, 10, 16 };

const int HEIGHT = 3; 

void output(int & data); 
bool test_avl_LL(); 
bool test_avl_RR();
bool test_avl_LR();
bool test_avl_RL(); 
bool test_avl_large_nums(); 

bool test_right_delete_LH_LH();
bool test_right_delete_LH_EH();
bool test_right_delete_LH_RH_RH();
bool test_right_delele_LH_RH_LH();
bool test_right_delete_LH_RH_EH(); 
bool test_right_delete_RH();
bool test_right_delete_EH(); 

bool test_left_delete_LH();
bool test_left_delete_EH();
bool test_left_delete_RH_LH_LH();
bool test_left_delele_RH_LH_RH();
bool test_left_delete_RH_LH_EH();
bool test_left_delete_RH_EH();
bool test_left_delete_RH_RH();

bool test_height(); 
bool test_op_equal();
bool test_copy_ctor(); 

out o = output;
FunctionPointer tests[] = {test_avl_LL, test_avl_RR, test_avl_LR, test_avl_RL, test_avl_large_nums, test_right_delete_LH_LH, test_right_delete_LH_EH, test_right_delete_LH_RH_RH,test_right_delele_LH_RH_LH,test_right_delete_LH_RH_EH, test_right_delete_RH,test_right_delete_EH, test_left_delete_LH, test_left_delete_EH,
  test_left_delete_RH_LH_LH, test_left_delele_RH_LH_RH, test_left_delete_RH_LH_EH,
  test_left_delete_RH_EH, test_left_delete_RH_RH, test_height, test_op_equal, test_copy_ctor};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	for(FunctionPointer test : tests)
	{
		if (test())
		{
			cout << " PASSED\n" << endl;
		}
		else
			cout << " FAILED ********** \n" << endl; 
	}

	return 0; 
}

void output(int & data)
{
	cout << data << " ";
}

bool test_avl_LL()
{
	bool pass = false; 
	char verify = '\0';

	AVLTree<int> avl;
	for (int i : test_LL)
	{
		avl.Insert(i); 
	}

	cout << "Verify insert LL rotation:\nAVL: ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: "; 
	for (int i = 0; i < num_result; i++)
		cout << LL_result[i] << " "; 

	cout << endl;
	cout << "match? (y/n) "; 
	cin >> verify; 

	verify = toupper(verify); 

	verify == 'Y' ? pass = true : pass = false; 

	cout << "LL rotation test ";

	return pass; 
}

bool test_avl_RR()
{
	bool pass = false;
	char verify = '\0';

	AVLTree<int> avl;
	for (int i : test_RR)
	{
		avl.Insert(i);
	}

	cout << "Verify insert RR rotation:\nAVL: ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int i = 0; i < num_result; i++)
		cout << RR_result[i] << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "RR rotation test ";

	return pass;
}

bool test_avl_LR()
{
	bool pass = false;
	char verify = '\0';

	AVLTree<int> avl;
	for (int i : test_LR)
	{
		avl.Insert(i);
	}

	cout << "Verify insert LR rotation:\nAVL: ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int i = 0; i < num_result; i++)
		cout << LR_result[i] << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "LR rotation test ";

	return pass;
}

bool test_avl_RL()
{
	bool pass = false;
	char verify = '\0';

	AVLTree<int> avl;
	for (int i : test_RL)
	{
		avl.Insert(i);
	}

	cout << "Verify insert RL rotation:\nAVL: ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int i = 0; i < num_result; i++)
		cout << RL_result[i] << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "RL rotation test ";

	return pass;
}

bool test_avl_large_nums()
{
	bool pass = false;
	char verify = '\0';

	AVLTree<int> avl;
	for (int i : test_nums)
	{
		avl.Insert(i);
	}

	cout << "Verify insertion of many nodes tree:\nAVL: ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int i = 0; i < 11; i++)
		cout << nums_result[i] << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "insert many nodes rotation test ";

	return pass;
}

bool test_right_delete_LH_LH()
{
	bool pass = false; 
	char verify = '\0';
	AVLTree<int> avl; 

	cout << "Delete from right side on LH head, LH left child:\n";
	cout << "Insertion nums: "; 
	for(int i: RD_LH_LH)
	{
		avl.Insert(i); 
		cout << i << " ";
	}

	avl.Delete(RD_DELETE); 

	cout << "\nVerify equality:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LH_LH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "leftBalance LH head, LH left child test ";

	return pass;
}

bool test_right_delete_LH_EH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from right side on LH head, EH left child:\n";
	cout << "Insertion nums: ";

	for (int i : RD_LH_EH)
	{
		avl.Insert(i);
		cout << i << ' ';
	}

	avl.Delete(RD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LH_EH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "leftBalance LH head, EH left child test ";

	return pass;
}

bool test_right_delete_LH_RH_RH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from right side DBL rotation on LH head, RH left child, RH lefts right:\n";
	cout << "Insertion nums: ";
	for (int i : RD_LH_RH_RH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(RD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LH_RH_RH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "leftBalance RH head, RH left child, RH left child's right child test ";

	return pass;
}

bool test_right_delele_LH_RH_LH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from right side DBL rotation on LH head, RH left child, LH lefts right:\n";
	cout << "Insertion nums: ";
	for (int i : RD_LH_RH_LH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(RD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LH_RH_LH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "leftBalance LH head, RH left child, LH left childs right child test ";

	return pass;
}

bool test_right_delete_LH_RH_EH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from right side DBL rotation on LH head, RH left child, EH lefts right:\n";
	cout << "Insertion nums: ";
	for (int i : RD_LH_RH_EH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(RD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LH_RH_EH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "leftBalance LH head, RH left child, EH left childs right child test ";

	return pass;
}

bool test_right_delete_RH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from right side on RH head:\n";
	cout << "Insertion nums: ";
	for (int i : RD_RH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(RD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_RH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "leftBalance RH head test ";

	return pass;
}

bool test_right_delete_EH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from right side on EH head\n";
	cout << "Insertion nums: ";
	for (int i : RD_EH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(RD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_EH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "leftBalance EH head test ";

	return pass;
}

bool test_left_delete_LH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from left side on LH head\n";
	cout << "Insertion nums: ";
	for (int i : LD_LH)
	{
		avl.Insert(i);
		cout << i << ' '; 
	}

	avl.Delete(LD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LD_LH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "rightBalance LH head test ";

	return pass;
}

bool test_left_delete_EH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from left side on EH head\n";
	cout << "Insertion nums: ";
	for (int i : LD_EH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(LD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LD_EH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "rightBalance EH head test ";

	return pass;
}

bool test_left_delete_RH_LH_LH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from left side DBL rotation on RH head, LH right child, LH rights left\n";
	cout << "Insertion nums: ";
	for (int i : LD_RH_LH_LH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(LD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LD_RH_LH_LH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "rightBalance RH head, LH right child, LH right child left child test ";

	return pass;
}

bool test_left_delele_RH_LH_RH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from left side DBL rotation on RH head, LH right child, RH rights left\n";
	cout << "Insertion nums: ";
	for (int i : LD_RH_LH_RH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(LD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LD_RH_LH_RH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "rightBalance RH head, LH right child, RH right child left child test ";

	return pass;
}

bool test_left_delete_RH_LH_EH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from left side DBL rotation on RH head, LH right child, EH rights left\n";
	cout << "Insertion nums: ";
	for (int i : LD_RH_LH_EH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(LD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LD_RH_LH_EH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "rightBalance RH head, LH right child, EH right child left child test ";

	return pass;
}

bool test_left_delete_RH_EH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from left side on RH head, EH right child \n";
	cout << "Insertion nums: ";
	for (int i : LD_RH_EH)
	{
		avl.Insert(i);
		cout << i << " ";
	}

	avl.Delete(LD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LD_RH_EH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "rightBalance RH head, EH right child test ";

	return pass;
}

bool test_left_delete_RH_RH()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Delete from left side on RH head, RH right child \n";
	cout << "Insertion nums: ";
	for (int i : LD_RH_RH)
	{
		avl.Insert(i);
		cout << i << " "; 
	}

	avl.Delete(LD_DELETE);

	cout << "\nVerify tree:\nAVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nAnswer: ";
	for (int result : RESULT_LD_RH_RH)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "rightBalance RH head, RH right child test ";

	return pass;
}

bool test_height()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	for (int i : test_nums )
	{
		avl.Insert(i);
	}
	
	if (avl.Height() == HEIGHT)
		pass = true; 

	cout << "correct height of tree test "; 
	return pass; 
}

bool test_op_equal()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;
	AVLTree<int> avl2; 

	cout << "Operator equal "; 
	for (int i : test_nums)
	{
		avl.Insert(i);
	}

	for (int i : LD_RH_LH_EH)
	{
		avl2.Insert(i);
	}

	avl = avl2; 

	cout << "\nVerify tree:\nNew AVL:  ";
	avl.TraverseBreadthOrder(output);
	cout << "\nCopied AVL: ";
	avl2.TraverseBreadthOrder(output); 

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "operator equal test ";

	return pass; 
}

bool test_copy_ctor()
{
	bool pass = false;
	char verify = '\0';
	AVLTree<int> avl;

	cout << "Copy c'tor test "; 
	for (int i : test_nums)
	{
		avl.Insert(i);
	}

	AVLTree<int> avl2 = avl; 

	cout << "\nVerify tree:\nNew AVL:  ";
	avl2.TraverseBreadthOrder(output);
	cout << "\nCopied AVL: ";
	for (int result : nums_result)
		cout << result << " ";

	cout << endl;
	cout << "match? (y/n) ";
	cin >> verify;

	verify = toupper(verify);

	verify == 'Y' ? pass = true : pass = false;

	cout << "Copy c'tor test ";

	return pass;
}
