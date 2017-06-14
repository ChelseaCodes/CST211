/*************************************************************
* Author:		Chelsea Christison
* Filename:		sorts.h
* Date Created:	4.18.2017
*
* Modifications:
*	4.20 - added easy sorts
*	4.23 - commenting
* *****
* Purpose: 
*	This templated file contains seven sorts, and a Swap function
*	for swapping elements in an array. 
*	The seven sorts are: 
*		- Brute Force Bubble Sort
*		- Flagged Bubble Sort
*		- Selection Sort
*		- Insertion Sort
*		- Shell Sort 
*		- Heap Sort
*		- Merge Sort
*		- Quick Sort
*
*************************************************************************/
#ifndef SORTS_H
#define SORTS_H
#include <vector>
#include <iterator>
using std::vector; 

/*********************************************************************************
* Purpose:
*	This function swaps two elements in an array
*	
* Precondition: 
*	array - filled array, passed by reference 
*	elem1 - first element to swap in array 
*	elem2 - second element to swap in array
*	
* Postcondition: 
*	Modifies the array by swapping the two elements. No returns
*	 
**********************************************************************************/
template <typename T>
void Swap(T& array, int elem1, int elem2)
{
	int temp = array[elem1]; 
	array[elem1] = array[elem2];
	array[elem2] = temp; 
}

/*********************************************************************************
* Purpose:
*	This function uses brute force bubble sorting algorithm to sort the array
*	given. 
*	
* Precondition: 
*	array - filled array, passed by reference 
*	n -		number of elements in the array
* Postcondition: 
*	Modifies the array by implementing the brute force algorithm. Array is sorted
* 
**********************************************************************************/
template <typename T>
void BruteForceBubbleSort(T& array, int n)
{
	//begin the logical end of array at last element
	int logical_end = n; ;

	//driving loop. iterate through array num times 
	for(int iterations = 0; iterations < n; iterations++, logical_end--)
	{
		//loop through the inside of the array till the logical end. j looks at the second elem first
		for(int j = 1; j < logical_end; j++)
		{
			//if first elem is > than elem after
			if(array[j - 1] > array[j])
			{
				Swap(array, j, j - 1);
			}
		}
	}
}

/*********************************************************************************
* Purpose:
*	This function uses flagged bubble sorting algorithm to sort the array 
* Precondition: 
*	array - filled array, passed by reference 
*	n -		number of elements in the array
* Postcondition: 
*	Modifies the array by implementing the flagged bubble sort algorithm
*	Array is sorted. 
**********************************************************************************/
template <typename T>
void FlaggedBubbleSort(T& array, int n)
{
	//begin the logical end of array at last element
	int logical_end = n;
	bool swapped = false;

	for (int iterations = 0; iterations < n && !swapped; iterations++)
	{
		swapped = true;	//flag to true
		for (int j = 0; j < logical_end - iterations - 1; j++)
		{
			if (array[j + 1] > array[j])
			{
				Swap(array, j, j +1);
				swapped = false; //set to false
			}
		}
	}
}

/*********************************************************************************
* Purpose:
*	This function implements Selection sort algorithm to sort the array.
* Precondition: 
*	array - filled array, passed by reference 
*	n -		number of elements in the array
* Postcondition: 
*	Modifies the array by implementing the selection sort algorithm
*	Array is sorted. *	
**********************************************************************************/
template<typename  T>
void SelectionSort(T & array, int n)
{
	int logical_end = n - 1;
	int j = 0;

	//loop until the logical end of the array
	for(int i = 0; i < n; i++, logical_end--)
	{
		int largest_index = 0;		//index of the largest value in array

		//loop until finding the largest value in the array
		for(j = 0 , largest_index = 0; j <= logical_end ; j++)
		{
			//if larger value is found, reset the largest index
			if(array[j] > array[largest_index])
				largest_index = j; 			
		}
		Swap(array, largest_index, logical_end);
	}
}

