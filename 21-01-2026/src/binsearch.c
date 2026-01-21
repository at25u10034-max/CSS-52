
#include <stdio.h>


int sorted(int *arr, int size, int start) {
	for (int i = start; i < size - 1; i++) {
		if (arr[i] > arr[i + 1])
			return 0;
	}
	return 1;
}


int binsearch(int *data, int needle, int low, int high) {
	int mid = (high + low) / 2;

	if (data[mid] == needle)
		return mid;
		
	if (low == high) return -1;
	
	if (data[mid] < needle)
		return binsearch(data, needle, mid + 1, high);
	if (data[mid] > needle)
		return binsearch(data, needle, low, mid - 1);

	return mid;
}



int main() {
	int n, needle, fidx, lidx;
	printf("Enter number of Elements: ");
	scanf("%d", &n);

	int data[n];
	printf("Enter Elements: ");
	
	for (int i = 0; i < n; i++) 
		scanf("%d", &data[i]);


	if (!sorted(data, n, 0)) {
		printf("Unsorted Array cannot be binary-searched.\n");
		return 1;
	}
	
	printf("Enter element to search: ");
	scanf("%d", &needle);

	lidx = fidx = binsearch(data, needle, 0, n - 1);

	if (lidx == -1) {
		printf("Element Not found.\n");
		return 1;
	}

	while (lidx < n && data[lidx] == needle)
		lidx++;
	lidx--;

	while (fidx >= 0 && data[fidx] == needle)
		fidx--;
	fidx++;

	printf("First Occurence = %d\n", fidx + 1);
	printf("Last Occurence = %d\n", lidx + 1);
}



// Cases:
/*
	1. Elements start at beginning
	2. Elements finish at end
	3. Elements are somewhere in between
	4. One Element
	5. Two Element
	6. No element
	7. Unsorted Array


*/
