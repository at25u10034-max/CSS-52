#include <stdio.h>
#include <stdlib.h>

#include "../../DataStructures/include/deque.h"

int maxof(Deque* q) {
	int max = front(q);
	for (int i = 1; i < size(q); i++) {
		if (at(q, i) > max) max = at(q, i);
	}

	return max;
}

int *window(int *arr, int size, int k) {
	int *out = malloc ((size - k + 1) * sizeof(int));
	int oidx = 0;
	Deque dq = createdeque(k, UNRESTRICTED);
	
	printf("VALUES: k= %d, size=%d\n", k, size);
	for (int i = 0; i < k; i++) enqueue_rear(&dq, arr[i]);

	int max = maxof(&dq);
	int var;
	out[oidx++] = max;
	showdeque(&dq);
	
	for (int i = k; i < size; i++) {
		var = dequeue_front(&dq);
		enqueue_rear(&dq, arr[i]);

		if (var == max) max = maxof(&dq);
		if (arr[i] > max) max = arr[i];

		showdeque(&dq);
		printf("MAX: %d\n", max);
		out[oidx++] = max;
	}

	return out;
}


/* ---------- helper functions ---------- */

int* expected_max(int *arr, int n, int k) {
    int out_size = n - k + 1;
    int *res = malloc(sizeof(int) * out_size);

    for (int i = 0; i < out_size; i++) {
        int max = arr[i];
        for (int j = i; j < i + k; j++) {
            if (arr[j] > max)
                max = arr[j];
        }
        res[i] = max;
    }

    return res;
}

int compare(int *a, int *b, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

void print_array(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n-1) printf(", ");
    }
    printf("]");
}

/* ---------- test runner ---------- */

void run_test(int *arr, int n, int k) {
	int out_size = n - k + 1;

	printf("\nArray = ");
    print_array(arr, n);
    printf(", k = %d\n", k);
    int *expected = expected_max(arr, n, k);
    int *result = window(arr, n , k);

    printf("\nArray = ");
    print_array(arr, n);
    printf(", k = %d\n", k);

    printf("Expected: ");
    print_array(expected, out_size);
    printf("\n");

    printf("Result:   ");
    print_array(result, out_size);
    printf("\n");

    if (compare(expected, result, out_size))
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");

    free(expected);
}

/* ---------- main ---------- */

int main() {

    int a2[] = {4,2,12,3};
    run_test(a2, 4, 2);

    int a3[] = {9,8,7,6};
    run_test(a3, 4, 1);

    int a4[] = {1,1,1,1};
    run_test(a4, 4, 3);

    int a5[] = {10};
    run_test(a5, 1, 1);

    int g1[] = {1,3,-1,-3,5,3,6,7};
    run_test(g1, 8, 3);

	int g2[] = {4,2,12,3,8};
    run_test(g2, 5, 2);

	int g3[] = {9,10,9,-7,-4,-8,2,-6};
    run_test(g3, 8, 5);

    return 0;
}