/*********************************************************************************
* Purpose:
*	This function implements the insertion sort algorithm to sort the array
* Precondition: 
*	array - filled array, passed by reference 
*	n -		number of elements in the array
* Postcondition: 
*	Modifies the array by implementing the insertion sort algorithm
*	Array is sorted. 
**********************************************************************************/
template <typename T>
void InsertionSort(T& array, int n)
{
	int j = 0; 

	for (int i = 1; i < n; i++)
	{
		int temp = array[i];
		j = i; 
		while(j > 0 && temp <array[j - 1])
		{
			array[j] = array[j - 1];
			j--;
		}
		array[j] = temp;
	}
}

/*********************************************************************************
* Purpose:
*	This function implements the shell sort algorithm 
* Precondition: 
*	array - filled array, passed by reference 
*	n -		number of elements in the array
* Postcondition: 
*	Modifies the array by implementing shell sort until sorted
**********************************************************************************/
template<typename T>
void ShellSort(T& array, int n)
{
	//create the gaps
	vector<int>gaps;

	for (int i = 0, h = 1; h < n; i++)
	{
		gaps.push_back(h);
		h = 3 * h + 1;
	}

	for(int rev = gaps.size() - 1; rev >= 0; rev--)
	{
		int gap_size = gaps[rev];	//grab the gap size

		for (int i = gap_size; i < n; i++)
		{
			int temp = array[i];
			int j = i;
			while (j > gap_size && temp < array[j - gap_size])
			{
				array[j] = array[j - gap_size];
				j -= gap_size;
			}
			array[j] = temp;
		}
	}
	
	//loops starting at the largest gap 
	//for (auto rev = gaps.rbegin() ; rev != gaps.rend(); ++rev)
	//{
	//	int gap_size = *rev;	//grab the gap size

	//	for(int i = gap_size; i < n; i++)
	//	{
	//		int temp = array[i]; 
	//		int j = i; 
	//		while (j >= gap_size && temp < array[j - gap_size])
	//		{
	//			array[j] = array[j - gap_size]; 
	//			j -= gap_size;		
	//		}
	//		array[j] = temp; 
	//	}
	//}
}

/*********************************************************************************
* Purpose:
*	This function implements the heap sort to a randomized array. It calls the 
*	function "Heapify" to first build the heap before sorting. 
* Precondition: 
*	array - filled array, passed by reference 
*	n -		number of elements in the array
* Postcondition: 
*	Modifies the array by implementing heap sort until sorted
**********************************************************************************/
template <typename T>
void HeapSort(T& array, int n)
{
	int first = (n / 2) - 1;

	int logical_end = n - 1;

	for(int i = first; i >= 0; i--)
	{
		Heapify(array, i, logical_end);
	}
	
	for(int i = logical_end; i != 0; i--)
	{
		Swap(array, 0, i); 
		Heapify(array, 0, i - 1); 
	}
}

/*********************************************************************************
* Purpose:
*	This function implements the second part of the heap sort algorithm: building
*	a heap from the array. 
* Precondition:
*	array - filled array, passed by reference
*	first - parent that is the top of the heap
*	lastIndex - integer to mark the end of the array
* Postcondition:
*	Modifies the array by creating a heap
**********************************************************************************/
template<typename T>
void Heapify(T& array, int first, int lastIndex)
{
	int parent = first;
	int left_child = 2 * parent + 1;
	int temp = array[parent];

	while (left_child <= lastIndex)
	{
		if (left_child < lastIndex && array[left_child] < array[left_child + 1]) //less than right child
			left_child++;

		if (temp < array[left_child])
		{
			array[parent] = array[left_child];
			array[left_child] = temp; 

			parent = left_child;
			left_child = parent * 2 + 1;
		}
		else
			left_child = lastIndex + 1; 
	}
}

/*********************************************************************************
* Purpose:
*	This function makes a copy of the array passed to call MergeSort(4 params)
* Precondition: 
*	array - filled array, passed by reference 
*	n -		number of elements in the array
* Postcondition: 
*	Modifies the array by implementing Merge sort. 
**********************************************************************************/
template <typename T> 
void MergeSort(T& array, int n)
{
	//create a temporary array that is the size of the original array
	T ra_copy = array; 
	MergeSort(array, ra_copy, 0, n - 1);
}

