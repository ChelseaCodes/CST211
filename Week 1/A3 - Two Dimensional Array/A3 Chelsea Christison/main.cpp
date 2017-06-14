/*************************************************************
* Author:		Chelsea Christison
* Filename:		main.cpp
* Date Created:	4.1.2017
* Modifications:
*	4.10 - testing const objects
************************************************************/
#define _CRTDBG_MAP_ALLOC
typedef bool(*FunctionPointer)();  // Define a function pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>
#include "array2D.h"
#include "exception.h"

// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 15;

// Test function declaration
bool test_neg_row();			
bool test_neg_column();			
bool test_row_upper_bounds();	
bool test_row_lower_bounds();	
bool test_column_upper_bounds();
bool test_column_lower_bounds();
bool test_2_arg_ctor();			
bool test_default_ctor();	
bool test_adding_values();		
bool test_larger_row_with_data();
bool test_smaller_row_with_data();		
bool test_larger_column_with_data();	
bool test_smaller_column_with_data();
bool test_copy_ctor();
bool test_op_eql();
//complex tests
bool test_neg_row_complex();
bool test_neg_column_complex(); 
bool test_row_lower_bounds_complex();
bool test_row_upper_bounds_complex();
bool test_column_upper_bounds_complex();
bool test_column_lower_bounds_complex();
bool test_2_arg_ctor_complex();
bool test_default_ctor_complex();
bool test_adding_values_complex();
bool test_larger_row_with_data_complex();
bool test_smaller_row_with_data_complex();
bool test_larger_column_with_data_complex();
bool test_smaller_column_with_data_complex();
bool test_copy_ctor_complex();
bool test_op_eql_complex();
//test const objects / methods 
bool test_view_elements_const();	//can't modify const methods ONLY view



// Array of test functions
FunctionPointer test_functions[] = { test_neg_row, test_neg_column, test_row_upper_bounds, test_row_lower_bounds,
	test_column_upper_bounds, test_column_lower_bounds, test_2_arg_ctor, test_default_ctor, test_adding_values,
	test_larger_row_with_data, test_smaller_row_with_data, test_larger_column_with_data, test_smaller_column_with_data,
	test_copy_ctor, test_op_eql, test_neg_row_complex, test_neg_column_complex, test_row_lower_bounds_complex, 
	test_row_upper_bounds_complex, test_column_upper_bounds_complex, test_column_lower_bounds_complex, 
	test_2_arg_ctor_complex, test_default_ctor_complex, test_adding_values_complex, test_larger_row_with_data_complex,
	test_smaller_row_with_data_complex, test_larger_column_with_data_complex, test_smaller_column_with_data_complex,
	test_copy_ctor_complex, test_op_eql_complex };

#include "row.h"
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	// Run the test functions
	for each (FunctionPointer func in test_functions)
	{
		if (func())
		{
			cout << "passed\n";
		}
		else
		{
			cout << "***** failed *****\n";
		}
	}
	cout << "\nPress Any Key to Exit";
	cin.get();

	system("pause");
	return 0; 
}

bool test_neg_row()
{
	// Exception should be thrown for negative number
	bool pass = false;

	Array2D<int> val_len(20, 2);

	try
	{
		val_len.setRow(-5);
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "set negative row test ";

	return pass;
}

bool test_neg_column()
{
	bool pass = false;

	Array2D<int> val_len(20, 2);

	try
	{
		val_len.setColumn(-3);
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "set negative column test ";

	return pass;
}

bool test_row_upper_bounds()
{
	bool pass = false;

	Array2D<int> val_len(20, 5);

	try
	{
		val_len[30][0] = 0;
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "row upper bounds test ";

	return pass;
}

bool test_row_lower_bounds()
{
	bool pass = false;


	Array2D<int> val_len(20, 5);

	try
	{
		val_len[-1][0] = 0; 
	}
	catch(Exception ex)
	{
		pass = true; 
	}

	cout << "row lower bounds test ";

	return pass;
}

bool test_column_upper_bounds()
{
	bool pass = false;

	Array2D<int> val_len(20, 5);

	try
	{
		val_len[0][10] = 0;
	}
	catch (Exception ex)
	{
		pass = true;
	}

	cout << "column upper bounds test ";

	return pass;
}

bool test_column_lower_bounds()
{
	bool pass = false;

	Array2D<int> val_len(20, 5);

	try
	{
		val_len[10][-3] = 0;
	}
	catch (Exception ex)
	{
		pass = true;
	}

	cout << "column lower bounds test ";

	return pass;
}

bool test_2_arg_ctor()
{
	bool pass = true;
	int row = 15;
	int column = 15;


	Array2D<int> val_len(row,column);

	if (val_len.getRow() != row)
		pass = false;

	if (val_len.getColumn() != column)
		pass = false;

	cout << "2 arg ctor test ";

	return pass;
}

bool test_default_ctor()
{
	bool pass = true;
	int row = 0;
	int column = 0;

	Array2D<int> val_len;

	if (val_len.getRow() != row)
		pass = false;

	if (val_len.getColumn() != column)
		pass = false;

	cout << "Default ctor test ";

	return pass;
}

bool test_adding_values()
{
	bool pass = true;
	int temp;
	int col = 2; 
	int row = 5;
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int temp_data_index = 0; 
	Array2D<int> val_len(row,col);

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for(int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = test_data[temp_data_index++];
		}
	}

	temp_data_index = 0;

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c];

			if (temp != test_data[temp_data_index++])
				pass = false;			
		}
	}

	cout << "Add values test ";

	return pass;
}

