/* Test Cases by ChatGPT */
/* Unit testing with colors + emojis + failed case numbers */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ---------- ANSI COLORS ---------- */
#define GREEN  "\033[1;32m"
#define RED    "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET  "\033[0m"

/* ---------- TEST DATA ---------- */
int tests[][7] = {
    { },                            /* 0: empty */
    { 1 },                          /* 1: single */
    { 2, 1 },                       /* 2: two unsorted */
    { 1, 2 },                       /* 3: two sorted */
    { 1, 2, 3, 4, 5 },              /* 4: sorted */
    { 5, 4, 3, 2, 1 },              /* 5: reverse */
    { 3, 1, 4, 1, 5 },              /* 6: duplicates */
    { 2, 2, 2, 2 },                 /* 7: all equal */
    { 0, -1, 5, -10 },              /* 8: mixed sign */
    { -5, -1, -3, -2 },             /* 9: all negative */
    { INT_MAX, 0, INT_MIN },        /* 10: extreme */
    { 1, 2, 3, 5, 4 },               /* 11: nearly sorted */
    { 1, 2, 1, 2, 1, 2 },            /* 12: repeating */
    { 6, 5, 4, 3, 2, 1, 0 }  ,        /* 13: large reverse */
    {10, 80, 30, 90, 40}
};

int sizes[] = {
    0, 1, 2, 2, 5, 5, 5,
    4, 4, 4, 3, 5, 6, 7, 5
};

#define NUM_TESTS (sizeof(sizes) / sizeof(sizes[0]))

/* ---------- HELPERS ---------- */
int is_sorted(int *a, int n) {
    for (int i = 0; i + 1 < n; i++)
        if (a[i] > a[i + 1])
            return 0;
    return 1;
}

/* ---------- TEST HARNESS ---------- */
void TEST(void (*f)(int *, int)) {
    int failed_indices[NUM_TESTS];
    int failed_count = 0;

    printf(YELLOW "🔍 Running sorting tests...\n\n" RESET);

    for (unsigned int t = 0; t < NUM_TESTS; t++) {
        int n = sizes[t];
        int *a = (n > 0) ? (int*) malloc(n * sizeof(int)) : NULL;

        for (int i = 0; i < n; i++)
            a[i] = tests[t][i];

        f(a, n);

        if (is_sorted(a, n)) {
            printf(GREEN "✅ Test %02d passed\n" RESET, t);
        } else {
            printf(RED   "❌ Test %02d FAILED\n" RESET, t);
            failed_indices[failed_count++] = t;
        }

        free(a);
    }

    printf("\n");
    if (failed_count == 0) {
        printf(GREEN "🎉 All test cases passed :)\n" RESET);
    } else {
        printf(RED "🚨 Failed! Cases: " RESET);
        for (int i = 0; i < failed_count; i++) {
            printf("%d", failed_indices[i]);
            if (i + 1 < failed_count) printf(", ");
        }
        printf("\n");
    }
}

/*
 * Usage:
 *
 * void sort(int *a, int n);
 *
 * int main() {
 *     TEST(sort);
 * }
 */

void swap(int *array, int fidx, int sidx) {
	int temp = array[fidx];
	array[fidx] = array[sidx];
	array[sidx] = temp;
}


void bubble_sort(int *arr, int n) {
	// bool swapped = false;
	
	for (int i = n-1; i > 0; i--)
	    for (int j= 0; j < i; j++) 
	        if (arr[j] > arr[j+1]) 
	            swap(arr, j, j+1);
}

void lomuto_partition (int *arr, int low, int high) {
	printf("From %d to %d\n", low, high);
	if (low >= high) return;
	
	int p = high;
	int f = low;
	for (int i = low; i < high; i++) {
		if (arr[i] < arr[p]) {
		    swap(arr, i, f);
		    f++;
		}
	}
	swap(arr, f,p);
	lomuto_partition(arr, low, f - 1);
	lomuto_partition(arr, f + 1, high);
}

void quicksort(int *arr, int n) {
	lomuto_partition(arr, 0, n-1);
}


void printarr(int size, int* arr, _Bool newl) {

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
	if (newl) puts("");
}

void printsubarr(int* arr, int low, int high, _Bool newl) {

	if (low > high) {
		printf("[< empty >]");
		return;
	}
		
	printf("[");
	for (int i = low; i < high; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d]", arr[high]);
	if (newl) puts("");
}


void merge(int *arr, int *part_l, int *part_r, int low, int high, int lsize, int rsize) {
	printarr(lsize, part_l, 0);
	printarr(rsize, part_r, 1);
	printf("Called: MERGE l: %d, h:%d, ls:%d, rs:%d\n", low, high, lsize, rsize);

	
	int l = 0, r = 0;
	for (int i = low; i <= high; i++) {
		if (l == lsize)
			for (; i <= high; i++) 
				arr[i] = part_r[r++];

		if (r == rsize)
			for (; i <= high; i++) 
				arr[i] = part_l[l++];

		if (part_l[l] < part_r[r])
			arr[i] = part_l[l++];
		else
			arr[i] = part_r[r++];
	}

	printf("After Merge:");
	printsubarr(arr, low, high, 1);

	
}

void split(int *arr, int low, int high) {
	printf("Called: SPLIT l: %d, h:%d\n", low, high);
	if (low >= high) return;
	printf("ARRAY IS: ");
	printarr(sizeof(arr) / sizeof(int), arr, 1);
	int *part_l, *part_r;
	int n = high - low + 1;
	printarr(n, arr, 1);
	if (n % 2 == 0) {
		part_l = malloc(sizeof(int) * n / 2);
		part_r = malloc(sizeof(int) * n / 2);
		printf("%d\n", n);
		for (int i = 0; i < n/2; i++) {
			part_l[i] = arr[i + low];
			part_r[i] = arr[n/2 + i + low];
		}

		printf("Parts ARE:");
		printarr(n/2, part_l, 0);
		printarr(n/2, part_r, 1);
		split(part_l, low, n/2 - 1 + low);
		split(part_r, n/2 + low, high);
		merge(arr, part_l, part_r, low, high, n/2, n/2);
		
	} else {
		part_l = malloc(sizeof(int) * (n + 1) / 2);
		part_r = malloc(sizeof(int) * (n - 1) / 2);

		for (int i = 0; i < n/2; i++) {
			part_l[i] = arr[i + low];
			part_r[i] = arr[n/2 + 1 + i + low];
		}
		part_l[n/2] = arr[low + n/2];	

		split(part_l, low, n/2 + low);
		split(part_r, n/2 + low + 1, high);
		merge(arr, part_l, part_r, low, high, (n + 1)/2, (n - 1)/2);

	}

}

void mergesort(int *arr, int n) {
	split(arr, 0, n-1);
	printf("Finally: ");
	printarr(n, arr, 1);
}


int main()
{
	//TEST(bubble_sort);
	//TEST(quicksort);
	TEST(mergesort);
}
