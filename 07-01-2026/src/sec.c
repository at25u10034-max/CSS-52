#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct vector {
	int l;
	int s;
};

struct vector second(size_t len, int* data) {
	struct vector sec = {0, INT_MAX};
	struct vector fir = {0, INT_MAX};
	
	for (size_t i = 0; i < len; i++) {
		if (data[i] > fir.l) {
			sec.l = fir.l;
			fir.l = data[i];
		} else if (data[i] > sec.l) {
			sec.l = data[i];
		}

		if (data[i] < fir.s) {
			sec.s = fir.s;
			fir.s = data[i];
		} else if (data[i] < sec.s) {
			sec.s = data[i];
		}
	}

	return sec;
}

int main() {
	int *data = malloc(1024 * sizeof(int));
	size_t idx = 0;
	size_t len;
	printf("\033[33;1mWARN: ERRANEOUS INPUT NOT HANDLED!\033[0m\n");
	printf("Enter number of integers: ");
	scanf("%zu", &len);

	while (len - idx) {
		printf("Enter integer: ");
		scanf("%d", &data[idx++]);
	}

	printf("Given Array: [");
	for (size_t i = 0; i < len - 1; i++) {
		printf("%d, ", data[i]);
	}
	printf("%d]\n", data[len - 1]);

	struct vector sec = second(len, data);
	printf("Second Largest Element: %d\n", sec.l);
	printf("Second Smallest Element: %d\n", sec.s);
	
}
