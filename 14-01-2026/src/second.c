#define __main__
#include "insertion.c"

int main() {
	for (int i = 0; i < N_CASES; i++) {

		if (sizes[i] < 2) {
			printf("No second element for array: ");
			printarr(sizes[i], tests[i]);
			printf("\n\n");
		}
		else { 
			isort(sizes[i], tests[i]);
			printf("2nd Largest Element: %d, 2nd Smallest Element: %d\n\n", tests[i][sizes[i] - 2], tests[i][1]);
		}

		printf("-------------------------------------------------------------\n");
		
	}
}
