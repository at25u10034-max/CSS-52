#include <stdio.h>
#include <stdlib.h>

// HELPERS
void printarr(int* arr, int size) {
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


void swap(int *arr, int i, int j) {
	int t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}


void heapify_c(int *heap, int n, int i) {
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	int max = i;
	if (l < n && heap[l] > heap[i]) max = l;
	if (r < n && heap[r] > heap[max]) max = r;

	if (max != i) {
		swap(heap, i, max);
		heapify_c(heap, n, max);
	}
}

void heapify_p(int *heap, int n, int i) {
	int p = (i - 1) / 2;
	if (p < 0 || p == i) return;

	int l = 2 * p + 1;
	int r = 2 * p + 2;


	int max = p;
	if (l < n && heap[l] > heap[max]) max = l;
	if (r < n && heap[r] > heap[max]) max = r;
	if (max != p) {
		swap(heap, p, max);
		heapify_p(heap, n, p);
	}
}


void heap_max(int *arr, int n) {
	int lastnonleaf = n / 2 - 1;

	for (int i = lastnonleaf; i >= 0; i--) 
		heapify_c(arr, n, i);
}


int *inorder(int ROOT, int *heap, int *arr, int *idx, int size) {
	if (ROOT >= size) return arr;
	if (!arr) arr = malloc(size * sizeof(int));
	if (!idx) idx = calloc(1, sizeof(int));

	inorder(2 * ROOT + 1, heap, arr, idx, size);
	arr[(*idx)++] = heap[ROOT];
	inorder(2 * ROOT + 2, heap, arr, idx, size);

	return arr;
}

int *preorder(int ROOT, int *heap, int *arr, int *idx, int size) {
	if (ROOT >= size) return arr;
	if (!arr) arr = malloc(size * sizeof(int));
	if (!idx) idx = calloc(1, sizeof(int));

	arr[(*idx)++] = heap[ROOT];
	preorder(2 * ROOT + 1, heap, arr, idx, size);
	preorder(2 * ROOT + 2, heap, arr, idx, size);

	return arr;
}

int *postorder(int ROOT, int *heap, int *arr, int *idx, int size) {
	if (ROOT >= size) return arr;
	if (!arr) arr = malloc(size * sizeof(int));
	if (!idx) idx = calloc(1, sizeof(int));

	postorder(2 * ROOT + 1, heap, arr, idx, size);
	postorder(2 * ROOT + 2, heap, arr, idx, size);
	arr[(*idx)++] = heap[ROOT];

	return arr;
}

void display(int *heap, int n) {
	printf("Level order:"); printarr(heap, n); printf("\n"); printf("\n");
	printf("Inorder:"); printarr(inorder(0, heap, NULL, NULL, n), n); printf("\n"); printf("\n");
	printf("Preorder:"); printarr(preorder(0, heap, NULL, NULL, n), n); printf("\n"); printf("\n");
	printf("Postorder:"); printarr(postorder(0, heap, NULL, NULL, n), n); printf("\n"); printf("\n");
}

void insert(int *heap, int val, int size) {
	heap[size] = val;
	heapify_p(heap, size + 1, size);
}

int delete(int *heap, int idx, int size) {
	int t = heap[size - 1];
	swap(heap, idx, size - 1);
	heap[size - 1] = 0;
	heapify_c(heap, size - 1, idx);
	heapify_p(heap, size - 1, idx);
	return t;
}

void enqueue(int *heap, int val, int size) {
	insert(heap, val, size);
}

int dequeue(int *heap, int size) {
	return delete(heap, 0, size);
}

void heapsort(int *arr, int size) {
	printf("Given Array: ");
	printarr(arr, size); printf("\n");
	printf("\n");

	heap_max(arr, size);

	for (int domain = size - 1; domain > 0; domain--) {
		swap(arr, 0, domain);
		heapify_c(arr, domain, 0);
	}

	printf("Sorted Array: ");
	printarr(arr, size); printf("\n");
	printf("\n");
}

void mergeheaps(int *heap1, int size1, int *heap2, int size2) {
	heap_max(heap1, size1);
	heap_max(heap2, size2);

	for (int i = size2 - 1; i >= 0; i--) {
		insert(heap1, delete(heap2, i, i + 1), size1++);
	}
}

void test() {

    // -------- Test 1 --------
    int heap1[100];
    int size1 = 0;
    printf("\nTest 1 (Empty)\nDisplay: ");
    display(heap1, size1);
    printf("Expected: (empty)\n");

    // -------- Test 2 --------
    int heap2[100];
    int size2 = 0;

    insert(heap2, 10, size2); size2++;
    printf("\nTest 2\nAfter Insert 10: ");
    display(heap2, size2);
    printf("Expected: 10\n");

    delete(heap2, 0, size2); size2--;
    printf("After Delete index 0: ");
    display(heap2, size2);
    printf("Expected: (empty)\n");

    // -------- Test 3 --------
    int heap3[100];
    int size3 = 0;
    int arr3[100] = {50, 30, 40, 10, 20, 35, 37};

    for (int i = 0; i < 7; i++) {
        insert(heap3, arr3[i], size3);
        size3++;
    }

    printf("\nTest 3\nAfter Inserts: ");
    display(heap3, size3);
    printf("Expected: 50 30 40 10 20 35 37\n");

    delete(heap3, 2, size3); size3--;
    printf("After Delete index 2: ");
    display(heap3, size3);
    printf("Expected: Valid max-heap\n");

    // -------- Test 4 --------
    int heap4[100];
    int size4 = 0;
    int arr4[100] = {10, 20, 15, 30, 40, 50, 100};

    for (int i = 0; i < 7; i++) {
        insert(heap4, arr4[i], size4);
        size4++;
    }

    printf("\nTest 4\nAfter Inserts: ");
    display(heap4, size4);
    printf("Expected: 100 40 50 30 20 10 15\n");

    delete(heap4, 3, size4); size4--;
    printf("After Delete index 3: ");
    display(heap4, size4);
    printf("Expected: Valid max-heap\n");

    // -------- Test 5 --------
    int heap5[100];
    int size5 = 0;
    int arr5[100] = {12, 11, 13, 5, 6, 7};

    for (int i = 0; i < 6; i++) {
        insert(heap5, arr5[i], size5);
        size5++;
    }

    printf("\nTest 5\nAfter Inserts: ");
    display(heap5, size5);
    printf("Expected: 13 11 12 5 6 7\n");

    delete(heap5, 4, size5); size5--;
    printf("After Delete index 4: ");
    display(heap5, size5);
    printf("Expected: Valid max-heap\n");

    // -------- Test 6 --------
    int heap6[100];
    int size6 = 0;
    int arr6[100] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < 7; i++) {
        insert(heap6, arr6[i], size6);
        size6++;
    }

    printf("\nTest 6\nAfter Inserts: ");
    display(heap6, size6);
    printf("Expected: 7 5 6 1 4 2 3\n");

    delete(heap6, 2, size6); size6--;
    printf("After Delete index 2: ");
    display(heap6, size6);
    printf("Expected: Valid max-heap\n");

    // -------- Test 7 --------
    int heap7[100];
    int size7 = 0;
    int arr7[100] = {9, 8, 7, 6, 5, 4, 3};

    for (int i = 0; i < 7; i++) {
        insert(heap7, arr7[i], size7);
        size7++;
    }

    printf("\nTest 7\nAfter Inserts: ");
    display(heap7, size7);
    printf("Expected: 9 8 7 6 5 4 3\n");

    delete(heap7, 1, size7); size7--;
    printf("After Delete index 1: ");
    display(heap7, size7);
    printf("Expected: Valid max-heap\n");

    // -------- Test 8 --------
    int heap8[100];
    int size8 = 0;
    int arr8[100] = {5, 5, 5, 5, 5};

    for (int i = 0; i < 5; i++) {
        insert(heap8, arr8[i], size8);
        size8++;
    }

    printf("\nTest 8\nAfter Inserts: ");
    display(heap8, size8);
    printf("Expected: 5 5 5 5 5\n");

    delete(heap8, 2, size8); size8--;
    printf("After Delete index 2: ");
    display(heap8, size8);
    printf("Expected: Valid max-heap\n");

    // -------- Test 9 --------
    int heap9[100];
    int size9 = 0;
    int arr9[100] = {-1, -3, -2, -7, -6, -5};

    for (int i = 0; i < 6; i++) {
        insert(heap9, arr9[i], size9);
        size9++;
    }

    printf("\nTest 9\nAfter Inserts: ");
    display(heap9, size9);
    printf("Expected: -1 -3 -2 -7 -6 -5\n");

    delete(heap9, 1, size9); size9--;
    printf("After Delete index 1: ");
    display(heap9, size9);
    printf("Expected: Valid max-heap\n");

    // -------- Test 10 --------
    int heap10[100];
    int size10 = 0;
    int arr10[100] = {3, -2, 15, 0, -7, 8, 4};

    for (int i = 0; i < 7; i++) {
        insert(heap10, arr10[i], size10);
        size10++;
    }

    printf("\nTest 10\nAfter Inserts: ");
    display(heap10, size10);
    printf("Expected: 15 3 8 0 -7 -2 4\n");

    delete(heap10, 3, size10); size10--;
    printf("After Delete index 3: ");
    display(heap10, size10);
    printf("Expected: Valid max-heap\n");
}