bool test_larger_row_with_data()
{
	bool pass = true;
	int temp;
	int col = 2;
	int old_row = 5;
	int num_elements = 10;  // Change this if test data changes
	int new_length = 2 * num_elements;
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int temp_data_index = 0;

	Array2D<int> val_len(old_row, col);

	//fill array 
	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = test_data[temp_data_index++];
		}
	}
	temp_data_index = 0;

	val_len.setRow(new_length);  // Double the length after data was assigned
	
	//check values up to the old row value 
	for (int r = 0; r < old_row; ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c];

			if (temp != test_data[temp_data_index++])
				pass = false;
		}
	}
	//check newest rows, which are garbage or 0
	for(int r = old_row; r < val_len.getRow(); r++)
	{
		for(int c(0); c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c]; 
			
			if (temp > 0)
				pass = false; 
		}
	}
	
	cout << "Change to larger row with data test ";

	return pass;
}

bool test_smaller_row_with_data()
{
	bool pass = false;
	int col = 2;
	int old_row = 5;
	int new_length = 3;
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int temp_data_index = 0;

	Array2D<int> val_len(old_row, col);

	//fill array 
	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = test_data[temp_data_index++];
		}
	}
	val_len.setRow(new_length);  // less rows 

	//try to access the deleted row values
	try
	{
		for (int r = 0; r < old_row; ++r)
		{
			for (int c(0); c < val_len.getColumn(); c++)
			{
				val_len[r][c];
			}
		}
	}
	catch(Exception ex)
	{
		pass = true; 
	}
	cout << "Change to smaller row with data test ";

	return pass;
}

bool test_larger_column_with_data()
{
	bool pass = true;
	int temp;
	int old_col = 2;
	int row = 5;
	int new_column = old_col * 2; 
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int temp_data_index = 0;

	Array2D<int> val_len(row, old_col);

	//fill array 
	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = test_data[temp_data_index++];
			cout << val_len[r][c] << " ";
		}
	}
	cout << endl; 
	val_len.setColumn(new_column); 

	//test the extra columns in each row for garbage 
	for(int r = 0; r < val_len.getRow(); r++)
	{
		for(int c = 0; c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c]; 
			cout << val_len[r][c] << " ";
			if (temp > 0)
				pass = false; 
		}
	}

	cout << "Set larger column with data test ";

	return pass;
}

bool test_smaller_column_with_data()
{
	bool pass = true;
	int temp;
	int old_col = 5;
	int row = 2;
	int new_column = 2;
	int length = 10; 
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int temp_data_index = 0;

	Array2D<int> val_len(row, old_col);

	//fill array 
	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = test_data[temp_data_index++];
			cout << val_len[r][c] << " ";
		}
	}
	val_len.setColumn(new_column);
	cout << endl;
	//access all columns. there shouldn't be garbage
	//in any
	for (int r = 0; r < val_len.getRow(); r++)
	{
		for (int c = 0; c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c];
			cout << val_len[r][c] << " ";
			if (temp < 0)
				pass = false;
		}
	}

	cout << "Set smaller column with data test ";

	return pass;
}

