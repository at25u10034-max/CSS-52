/* Test Cases by ChatGPT */

#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

#define N_CASES 22

/*
 * Comprehensive minimal 2D test matrix.
 * Each row is a test case.
 * Only the first `sizes[i]` elements of each row are valid.
 */
int tests[][7] = {
    { },                            /* empty array */
    { 1 },                          /* single element */
    { 2, 1 },                       /* two elements unsorted */
    { 1, 2 },                       /* two elements sorted */
    { 1, 2, 3, 4, 5 },              /* already sorted */
    { 5, 4, 3, 2, 1 },              /* reverse sorted */
    { 3, 1, 4, 1, 5 },              /* random with duplicates */
    { 2, 2, 2, 2 },                 /* all equal elements */
    { 0, -1, 5, -10 },              /* mixed positive and negative */
    { -5, -1, -3, -2 },             /* all negative */
    { INT_MAX, 0, INT_MIN },        /* extreme integer values */
    { 1, 2, 3, 5, 4 },               /* nearly sorted */
    { 1, 3, 2, 4, 5 },               /* small local inversion */
    { 1, 2, 1, 2, 1, 2 },            /* repeating pattern */
    { 9, 9, 9, 2, 3 },               /* large identical prefix */
    { 5, 1, 5, 1, 5, 1 },            /* alternating duplicates */
    { 7, 7, 3, 7, 7 },               /* single distinct in duplicates */
    { 4, 1, 3, 9, 7, 2 },             /* typical random */
    { 2, 0, 1, 0, 2, 0 },             /* few distinct keys */
    { 6, 5, 4, 3, 2, 1, 0 },           /* larger reverse sorted */


    // Lab Sample cases
    { 64, 34, 25, 12, 22 },
    { 5, 1, 4, 2, 8 }
};

/* logical sizes of each test case */
int sizes[] = {
    0,  /* empty */
    1,  /* single */
    2,  /* two unsorted */
    2,  /* two sorted */
    5,  /* sorted */
    5,  /* reverse */
    5,  /* random duplicates */
    4,  /* all equal */
    4,  /* mixed sign */
    4,  /* all negative */
    3,  /* extreme values */
    5,  /* nearly sorted */
    5,  /* local inversion */
    6,  /* repeating pattern */
    5,  /* identical prefix */
    6,  /* alternating duplicates */
    5,  /* single distinct */
    6,  /* random */
    6,  /* few distinct */
    7,  /* larger reverse */
    5,
    5
};


void printarr(int size, int* arr) {

	if (size == 0) {
		printf("[< empty >]");
		return;
	}
		
	printf("[");
	int i;
	for (i = 0; i < size - 1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d]", arr[i]);
}

void swapint(int i, int j, int *arr) {
	int t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}

void swap(int i, int j, void **arr) {
	void* t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}


bool sorted(int *arr, int size, int start) {
	for (int i = start; i < size - 1; i++) {
		if (arr[i] > arr[i + 1])
			return false;
	}
	return true;
}
