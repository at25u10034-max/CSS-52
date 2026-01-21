
#include <stdio.h>

void linsearch(int *data, int needle, int size) {
	int started = 0, freq = 0;
	for (int i = 0; i < size; i++) {
		if (data[i] == needle) {
			if (!started) {
				started = 1;
				printf("Element found at positions: ");
			}

			printf("%d ", i + 1);
			freq++;
		}
	}
	
	if (!started) {
		printf("Not Found.");
	}
	
	printf("\nFrequency = %d\n", freq);
}



int main() {
	int n, needle;
	printf("Enter number of Elements: ");
	scanf("%d", &n);

	int data[n];
	printf("Enter Elements: ");
	
	for (int i = 0; i < n; i++) 
		scanf("%d", &data[i]);

	printf("Enter Element to search: ");
	scanf("%d", &needle);

	linsearch(data, needle, n);
}