bool test_copy_ctor()
{
	bool pass = true;
	int temp; 
	int col = 2;
	int row = 5;
	int num_elements = 10; 
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int temp_data_index = 0;

	Array2D<int> val_len(row, col);

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = test_data[temp_data_index++];
		}
	}
	temp_data_index = 0; 
	
	Array2D<int> val_len_cpy(val_len); 

	// Check data integrity
	for (int r = 0; r < row; ++r)
	{
		for (int c(0); c < col; c++)
		{
			temp = val_len_cpy[r][c];

			if (temp != test_data[temp_data_index++])
				pass = false;
		}
	}
	cout << "Copy ctor test ";

	return pass;
}

bool test_op_eql()
{
	bool pass = true;
	int temp;
	int col = 2;
	int row = 5;
	int num_elements = 10;
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int temp_data_index = 0;

	Array2D<int> val_len(row, col);
	Array2D<int> val_len_2(row, col); 

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = test_data[temp_data_index++];
		}
	}
	temp_data_index = 0;

	val_len_2 = val_len; 

	// Check data integrity
	for (int r = 0; r < row; ++r)
	{
		for (int c(0); c < col; c++)
		{
			temp = val_len_2[r][c];

			if (temp != test_data[temp_data_index++])
				pass = false;
		}
	}

	cout << "Op equal test ";

	return pass;
}

////////////////////////////////////////////
// Complex data type tests
////////////////////////////////////////////

bool test_neg_row_complex()
{
	// Exception should be thrown for negative number
	bool pass = false;

	Array2D<string> val_len(20, 2);

	try
	{
		val_len.setRow(-5);
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Negative length test complex ";

	return pass;
}

bool test_neg_column_complex()
{
	bool pass = false; 

	Array2D<string> val_len(20, 2);

	try
	{
		val_len.setColumn(-3);
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Lower bounds test complex ";

	return pass; 
}

bool test_row_lower_bounds_complex()
{
	bool pass = false;

	Array2D<string> val_len(20, 5);

	try
	{
		val_len[-3][0] = "test";
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "row lower bounds test complex ";

	return pass;
}

bool test_row_upper_bounds_complex()
{
	bool pass = false;

	Array2D<string> val_len(20, 5);

	try
	{
		val_len[30][0] = "test";
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "row upper bounds test complex ";

	return pass;
}

bool test_column_upper_bounds_complex()
{
	bool pass = false;

	Array2D<string> val_len(20, 5);

	try
	{
		val_len[0][10] = "test";
	}
	catch (Exception ex)
	{
		pass = true;
	}

	cout << "column upper bounds test complex ";

	return pass;
}

bool test_column_lower_bounds_complex()
{
	bool pass = false;

	Array2D<string> val_len(20, 5);

	try
	{
		val_len[10][-3] = "test";
	}
	catch (Exception ex)
	{
		pass = true;
	}

	cout << "column lower bounds test complex ";

	return pass;
}

bool test_2_arg_ctor_complex()
{
	bool pass = true;
	int row = 15;
	int column = 15;

	Array2D<string> val_len(row, column);

	if (val_len.getRow() != row)
		pass = false;

	if (val_len.getColumn() != column)
		pass = false;

	cout << "2 arg ctor test complex ";
	return pass;
}

bool test_default_ctor_complex()
{
	bool pass = true;
	int row = 0;
	int column = 0;

	Array2D<string> val_len;

	if (val_len.getRow() != row)
		pass = false;

	if (val_len.getColumn() != column)
		pass = false;

	cout << "Default ctor test complex ";

	return pass;
}

bool test_adding_values_complex()
{
	bool pass = true;
	string temp;
	int col = 2;
	int row = 5;
	int temp_data_index = 0;

	Array2D<string> val_len(row, col);

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = NAMES[temp_data_index++];
		}
	}

	temp_data_index = 0;

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c];

			if (temp != NAMES[temp_data_index++])
				pass = false;
		}
	}

	cout << "Add values test complex ";

	return pass;
}

bool test_larger_row_with_data_complex()
{
	bool pass = true;
	string temp;
	int col = 2;
	int old_row = 5;
	int num_elements = 10;  // Change this if test data changes
	int new_length = 2 * num_elements;
	int temp_data_index = 0;

	Array2D<string> val_len(old_row, col);

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = NAMES[temp_data_index++];
		}
	}

	temp_data_index = 0;

	val_len.setRow(new_length);  // Double the length after data was assigned

	for (int r = 0; r < old_row; ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c];

			if (temp != NAMES[temp_data_index++])
				pass = false;
		}
	}

	//check newest rows, which are empty strings
	for (int r = old_row; r < val_len.getRow(); r++)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c];

			if (temp != "")
				pass = false;
		}
	}

	cout << "Change larger row with data test complex ";

	return pass;
}