void test_heapsort() {

    // Case 1: Already sorted
    int a1[100] = {1, 2, 3, 4, 5};
    int n1 = 5;
    heapsort(a1, n1);
    // Expected: 1 2 3 4 5

    // Case 2: Reverse sorted
    int a2[100] = {9, 7, 5, 3, 1};
    int n2 = 5;
    heapsort(a2, n2);
    // Expected: 1 3 5 7 9

    // Case 3: Random order
    int a3[100] = {4, 1, 6, 2, 8, 5};
    int n3 = 6;
    heapsort(a3, n3);
    // Expected: 1 2 4 5 6 8

    // Case 4: Contains duplicates
    int a4[100] = {4, 2, 4, 3, 2, 1};
    int n4 = 6;
    heapsort(a4, n4);
    // Expected: 1 2 2 3 4 4

    // Edge Case 1: Single element
    int a5[100] = {42};
    int n5 = 1;
    heapsort(a5, n5);
    // Expected: 42

    // Edge Case 2: Two elements (unsorted)
    int a6[100] = {10, 2};
    int n6 = 2;
    heapsort(a6, n6);
    // Expected: 2 10

    // Edge Case 3: All elements equal
    int a7[100] = {7, 7, 7, 7};
    int n7 = 4;
    heapsort(a7, n7);
    // Expected: 7 7 7 7

    // Edge Case 4: Empty array
    int a8[100] = {};
    int n8 = 0;
    heapsort(a8, n8);
    // Expected: (no output)

    // Edge Case 5: Negative numbers
    int a9[100] = {-3, -1, -7, -4, -5};
    int n9 = 5;
    heapsort(a9, n9);
    // Expected: -7 -5 -4 -3 -1

    // Edge Case 6: Mixed positive and negative
    int a10[100] = {3, -2, 5, -1, 0};
    int n10 = 5;
    heapsort(a10, n10);
    // Expected: -2 -1 0 3 5
}

