#include "cases.c"
#include <string.h>

// Bubble sort algorithm:
// It says, compare 2 adjacent elements. 
// Bring the larger value to the right.
// Always, either of the values is the largest in the array.

void bsort(int size, int* arr) {
	int comp = 0;
	int swap = 0; 
	printf("Initial Input: ");
	printarr(size, arr);
	printf("\n");

	// If size is 0 or 1, then no point of doing any comparisions.
	for (int i = size - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			comp++;
			if (arr[j] > arr[j + 1]) {
				swapint(j, j + 1, arr);
				swap++;
			}
		}

		printf("After pass %d: ", size - i - 1);
		printarr(size, arr);
		printf("\n");
	}

	printf("Final Output: ");
	printarr(size, arr);
	printf("\n");
	printf("Bubble Sort:\nComparisions: %d\nSwaps: %d\n", comp, swap);
	printf("\n\n\n");
}


void ssort(int size, int* arr) {
	int comp = 0;
	int swap = 0; 
	int min;
	printf("Initial Input: ");
	printarr(size, arr);
	printf("\n");

	// If size is 0 or 1, then no point of doing any comparisions.
	for (int i = 0; i < size - 1; i++) {
		min = i;
		for (int j = i + 1; j < size; j++) {
			comp++;
			if (arr[j] < arr[min]) {
				min = j;
			}
		}

		if (i != min) {
			swapint(i, min, arr);
			swap++;
		}

		printf("After pass %d: ", i);
		printarr(size, arr);
		printf("\n");
	}

	printf("Final Output: ");
	printarr(size, arr);
	printf("\n");
	printf("Selection Sort:\nComparisions: %d\nSwaps: %d\n", comp, swap);

	printf("\n\n\n");
}

int main() {
	int test2[N_CASES][7];

	for (int i = 0; i < N_CASES; i++)
		memcpy(test2[i], tests[i], sizeof(tests[i]));
		
	for (int i = 0; i < N_CASES; i++) {
		bsort(sizes[i], tests[i]);
		ssort(sizes[i], test2[i]);
	}
}
