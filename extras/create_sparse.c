#ifndef __HEADER
#define __HEADER

#include <stdio.h>
#include <stdlib.h>
#define MAX 10
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

void showlist(Node *A);

Node* create_sparse(int matrix[][MAX], int rows, int cols) {
	Node* HEAD = NULL, *temp = NULL, *new;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j]) {
				new = malloc(sizeof(Node));
				
				new -> row = i;
				new -> col = j;
				new -> value = matrix[i][j];
				new -> next = NULL;
				if (!HEAD) {
					HEAD = temp = new;
				} else {
					temp->next = new;
					temp = new;
				}
			}
		}
	}

	printf("Created List: ");
	showlist(HEAD);
	return HEAD;
				
}
