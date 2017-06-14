/*************************************************************
* Author:		Chelsea Christison
* Filename:		main.cpp
* Date Created:	4/18/2017
* Modifications:	
*
* Lab/Assignment: Lab 2 – All Sorts of Sorts
*
* Overview:
*	This program times how fast 7 different sorts are 
*	
*	- Brute Force Bubble 
*	- Flagged Bubble
*	- Selection 
*	- Insertion
*	- Shell
*	- Heap 
*	- Merge
*	- Quick 
*	
*	Using 3 different containers: standard array, 
*	vector and my own array class. 
*	Containers will contain the same 10,000 elements
*	to sort through, and will each have their own timers
*	to time how quickly each Sort function sorted the 
*	same 10K elements. 
*	
* Input:
*	Command line passes in the number of elements to sort
*	through, 10,000. 
*	
* Output:
*	The output of this program will be to console and to 
*	the data.txt file. 
*	Console will output the name of the sort being executed,
*	how quickly it sorted the three different containers,
*	and the name of the file that holds the output. 
*	The data.txt file will hold every 1000th element 
*	to prove it was sorted. 
*
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <time.h>
#include <iostream>
using std::cout;
#include <vector>
using std::vector; 
#include <fstream>
using std::ofstream;
#include <iomanip>
using std::setprecision; 
using std::fixed; 

#include "sorts.h"
#include "Array.h"

//Struct to hold necessary containers used to test sorts. 
struct SortObj
{
	Array<int> my_array;
	vector<int> v_array;
	int * c_array_original;
	int * c_array_to_sort;
	int elements;
};

//function pointer to hold all testing functions
typedef void(*FunctionPointer)(SortObj); 

//display function
void DisplaySortTime(const char * array_name, double time_elapsed); 

//resets the standard int array
void ResetArray(int * cArray, int * original, int n);

/*						Sorting functions						*/

// Brute Force Bubble Sort O(n^2)
void Test_BruteForceBubbleSort(SortObj sort);
void Test_BFB_myArray(Array<int> myArray, int n, ofstream& fout);
void Test_BFB_vArray(vector<int> vArray, int n, ofstream& fout);
void Test_BFB_cArray(int cArray[], int n, ofstream& fout);

// Flagged Bubble Sort O(n^2)
void Test_FlaggedBubbleSort(SortObj sort);
void Test_FBS_myArray(Array<int> myArray, int n, ofstream& fout);
void Test_FBS_vArray(vector<int> vArray, int n, ofstream& fout);
void Test_FBS_cArray(int* cArray, int n, ofstream& fout);

// Selection Sort 0(n^2)
void Test_SelectionSort(SortObj sort); 
void Test_SS_myArray(Array<int> myArray, int n, ofstream& fout);
void Test_SS_vArray(vector<int> vArray, int n, ofstream& fout); 
void Test_SS_cArray(int* cArray, int n, ofstream& fout); 

// Insertion Sort O(n^2)
void Test_InsertionSort(SortObj sort);
void Test_IS_myArray(Array<int> mArray, int n, ofstream& fout);
void Test_IS_vArray(vector<int> vArray, int n, ofstream& fout); 
void Test_IS_cArray(int * cArray, int n, ofstream& fout); 

// Shell Sort O(n log n)
void Test_ShellSort(SortObj sort); 
void Test_SHLS_myArray(Array<int> mArray, int n, ofstream& fout);
void Test_SHLS_vArray(vector<int> vArray, int n, ofstream& fout);
void Test_SHLS_cArray(int * cArray, int n, ofstream& fout);

// Heap Sort O(n log n)
void Test_HeapSort(SortObj sort); 
void Test_HS_myArray(Array<int> myArray, int n, ofstream& fout);
void Test_HS_vArray(vector<int> vArray, int n, ofstream& fout);
void Test_HS_cArray(int * cArray, int n, ofstream& fout);  

// Merge Sort O(n log n)
void Test_MergeSort(SortObj sort); 
void Test_MS_myArray(Array<int> myArray, int n, ofstream& fout); 
void Test_MS_vArray(vector<int> vArray, int n, ofstream& fout);
void Test_MS_cArray(int * cArray, int n, ofstream& fout);

