/*************************************************************
* Author:		Chelsea Christison
* Filename:		main.h
* Date Created:	4.4.2017
*
* Modifications:
*	4.6 - modeled tests after given test stub
**************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

typedef bool(*FunctionPointer)(); //func ptr of type bool

#include <iostream>
using std::cout;
using std::endl; 
using std::cin; 

#include <iomanip>
using std::setw;
using std::left; 

#include "linkedlist.h"

char b = 'B';
char a = 'A';
char f = 'F';
char e = 'E';
char g = 'G';
char l = 'L';
char z = 'Z';
char o = 'O';
char h = 'H';
char p = 'P';

//Test Function Decls
bool test_default_ctor_getHead();
bool test_default_ctor_getTail(); 
bool test_copy_ctor(); 
bool test_op_equals(); 
bool test_prepend_empty_list();
bool test_append_empty_list();
bool test_insert_after_empty_list();
bool test_insert_before_empty_list();
bool test_grab_first_empty_list();
bool test_grab_last_emtpy_list(); 
bool test_fill_list_prepend();
bool test_fill_list_append();
bool test_extract();
bool test_extract_nonexistent(); 

FunctionPointer test_functions[] = { test_default_ctor_getHead, test_default_ctor_getTail,
	test_copy_ctor, test_op_equals,test_prepend_empty_list, test_append_empty_list,
	test_insert_after_empty_list, test_insert_before_empty_list, test_grab_first_empty_list,
	test_grab_last_emtpy_list, test_fill_list_prepend,test_fill_list_append, test_extract,
	test_extract_nonexistent };

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	for each(FunctionPointer func in test_functions)
	{
		if(func())
		{
			cout << " passed\n"; 
		}
		else
		{
			cout << "******** FAILED *********\n";
		}
	}
	system("pause"); 
	return 0; 
}

void TestLinkedList()
{
	char a = 65;
	char b = 66;
	char c = 67;
	char d = 68;
	char z = 'z';
	char y = 'y';
	char x = 'x';
	char v = 'v'; 

	cout << "testing linked list default c'tor" << endl;
	LList<char> char_list;

	cout << "Testing isEmpty function " << char_list.isEmpty() << endl; 

	cout << "Testing linked list prepend" << endl; 
	char_list.Prepend(d); 
	char_list.Prepend(b); 
	char_list.Prepend(c);
	char_list.Prepend(a);
		cout << "Testing isEmpty function again " << char_list.isEmpty() << endl;

	cout << "testing linked list print forwards" << endl; 
	char_list.PrintForwards(); 

	cout << "testing linked list print backwards" << endl; 
	char_list.PrintBackwards(); 

	cout << "Testing linked list append" << endl; 
	char_list.Append(v);
	char_list.Append(z);

	cout << "Print forward: " << endl; 
	char_list.PrintForwards(); 

	cout << "Print backwards: " << endl; 
	char_list.PrintBackwards(); 

	cout << "testing linked list First: " << endl; 
	cout << char_list.First() << endl; 

	cout << "Testing linked list Last: " << endl; 
	cout << char_list.Last() << endl;
	
	cout << "Testing extract\nExtracting A" << endl; 
	cout << char_list.Extract(a) << endl;
	cout << "Extracting Z: " << char_list.Extract(z) << endl;
	cout << "Extracting A: " << char_list.Extract(a) << endl; 
	cout << "Print all" << endl; 
	char_list.PrintForwards(); 

	cout << "Testing Insert After\nInsert Z, after D " << endl; 
	char_list.InsertAfter(z, d); 
	cout << "Print All: " << endl; 
	char_list.PrintForwards(); 
	cout << "Inserting after non existing link\nInsert C after A " << endl;
	char_list.InsertAfter(c, a); 
	cout << "Print All: " << endl; 
	char_list.PrintForwards(); 
}

bool test_default_ctor_getHead()
{
	bool pass = false; 

	LList<char> test_list;
	
	try
	{
		test_list.getHead(); 
	}
	catch(Exception & ex)
	{
		pass = true; 
	}

	cout << "Default c'tor get head test "; 
	return pass; 
}

bool test_default_ctor_getTail()
{
	bool pass = false;

	LList<char> test_list;

	try
	{
		test_list.getTail();
	}
	catch (Exception & ex)
	{
		pass = true;
	}

	cout << "Default c'tor get tail test ";
	return pass;
}

bool test_copy_ctor()
{
	bool pass = true;
	int num_elements = 10;
	char * test_data[] = { "B", "A", "F", "E", "G", "L", "Z", "O", "H", "P" };

	LList<char> test_list;
	for(int i(0); i < num_elements; i++)
	{
		test_list.Prepend(*test_data[i]); 
	}

	LList<char> copy_list = test_list; 
	
	//head should contain same 
	if(*(test_list.getHead()->getData()) != *(copy_list.getHead()->getData()))
	{
		pass = false; 
	}
	if (*(test_list.getTail()->getData()) != *(copy_list.getTail()->getData()))
	{
		pass = false;
	}

	cout << "Copy c'tor test "; 
	return pass; 
}

bool test_op_equals()
{
	bool pass = true; 
	int num_elements = 5;
	char * test_data[] = { "B", "A", "F", "E", "G"};
	char * test_data2[] = { "L", "Z", "O", "H", "P" };

	LList<char> default_copy; 
	for (int i(0); i < num_elements; i++)
	{
		default_copy.Prepend(*test_data2[i]);
	}

	LList<char> test_list;
	for (int i(0); i < num_elements; i++)
	{
		test_list.Prepend(*test_data[i]);
	}

	default_copy = test_list;

	if (*(test_list.getHead()->getData()) != *(default_copy.getHead()->getData()))
	{
		pass = false;
	}
	if (*(test_list.getTail()->getData()) != *(default_copy.getTail()->getData()))
	{
		pass = false;
	}

	cout << "Operator equals test ";
	return pass;
}

bool test_prepend_empty_list()
{
	bool pass = true;
	LList<char> test_list;
	test_list.Prepend(z); 

	if(*(test_list.getHead()->getData()) != z)
	{
		pass = false; 
	}
	if(*(test_list.getTail()->getData()) != z)
	{
		pass = false;
	}

	cout << "Prepend to empty list test ";
	return pass; 
}

bool test_append_empty_list()
{
	bool pass = true;
	LList<char> test_list;
	test_list.Append(a);

	if (*(test_list.getHead()->getData()) != a)
	{
		pass = false;
	}
	if (*(test_list.getTail()->getData()) != a)
	{
		pass = false;
	}

	cout << "Append to empty list test ";
	return pass;
}

bool test_insert_after_empty_list()
{
	bool pass = false;
	LList<char> test_list;
	try
	{
		test_list.InsertAfter(a, z);
	}
	catch(Exception& ex)
	{
		pass = true; 
	}

	cout << "insert after empty list test ";

	return pass;
}

bool test_insert_before_empty_list()
{
	bool pass = false;
	LList<char> test_list;
	try
	{
		test_list.InsertBefore(a, z);
	}
	catch (Exception& ex)
	{
		pass = true;
	}

	cout << "insert before empty list test ";

	return pass;
}

bool test_grab_first_empty_list()
{
	bool pass = false;
	LList<char> test_list;
	try
	{
		test_list.First();
	}
	catch (Exception& ex)
	{
		pass = true;
	}

	cout << "grab first element empty list test ";

	return pass;
}

bool test_grab_last_emtpy_list()
{
	bool pass = false;
	LList<char> test_list;
	try
	{
		test_list.Last();
	}
	catch (Exception& ex)
	{
		pass = true;
	}

	cout << "grab Last element empty list test ";

	return pass;
}

bool test_fill_list_prepend()
{
	bool pass = true;
	char input; 
	int num_elements = 10;
	char * test_data[] = { "B", "A", "F", "E", "G", "L", "Z", "O", "H", "P" };

	LList<char> test_list;
	cout << "\nFill list prepend visual test: " << endl; 
	cout << left << setw(13) << "Test Data: "; 
	for (int i(0); i < num_elements; i++)
	{
		test_list.Prepend(*test_data[i]);
		cout << *test_data[i] << " "; 
	}
	cout << setw(14) << "\nList: ";
	test_list.PrintBackwards();

	cout << "\nPass visual test?(y/n)";
	cin >> input; 

	if (input == 'y' || input == 'Y')
		pass = true;
	else
		pass = false;

	cout << "Fill list prepend test "; 
	return pass;
}

bool test_fill_list_append()
{
	bool pass = true;
	char input;
	int num_elements = 10;
	char * test_data[] = { "B", "A", "F", "E", "G", "L", "Z", "O", "H", "P" };

	LList<char> test_list;
	cout << "\nFill list append visual test: " << endl;
	cout << left << setw(13) << "Test Data: ";
	for (int i(0); i < num_elements; i++)
	{
		test_list.Append(*test_data[i]);
		cout << *test_data[i] << " ";
	}
	cout << setw(14) << "\nList: ";
	test_list.PrintForwards();

	cout << "\nPass visual test?(y/n)";
	cin >> input;

	if (input == 'y' || input == 'Y')
		pass = true;
	else
		pass = false;

	cout << "Fill list prepend test ";
	return pass;
}

bool test_extract()
{
	bool pass = false; 
	int num_elements = 10; 
	char * test_data[] = { "B", "A", "F", "E", "G", "L", "Z", "O", "H", "P" };

	LList<char> test_list;
	for (int i(0); i < num_elements; i++)
	{
		test_list.Append(*test_data[i]);
	}

	cout << "\nExtract " << g << " test" << endl; 
	cout << setw(14)<< left << "List: "; 
	test_list.PrintForwards(); 
	
	if(test_list.Extract(g))
	{
		pass = true;
		cout << setw(15) << left << "\nList after: ";
		test_list.PrintForwards(); 
	}

	cout << "\nExtraction test ";
	return pass; 
}

bool test_extract_nonexistent()
{
	bool pass = false;
	int num_elements = 9;
	char * test_data[] = { "B", "A", "F", "E", "L", "Z", "O", "H", "P" };

	LList<char> test_list;
	for (int i(0); i < num_elements; i++)
	{
		test_list.Append(*test_data[i]);
	}

	cout << "\nExtract nonexistent " << g << " test" << endl;
	cout << setw(14) << left << "List: ";
	test_list.PrintForwards();

	if (!test_list.Extract(g))
	{
		pass = true;
		cout << setw(15) << left << "\nList: ";
		test_list.PrintForwards();
	}

	cout << "\nExtract non existing item test ";
	return pass;
}