#define __incl_display


#ifndef __HEADER
#define __HEADER

#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef __NODE
#define __NODE
typedef struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
} Node;
#endif

void display_sparse(Node* HEAD, int rows, int cols, FILE* outfile) {
	int i = 0, j = 0;
	
	while (HEAD) {
		// if (i != HEAD -> row) j=0;
		while (i != HEAD -> row) {
			if (j == cols - 1) {
				printf("0\n");
				if (outfile) fprintf(outfile, "0\n");
				j = 0;
				i++;
			} else {
				printf("0 ");
				if (outfile) fprintf(outfile, "0 ");

				j++;
			}
		}

		while (j != HEAD -> col) {
			printf("0 ");
			if (outfile) fprintf(outfile, "0 ");

			j++;
		}

		if (HEAD -> col == cols - 1) {
			printf("%d\n", HEAD -> value);
			if (outfile) fprintf(outfile, "%d\n", HEAD -> value);
			j = 0;
			i++;
		} else {
			printf("%d ", HEAD -> value);
			if (outfile) fprintf(outfile, "%d ", HEAD -> value);
			j++;
		}

		HEAD = HEAD -> next;
	}

	while (i < rows) {
		if (j == cols - 1) {
			printf("0\n");
			if (outfile) fprintf(outfile, "0\n");
			j = 0;
			i++;
		} else {
			printf("0 ");
			if (outfile) fprintf(outfile, "0 ");
			j++;
		}
	}
}