void test_mergeheaps() {

    // Case 1
    int a1[100] = {1, 3, 5, 7};
    int a2[100] = {2, 4, 6, 8};
    mergeheaps(a1, 4, a2, 4);
    printf("Merged: \n");
    printarr(a1, 8); printf("\n");
    // Expected: 1 2 3 4 5 6 7 8

    // Case 2
    int b1[10] = {1, 5, 9};
    int b2[100] = {2, 6, 10, 12};
    mergeheaps(b1, 3, b2, 4);
    printf("Merged: \n");
    printarr(b1, 7); printf("\n");
    // Expected: 1 2 5 6 9 10 12

    // Case 3
    int c1[10] = {3, 8, 15, 20, 25};
    int c2[100] = {1, 2};
    mergeheaps(c1, 5, c2, 2);
    printf("Merged: \n");
    printarr(c1, 7); printf("\n");
    // Expected: 1 2 3 8 15 20 25

    // Case 4 (h2 empty)
    int d1[100] = {4, 10, 14};
    int d2[100] = {};
    mergeheaps(d1, 3, d2, 0);
    printf("Merged: \n");
    printarr(d1, 3); printf("\n");
    // Expected: 4 10 14

    // Case 5 (h1 empty)
    int e1[5] = {};
    int e2[100] = {5, 3, 1};
    mergeheaps(e1, 0, e2, 3);
    printf("Merged: \n");
    printarr(e1, 3); printf("\n");
    // Expected: 1 3 5

    // Case 6 (both empty)
    int f1[5] = {};
    int f2[100] = {};
    mergeheaps(f1, 0, f2, 0);
    printf("Merged: \n");
    printarr(f1, 0); printf("\n");
    // Expected: (empty line)

    // Case 7 (duplicates)
    int g1[10] = {2, 4, 6};
    int g2[100] = {2, 4, 5};
    mergeheaps(g1, 3, g2, 3);
    printf("Merged: \n");
    printarr(g1, 6); printf("\n");
    // Expected: 2 2 4 4 5 6

    // Case 8 (mixed)
    int h1arr[10] = {1, 10, 20};
    int h2arr[100] = {2, 3, 4, 5};
    mergeheaps(h1arr, 3, h2arr, 4);
    printf("Merged: \n");
    printarr(h1arr, 7); printf("\n");
    // Expected: 1 2 3 4 5 10 20

    // Case 9 (negative values)
    int i1[10] = {-3, 0, 7};
    int i2[100] = {-10, -5, 2};
    mergeheaps(i1, 3, i2, 3);
    printf("Merged: ");
    printarr(i1, 6); printf("\n");
    // Expected: -10 -5 -3 0 2 7
}

int main() {

    // Run predefined tests
    test();
    printf("\n\n");
    test_heapsort();
    printf("\n\n");
    test_mergeheaps();

    // -------- User Input --------
    int n;
    printf("\nEnter size: ");
    scanf("%d", &n);

    int arr[100];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Input: ");
    printarr(arr, n); printf("\n");

    heap_max(arr, n);

    printf("Output (Max Heap): ");
    printarr(arr, n); printf("\n");

    return 0;
}
