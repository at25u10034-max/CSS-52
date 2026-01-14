#include "cases.c"

typedef int Comparator(void*, void*);

// Bubble sort algorithm:
// It says, compare 2 adjacent elements. 
// Bring the larger value to the right.
// Always, either of the values is the largest in the array.

void bsort(size_t size, void** arr, Comparator *comp) {
	// If size is 0 or 1, then no point of doing any comparisions.
	for (int i = size - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			if (comp(arr[j], arr[j + 1]) > 0) {
				swap(j, j + 1, arr);
			}
		}

	}
}