/*********************************************************************************
* Purpose:
*	This function makes a copy of an array that is passed by pointer , then 
*	calls MergeSort(4 params). deletes the copied array after sort
* Precondition:
*	array - filled array, passed by pointer
*	n -		number of elements in the array
* Postcondition:
*	Modifies the array by implementing merge sort
**********************************************************************************/
template <typename T>
void MergeSort( T * array, int n)
{
	T * ra_copy = new int[n];	//create new array of size n 

	//copy all information over
	for(int i =0; i < n; i++)
	{
		ra_copy[i] = array[i]; 
	}
	MergeSort(array, ra_copy, 0, n - 1);

	delete[] ra_copy; 
}

/*********************************************************************************
* Purpose:
*	This function takes the array and recursively calls itself to create 
*	smaller arrays before sorting and merging together
* Precondition:
*	array - filled array, passed by ref
*	copy -  copy of array, passed by ref
*	left_index - represents the left most element in array
*	right - represents the right most element in array 
* Postcondition:
*	Modifies the array by implementing merge sort. recursively calls itself to 
*	establish smaller logical arrays. 
**********************************************************************************/
template <typename T>
void MergeSort(T& array, T& copy, int left_index, int right)
{
	int mid = 0; 
	if (left_index < right)
	{
		mid = (left_index + right) / 2;

		MergeSort(array, copy, left_index, mid);
		MergeSort(array, copy, mid + 1, right);
		Merge(array, copy, left_index, mid, right);
	}
}

/*********************************************************************************
* Purpose:
*	This function implements the merging of arrays in the merge sort algorithm. 
* Precondition:
*	array - filled array, passed by reference
*	copy -	copy of array, used to hold sorted array 
*	left_index - left most element in array 
*	mid - midpoint between left and right, separator
*	right_end - right most element in array 
* Postcondition:
*	Modifies the array by merging the left and right array into a sorted copy
**********************************************************************************/
template <typename T>
void Merge(T& array, T& copy, int left_index, int mid, int right_end)
{
	int left = left_index;	
	int right = mid + 1;
	int temp_pos = left_index; 

	 while(left <= mid  && right <= right_end)
	 {
		 if(array[left] <= array[right])
			 copy[temp_pos] = array[left++]; 
		 else
			 copy[temp_pos] = array[right++]; 

		 temp_pos++; 
	 }

	//which portion of array to copy back 
	 if(left > mid)
	 {
		 //copy contents of right array into temp 
		 for (int r = right; r <= right_end; r++)
			 copy[temp_pos++] = array[r];
	 }
	 else
	 {
		 //copy contents of left array into temp`
		 for (int l = left; l <= mid; l++)
			 copy[temp_pos++] = array[l];
	 }
	
	for (int i = left_index; i <= right_end; i++)
		array[i] = copy[i]; 

}

/*********************************************************************************
* Purpose:
*	This function find the maximum value in given array and places at the end of
*	the array. This is the first part of the quick sort algorithm. Calls Quick
*	Sort to sort the rest of the array. 
* Precondition:
*	array - filled array, passed by reference
*	n -		number of elements in the array
* Postcondition:
*	Modifies array by implementing QuickSort to sort. 
**********************************************************************************/
template <typename  T>
void QuickSort(T& array, int n)
{
	int max = 0; 
	//find largest value 
	for (int i = 1; i < n; i++)
	{
		if (array[max] < array[i])
			max = i; 
	}
	Swap(array, max, n - 1); 
	QuickSort(array, 0, n - 2); 
}

/*********************************************************************************
* Purpose:
*	This function implements sorting the array passed using the quick sort 
*	algorithm. After placing an element in its position, function calls 
*	QuickSort once again, without the element that it placed.
* Precondition:
*	array - filled array, passed by reference
*	first - first element in the array
*	last - last element in the array
* Postcondition:
*	Modifies array by implementing QuickSort to sort. 
**********************************************************************************/
template <typename T>
void QuickSort(T& array, int first, int last)
{
	int small = first + 1;
	int large = last; 
	int pivot = array[first]; 

	while(small <= large)
	{
		while (array[small] <= pivot)
			small++;
		while (array[large] > pivot)
			large--;

		if (small < large)
			Swap(array, small++, large--);
		else
			small++;
	}	

	Swap(array, large, first); 

	if (first < large - 1)
		QuickSort(array, first, large - 1); 
	if (last > large + 1)
		QuickSort(array, large + 1, last); 

}
#endif