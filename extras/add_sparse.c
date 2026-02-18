#define __incl_add

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

Node *copy(Node *t) {
	Node *c = malloc(sizeof(Node));
	*c = *t;
	return c;
}

#ifndef __incl_display
#include "display_sparse.c"
#endif

Node* add_sparse(Node* A, Node* B) {
	Node *_A = A, *_B = B;
	Node *HEAD = NULL, *temp = NULL, *new;

	while (A && B) {
		if (A -> row < B -> row) {
			new = copy(A);
			A = A -> next;
		} else if (B -> row < A -> row) {
			new = copy(B);
			B = B -> next;
		} else {
			if (A -> col < B -> col) {
				new = copy(A);
				A = A -> next;
			} else if (B -> col < A -> col) {
				new = copy(B);
				B = B -> next;
			} else {
				new = copy(A);
				new -> value += B -> value;
				A = A -> next;
				B = B -> next;
			}
		}

		if (new -> value != 0) {
			if (!HEAD) {
				HEAD = temp = new;
			} else {
				temp -> next = new;
				temp = new;
			}
		}
		
 				
	}

	if (!A){
		while (B) {
			new = copy(B);
			if (!HEAD) {
				HEAD = temp = new;
			} else {
				temp -> next = new;
				temp = new;
			}

			B = B->next;
		}
	}
	
	if (!B){
		while (A) {
			new = copy(A);
			if (!HEAD) {
				HEAD = temp = new;
			} else {
				temp -> next = new;
				temp = new;
			}

			A = A->next;
		}
	}

	FILE *f = fopen("temp.txt", "w");
	
	printf("Matrix_1: \n");
	showlist(_A);
	display_sparse (_A, MAX, MAX, f);

	printf("Matrix_2: \n");
	showlist(_B);
	display_sparse (_B, MAX, MAX, f);

	printf("Sum: \n");
	showlist(HEAD);
	display_sparse (HEAD, MAX, MAX, f);

	fclose(f);
	




	return HEAD;
	
};
