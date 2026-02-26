#ifndef __incl_del
#define __incl_del

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


#include <stdio.h>
void showlist(Node *A);
void display_sparse(Node* HEAD, int rows, int cols, FILE* outfile);

Node* delete_element(Node *HEAD, int row, int col) {
	if (!HEAD) return NULL;
	if (HEAD -> row == row && HEAD -> col == col) {
		Node *d = HEAD;
		HEAD = HEAD -> next;
		free(d);
		return HEAD;
	}

	printf("Before Delete: \n");
	display_sparse(HEAD, MAX, MAX, NULL);
	printf("To Delete: %d %d\n", row, col);
	Node *temp = HEAD;
	while (temp && temp -> next && (temp -> next -> row != row || temp -> next -> col != col))
		temp = temp -> next;

	if (!temp -> next)
		return HEAD;

	Node *d = temp -> next;
	temp -> next = temp -> next -> next;
	free(d);
	printf("After Delete: \n");
	display_sparse(HEAD, MAX, MAX, NULL);
	return HEAD;
}

#endif