bool test_smaller_row_with_data_complex()
{
	bool pass = false;
	string temp;
	int temp_data_index = 0; 
	int col = 2; 
	int old_row = 5;
	int new_length = 3;

	Array2D<string> val_len(old_row, col);

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = NAMES[temp_data_index++];
		}
	}

	val_len.setRow(new_length);

	//access deleted values
	try
	{
		for (int r = 0; r < old_row; ++r)
		{
			for (int c(0); c < val_len.getColumn(); c++)
			{
				val_len[r][c];
			}
		}
	}
	catch (Exception ex)
	{
		pass = true;
	}
	cout << "Change smaller row with data test complex ";

	return pass;
}

bool test_larger_column_with_data_complex()
{
	bool pass = true;
	string temp;
	int temp_data_index = 0;
	int old_col = 2;
	int row = 5;
	int new_column = old_col * 2;

	Array2D<string> val_len(row, old_col);

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = NAMES[temp_data_index++];
			cout << val_len[r][c] << " "; 
		}
	}

	cout << endl; 
	val_len.setColumn(new_column);

	// Check new columns for empty strings
	for (int r = 0; r < val_len.getRow(); r++)
	{
		for (int c = 0 ; c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c];
			cout << val_len[r][c] << " ";
			if (temp != "")
				pass = false;
		}
	}
	cout << "Set larger column with data test complex ";

	return pass;
}

bool test_smaller_column_with_data_complex()
{
	bool pass = true; 
	string temp;
	int old_col = 5;
	int row = 2;
	int new_column = 2;
	int length = 10;
	int temp_data_index = 0;

	Array2D<string> val_len(row, old_col);

	//fill array 
	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = NAMES[temp_data_index++];
		}
	}

	val_len.setColumn(new_column);

	
	//access all columns. there shouldn't be empty strings
	for (int r = 0; r < val_len.getRow(); r++)
	{
		for (int c = 0; c < val_len.getColumn(); c++)
		{
			temp = val_len[r][c];
			if (temp == "")
				pass = false;
		}
	}

	cout << "set smaller column with data test complex "; 
	return pass; 
}

bool test_copy_ctor_complex()
{
	bool pass = true;
	string temp; 
	int col = 2; 
	int row = 5; 
	int temp_data_index = 0; 

	Array2D<string> val_len(row, col);

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = NAMES[temp_data_index++];
		}
	}

	temp_data_index = 0; 
	Array2D<string> val_len_cpy(val_len);

	// Check data integrity
	for (int r = 0; r < row; ++r)
	{
		for (int c(0); c < col; c++)
		{
			temp = val_len_cpy[r][c];

			if (temp != NAMES[temp_data_index++])
				pass = false;
		}
	}
	cout << "Copy ctor test complex ";

	return pass;
}

bool test_op_eql_complex()
{
	bool pass = true;
	string temp;
	int col = 2;
	int row = 5;
	int temp_data_index = 0;

	Array2D<string> val_len(row, col);

	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = NAMES[temp_data_index++];
		}
	}

	temp_data_index = 0;
	Array2D<string> val_len_cpy;

	val_len_cpy = val_len; 

	// Check data integrity
	for (int r = 0; r < row; ++r)
	{
		for (int c(0); c < col; c++)
		{
			temp = val_len_cpy[r][c];

			if (temp != NAMES[temp_data_index++])
				pass = false;
		}
	}

	cout << "Op equal test complex ";

	return pass;
}

bool test_view_elements_const()
{
	bool pass = true;
	int col = 5;
	int row = 2;
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int temp_data_index = 0;

	Array2D<int> val_len(row, col);

	//fill array 
	for (int r = 0; r < val_len.getRow(); ++r)
	{
		for (int c(0); c < val_len.getColumn(); c++)
		{
			val_len[r][c] = test_data[temp_data_index++];
		}
	}

	//create const obj using data from val_len
	const Array2D<int> val_len_const(val_len);

	//cant set it - gives error
	//val_len_const[0][0] = 13;
	//can only view contents
	int value =	val_len_const[0][0]; 
	
	return pass;
}