// Quick Sort O(n log n)
void Test_QuickSort(SortObj sort); 
void Test_QS_myArray(Array<int> myArray, int n, ofstream& fout);
void Test_QS_vArray(vector<int> vArray, int n, ofstream& fout);
void Test_QS_cArray(int * cArray, int n, ofstream& fout); 

//assign 7 functions to function pointer
FunctionPointer run_sorts[] = { Test_BruteForceBubbleSort, Test_FlaggedBubbleSort, Test_SelectionSort,
								Test_InsertionSort, Test_ShellSort, Test_HeapSort, Test_MergeSort,
								Test_QuickSort };

//const chars used for cout and fout
const char * MYARRAY = "My Array";
const char * VARRAY = "Vector Array";
const char * CARRAY = "Native Array"; 

//number of elements to skip when outputting to data.txt
const int ELEMPEEK = 1; 

int main(int argc, char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(NULL));				//seed random generator
	int random_number = 0;			//integer used to fill array
	const int n = atoi(argv[1]);	//gets the number of elements from command line

	//struct that holds the 3 containers, assign memory 
	SortObj sort; 
	sort.my_array = Array<int>(n);
	sort.v_array = vector<int>(n); 
	sort.c_array_original = new int[n];
	sort.c_array_to_sort = new int[n];
	sort.elements = n; 

	//populate the containers with random numbers. but all the same 
	for(int i = 0; i < n; i++)
	{
		random_number = rand() % n;

		sort.my_array[i] = random_number; 
		sort.v_array[i] = random_number;
		sort.c_array_original[i] = random_number;
		sort.c_array_to_sort[i] = random_number;
	}

	//call tests
	cout << "Sorting " << n << " items...\n" << endl; 

	Test_ShellSort(sort); 
	//for each(FunctionPointer func in run_sorts)
	//{
	//	func(sort); 

	//	//reset int * after every call
	//	ResetArray(sort.c_array_to_sort, sort.c_array_original, n);	
	//	cout << "-\n\n";
	//}

	//clean up memory 
	delete[] sort.c_array_original;
	delete[] sort.c_array_to_sort;

	return 0; 
}

/*********************************************************************************
* Purpose:
*	This function overwrites the int * c_array to contain the original set of
*	randomized values as the other two containers. Such that after each sorting
*	function, the array is exactly like the others. 
* Precondition:
*	cArray - array to overwrite after going through a sort test
*	original - array to copy from, unsorted copy 
*	n - number of elements in the array
* Postcondition:
*	changes cArray to have the original unsorted copy before sorting again
* 
**********************************************************************************/
void ResetArray(int * cArray, int * original, int n)
{ 
	for(int i = 0; i < n; i++)
	{
		cArray[i] = original[i]; 
	}
}

/*********************************************************************************
* Purpose:
*	This function outputs the name of the sort and its sorting time 
* Precondition:
*  array_name - const char of the name of the array used in sort 
*  time_elapsed - time it took to sort array, in seconds. 
* Postcondition:
*  output of name and time 
**********************************************************************************/
void DisplaySortTime(const char * array_name, double time_elapsed)
{
	cout << array_name << "\nTime Elapsed: " << setprecision(4) 
		 << fixed << time_elapsed << " seconds" << endl; 
}

/*********************************************************************************
* Purpose:
*	This function drives the tests for Brute Bubble sort for all 3 containers
* Precondition:
*	sort - SortObj struct that has the three arrays and number of elements in each
* Postcondition:
*   Calls the brute force bubble sort test for each array type and sorts
**********************************************************************************/
void Test_BruteForceBubbleSort(SortObj sort)
{
	const char * sortname = "[ = Brute Force Bubble Sort = ]";  
	ofstream fout("data.txt", std::ios_base::app);	//open file for appending
	fout << sortname; 
	cout << sortname << endl; 

	Test_BFB_myArray(sort.my_array, sort.elements, fout); 
    Test_BFB_vArray(sort.v_array, sort.elements, fout);
	Test_BFB_cArray(sort.c_array_to_sort, sort.elements, fout); 
	fout << "\n";

	fout.close(); 
}

