#include "cases.c"
	
// Insertion sort premature exit algorithm.
// Select KEY element and insert it in sorted portion.
// Taking 2 parts of array: one sorted, another unsorted.

void insert(int val, int idx, int* arr, int last) {
	for (int i = last - 1; i >= idx; i--) {
		arr[i + 1] = arr[i];
	}
	arr[idx] = val;
}

void isort(int size, int* arr) {
	printf("Initial Input: ");
	printarr(size, arr);
	printf("\n");

	int key, sidx;
	
	// If size is 0 or 1, then no point of doing any comparisions.
	for (int i = 1; i < size; i++) {
		if (sorted(arr, size, i - 1)) {
			printf("ARRAY IS ALREADY SORTED. EXITING...\n");
			break;
		}
		
		key = sidx = i;
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[key]) {
				sidx = j;
				break;
			}
		}

		insert(arr[key], sidx, arr, key);
		printf("After pass %d: ", i);
		printarr(size, arr);
		printf("\n");
	}

	printf("Final Output: ");
	printarr(size, arr);
	printf("\n");
	printf("\n\n\n");
}

#ifndef __main__
int main() {
	for (int i = 0; i < N_CASES; i++) {
		isort(sizes[i], tests[i]);
	}
}

#endif
