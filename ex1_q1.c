// Course: Advanced C programming
// exercise 1, question 1
// file name: ex1_q1.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------- //
//


//
// --------------------------- //

// function declarations section:
int* scanArray(int*);
void printArray(int*, int);
int arrangeArray(int**, int);

// --------------------------- //

// main section:
// DO NOT CHANGE the following function:
int main()
{
	int* arr, n, k;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	arr = scanArray(&n);
	k = arrangeArray(&arr, n);

	// write output:
	printf("Output:\n");
	printf("Size of k: %d\n", k);
	printf("Sorted array:\n");
	printArray(arr, n);
	free(arr);

	return 0;
}
// --------------------------- //


// DO NOT CHANGE the following function:
int* scanArray(int* n)
{
	int i;
	int* arr;

	printf("Enter array size: ");
	scanf("%d", n);

	arr = (int*)malloc(sizeof(int) * (*n));
	for (i = 0; i < *n; ++i)
	{
		printf("Enter value #%d: ", i + 1);
		scanf("%d", arr + i);
	}

	return arr;
}
// --------------------------- //


// DO NOT CHANGE the following function:
void printArray(int* arr, int n)
{
	int i;
	printf("{");
	for (i = 0; i < n; ++i)
		printf("%d%s", arr[i], i == n - 1 ? "" : ", ");
	printf("}\n");
}
// --------------------------- //

/// <summary>
/// Combine the two groups using realloc and memcpy only. 
/// </summary>
/// <param>int **arr - Address of the array pointer</param>
/// <param>int n - Size of the array</param>
/// <returns>Size of the first group</returns>
int arrangeArray(int** arr, int n)
{
	//your code:
	int i, k;
	//loop that checks amount of numbers in first increasing series
	for (i = 0; i < n; i++)
	{
		if ((*arr)[i] > (*arr)[i + 1])
		{
			k = i + 1;
			break;
		}
	}
	//reallocating extra memory->n-k extra places besides n places we had->total: 2*n-k places overall
	*arr = (int*)realloc(*arr, sizeof(int) * (2 * n - k));

	if (*arr)
	{
		//move all n elements (n-k) places right ,to the end of the new allocated array
		memcpy(*arr + n - k, *arr, sizeof(int) * n);
		//move back to the front the secont series of n-k elements that are smaller
		memcpy(*arr, *arr + n, sizeof(int) * (n - k));
	}
	else
	{
		printf("No memory allocation space!\n");
		return 0;
	}

	return k;
}
// --------------------------- //