/*********************************************************************************
* Purpose:
*	This function tests brute force bubble sort on Array class I made. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort. 
* Precondition:
*	myArray - copy of the unsorted array of Array<int> 
*	n - number of elements in array 
*	fout - output file stream to data.txt in append mode
* Postcondition:
*   myArray will be sorted, and fout will write and change data.txt by appending 
*   the sorted array at every nth interval. 
*
**********************************************************************************/
void Test_BFB_myArray(Array<int> myArray, int n, ofstream& fout)
{
	//begin clock, call sort then store the ending clock time
	clock_t start = clock();
	BruteForceBubbleSort(myArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(MYARRAY, elapsed);

	fout << "\n" << MYARRAY << ": ";
	for(int i = 0; i < n; i+= ELEMPEEK)
	{
		fout << myArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n"; 
}

/*********************************************************************************
* Purpose:
*	This function tests brute force bubble sort on a vector array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort. 
* Precondition:
*   myArray - copy of the unsorted array of Array<int>
*	n - number of elements in array
*	fout - output file stream to data.txt in append mode
* Postcondition:
*	the vector array will be sorted, and results will be outputted to console
*	and to data.txt
**********************************************************************************/
void Test_BFB_vArray(vector<int> vArray, int n, ofstream& fout)
{
	//begin clock, call sort then store the ending clock time
	clock_t start = clock();
	BruteForceBubbleSort(vArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(VARRAY, elapsed);

	fout << VARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << vArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests brute force bubble sort on a native integer array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	cArray - integer array with random numbers, passed by pointer
*	n - number of elements in array 
*	fout - output to data.txt, in append mode
* Postcondition:
*	integer array will be sorted, and results will be outputted to console,
*	and to data.txt. Must reset cArray to have original random set of numbers 
*	before the next sorting algorithm calls it. 
*
**********************************************************************************/
void Test_BFB_cArray(int cArray[], int n, ofstream& fout)
{
	clock_t start = clock();
	BruteForceBubbleSort(cArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(CARRAY, elapsed);

	fout << CARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << cArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function drives the tests the Flagged Bubble sort for all 3 containers
* Precondition:
*  sort - SortObj struct that has the three arrays and number of elements in each
* Postcondition:
*   Calls the flagged bubble sort test for each array type and sorts
*
**********************************************************************************/
void Test_FlaggedBubbleSort(SortObj sort)
{
	const char * sortname = "[ = Flagged Bubble Sort = ]";
	ofstream fout("data.txt", std::ios_base::app);	//open file for appending
	fout << sortname;
	cout << sortname << endl;

	Test_FBS_myArray(sort.my_array,sort.elements, fout);
	Test_FBS_vArray(sort.v_array, sort.elements, fout);
	Test_FBS_cArray(sort.c_array_to_sort, sort.elements, fout);
	fout << '\n';

	fout.close();
}

/*********************************************************************************
* Purpose:
*	This function tests flagged bubble sort on my array class. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	myArray - randomized array of type Array<int> 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes myArray to be sorted, and outputs the results to fout and console.
**********************************************************************************/
void Test_FBS_myArray(Array<int> myArray, int n, ofstream& fout)
{
	clock_t start = clock();
	FlaggedBubbleSort(myArray, n);
	clock_t stop = clock();

	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(MYARRAY, elapsed);

	fout << "\n" << MYARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << myArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests flagged bubble sort on a vector array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	vArray - randomized array that is of the vector class
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes vArray to be sorted, and outputs the results to fout and console.
**********************************************************************************/
void Test_FBS_vArray(vector<int> vArray, int n, ofstream& fout)
{
	clock_t start = clock();
	FlaggedBubbleSort(vArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(VARRAY, elapsed);

	fout << VARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << vArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests flagged bubble sort on a native integer array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	cArray - randomized array of integers
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes cArray to be sorted, and outputs the results to fout and console.
*	Must reset to the randomized values before calling the next sort. 
**********************************************************************************/
void Test_FBS_cArray(int* cArray, int n, ofstream& fout)
{
	clock_t start = clock();
	FlaggedBubbleSort(cArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(CARRAY, elapsed);

	fout << CARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << cArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function drives the tests the selection sort for all 3 containers
* Precondition:
*	sort - SortObj struct that has the three arrays and number of elements in each
* Postcondition:
*   Calls the selection sort test for each array type and sorts
**********************************************************************************/
void Test_SelectionSort(SortObj sort)
{
	const char * sortname = "[ = Selection Sort = ]";
	ofstream fout("data.txt", std::ios_base::app);	//open file for appending
	fout << sortname;
	cout << sortname << endl;

	Test_SS_myArray(sort.my_array, sort.elements, fout);
	Test_SS_vArray(sort.v_array, sort.elements, fout);
	Test_SS_cArray(sort.c_array_to_sort, sort.elements, fout);
	fout << "\n"; 

	fout.close();
}

/*********************************************************************************
* Purpose:
*	This function tests selection sort on my array class. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	myArray - randomized array of type Array<int> 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes myArray to be sorted calling SelectionSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_SS_myArray(Array<int> myArray, int n, ofstream& fout)
{
	clock_t start = clock();
	SelectionSort(myArray, n);
	clock_t stop = clock();

	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(MYARRAY, elapsed);

	fout << "\n" << MYARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << myArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests selection sort on a vector array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	vArray - randomized vector class array to sort
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes vArray to be sorted using SelectionSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_SS_vArray(vector<int> vArray, int n, ofstream& fout)
{
	clock_t start = clock();
	SelectionSort(vArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(VARRAY, elapsed);

	fout << VARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << vArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests selection sort on native integer array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	cArray - randomized array of integers to sort
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes cArray to be sorted using SelectionSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_SS_cArray(int* cArray, int n, ofstream& fout)
{
	clock_t start = clock();
	SelectionSort(cArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(CARRAY, elapsed);

	fout << CARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << cArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests insertion sort for all 3 array types 
* Precondition:
*	sort - SortObj struct that has the three arrays and number of elements in each
* Postcondition:
*   Calls the insertion sort test for each array type and sorts
**********************************************************************************/
void Test_InsertionSort(SortObj sort)
{
	const char * sortname = "[ = Insertion Sort = ]";
	ofstream fout("data.txt", std::ios_base::app);	//open file for appending
	fout << sortname;
	cout << sortname << endl;

	Test_IS_myArray(sort.my_array, sort.elements, fout);
	Test_IS_vArray(sort.v_array, sort.elements, fout);
	Test_IS_cArray(sort.c_array_to_sort, sort.elements, fout);
	fout << "\n";

	fout.close();
}

/*********************************************************************************
* Purpose:
*	This function tests insertion sort on my array class. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	myArray - randomized array of type Array<int> 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes myArray to be sorted calling InsertionSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_IS_myArray(Array<int> myArray, int n, ofstream& fout)
{
	clock_t start = clock();
	InsertionSort(myArray, n);
	clock_t stop = clock();

	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(MYARRAY, elapsed);

	fout << "\n" << MYARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << myArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests insertion sort on a vector. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	vArray - randomized vector array
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes vArray to be sorted using InsertionSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_IS_vArray(vector<int> vArray, int n, ofstream& fout)
{
	clock_t start = clock();
	InsertionSort(vArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(VARRAY, elapsed);

	fout << VARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << vArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests insertion sort on a native integer array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	cArray - randomized array of integers, passed by pointer
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes cArray to be sorted calling InsertionSort(),
*	and outputs the results to fout and console. Must reset array to original 
*	randomized values before calling another sort function.	
**********************************************************************************/
void Test_IS_cArray(int* cArray, int n, ofstream& fout)
{
	clock_t start = clock();
	InsertionSort(cArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(CARRAY, elapsed);

	fout << CARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << cArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests the shell sort on all 3 array types 
* Precondition:
*	sort - SortObj struct that has the three arrays and number of elements in each
* Postcondition:
*   Calls the shell sort test for each array type and sorts each type
**********************************************************************************/
void Test_ShellSort(SortObj sort)
{
	const char * sortname = "[ = Shell Sort = ]";
	ofstream fout("data.txt", std::ios_base::app);	//open file for appending
	fout << sortname;
	cout << sortname << endl;

	Test_SHLS_myArray(sort.my_array, sort.elements, fout);
	Test_SHLS_vArray(sort.v_array, sort.elements, fout);
	Test_SHLS_cArray(sort.c_array_to_sort, sort.elements, fout);
	fout << "\n";

	fout.close();
}

/*********************************************************************************
* Purpose:
*	This function tests shell sort on my array class. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	myArray - randomized array of type Array<int> 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes myArray to be sorted calling ShellSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_SHLS_myArray(Array<int> myArray, int n, ofstream& fout)
{
	clock_t start = clock();
	ShellSort(myArray, n);
	clock_t stop = clock();

	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(MYARRAY, elapsed);

	fout << "\n" << MYARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << myArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests shell sort on the vector. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	vArray - randomized vector array 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes vArray to be sorted calling ShellSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_SHLS_vArray(vector<int> vArray, int n, ofstream& fout)
{
	clock_t start = clock();
	ShellSort(vArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(VARRAY, elapsed);

	fout << VARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << vArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests shell sort on an integer array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	cArray - randomized array of integers, passed by pointer
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes cArray to be sorted calling ShellSort(),
*	and outputs the results to fout and console. Must reset array to original 
*	randomized values before calling another short
**********************************************************************************/
void Test_SHLS_cArray(int* cArray, int n, ofstream& fout)
{
	clock_t start = clock();
	ShellSort(cArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(CARRAY, elapsed);

	fout << CARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << cArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function drives the heap sort tests on 3 different array types 
* Precondition:
*	sort - SortObj struct that has the three arrays and number of elements in each
* Postcondition:
*   Calls the heap sort test for each array type and sorts
**********************************************************************************/
void Test_HeapSort(SortObj sort)
{
	const char * sortname = "[ = Heap Sort = ]";
	ofstream fout("data.txt", std::ios_base::app);	//open file for appending
	fout << sortname;
	cout << sortname << endl;

	Test_HS_myArray(sort.my_array, sort.elements, fout);
	Test_HS_vArray(sort.v_array, sort.elements, fout);
	Test_HS_cArray(sort.c_array_to_sort, sort.elements, fout);
	fout << "\n";

	fout.close();
}

/*********************************************************************************
* Purpose:
*	This function tests the heap sort on my array class. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	myArray - randomized array of type Array<int> 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes myArray to be sorted calling HeapSort(),
*	and outputs the results to fout and console.
***********************************************************************************/
void Test_HS_myArray(Array<int> myArray, int n, ofstream& fout)
{
	clock_t start = clock();
	HeapSort(myArray, n);
	clock_t stop = clock();

	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(MYARRAY, elapsed);

	fout << "\n" << MYARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << myArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests heap sort on the vector array class. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	vArray - randomized vector array
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes vArray to be sorted calling HeapSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_HS_vArray(vector<int> vArray, int n, ofstream& fout)
{
	clock_t start = clock();
	HeapSort(vArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(VARRAY, elapsed);

	fout << VARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << vArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests heap sort on native integer array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	cArray - randomized array of integers, passed by pointer
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes cArray to be sorted calling HeapSort(),
*	and outputs the results to fout and console. Must reset array to original 
*	randomized values before calling another sort.
**********************************************************************************/
void Test_HS_cArray(int* cArray, int n, ofstream& fout)
{
	clock_t start = clock();
	HeapSort(cArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(CARRAY, elapsed);

	fout << CARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << cArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests the merge sort on all 3 array types. 
* Precondition:
*	sort - SortObj struct that has the three arrays and number of elements in each
* Postcondition:
*   Calls the merge sort test for each array type and sorts
**********************************************************************************/
void Test_MergeSort(SortObj sort)
{
	const char * sortname = "[ = Merge Sort = ]";
	ofstream fout("data.txt", std::ios_base::app);	//open file for appending
	fout << sortname;
	cout << sortname << endl;

	Test_MS_myArray(sort.my_array, sort.elements, fout);
	Test_MS_vArray(sort.v_array, sort.elements, fout);
	Test_MS_cArray(sort.c_array_to_sort, sort.elements, fout);
	fout << "\n";

	fout.close();
}

/*********************************************************************************
* Purpose:
*	This function tests merge sort on my array class. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	myArray - randomized array of type Array<int> 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes myArray to be sorted calling MergeSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_MS_myArray(Array<int> myArray, int n, ofstream& fout)
{
	clock_t start = clock();
	MergeSort(myArray, n);
	clock_t stop = clock();

	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(MYARRAY, elapsed);

	fout << "\n" << MYARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << myArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests merge sort on the vector array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	vArray - randomized vector array
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes vArray to be sorted calling MergeSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_MS_vArray(vector<int> vArray, int n, ofstream& fout)
{
	clock_t start = clock();
	MergeSort(vArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(VARRAY, elapsed);

	fout << VARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << vArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests selection sort on native integer array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	cArray - randomized array of integers
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes cArray to be sorted MergeSort(),
*	and outputs the results to fout and console. Must reset the values to original
*	randomized values before calling another sort.
**********************************************************************************/
void Test_MS_cArray(int* cArray, int n, ofstream& fout)
{
	clock_t start = clock();
	MergeSort(cArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(CARRAY, elapsed);

	fout << CARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << cArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests quick sort on 3 array types
* Precondition:
*	sort - SortObj struct that has the three arrays and number of elements in each
* Postcondition:
*   Calls the quick sort test for each array type and sorts
**********************************************************************************/
void Test_QuickSort(SortObj sort)
{
	const char * sortname = "[ = Quick Sort = ]";
	ofstream fout("data.txt", std::ios_base::app);	//open file for appending
	fout << sortname;
	cout << sortname << endl;

	Test_QS_myArray(sort.my_array, sort.elements, fout);
	Test_QS_vArray(sort.v_array, sort.elements, fout);
	Test_QS_cArray(sort.c_array_to_sort, sort.elements, fout);
	fout << "\n";

	fout.close();
}

/*********************************************************************************
* Purpose:
*	This function tests quick sort on my array class. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	myArray - randomized array of type Array<int> 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes myArray to be sorted calling QuickSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_QS_myArray(Array<int> myArray, int n, ofstream& fout)
{
	clock_t start = clock();
	QuickSort(myArray, n);
	clock_t stop = clock();

	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(MYARRAY, elapsed);

	fout << "\n" << MYARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << myArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests quick sort on the vector array class. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*	vArray - randomized vector array 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes vArray to be sorted calling QuickSort(),
*	and outputs the results to fout and console.
**********************************************************************************/
void Test_QS_vArray(vector<int> vArray, int n, ofstream& fout)
{
	clock_t start = clock();
	QuickSort(vArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(VARRAY, elapsed);

	fout << VARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << vArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}

/*********************************************************************************
* Purpose:
*	This function tests quick sort on an integer array. It outputs
*	to data.txt every nth element in array depending on ELEMPEEK, and outputs
*	to console the name of array and duration it took to sort.
* Precondition:
*   cArray - randomized vector array 
*	n - number of elements in the array
*	fout - output file to data.txt, in append mode 
* Postcondition:
*	changes cArray to be sorted calling QuickSort(),
*	and outputs the results to fout and console. Must reset the values to original
*	randomized values before calling another sort.
**********************************************************************************/
void Test_QS_cArray(int* cArray, int n, ofstream& fout)
{
	clock_t start = clock();
	QuickSort(cArray, n);
	clock_t stop = clock();

	//determine duration
	double elapsed = static_cast<double>(stop - start) * 1 / CLOCKS_PER_SEC;
	DisplaySortTime(CARRAY, elapsed);

	fout << CARRAY << ": ";
	for (int i = 0; i < n; i += ELEMPEEK)
	{
		fout << cArray[i] << " ";
	}
	fout << ": " << elapsed << " sec\n";
}
