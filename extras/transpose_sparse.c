#define __incl_transpose

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

// Using Orthogonal Nodes, it is much simpler and time efficient, despite taking up more space.
typedef struct ONode {
	struct Node* node;
	struct ONode* right;
	struct ONode* down;
} ONode;

ONode *wrap(Node *t) {
	ONode *wrapper = malloc(sizeof(ONode));
	wrapper -> node = malloc(sizeof(Node));
	wrapper -> right = wrapper -> down = NULL;
	wrapper -> node -> value = t-> value;
	wrapper -> node -> row = t -> col;
	wrapper -> node -> col = t -> row;

	return wrapper;
}

Node* transpose_sparse(Node *A) {
	ONode *T = wrap(A), *otemp = T, *otemph = T;
	Node *temp = A, *HEAD = A;

	while (temp) {
		while (temp -> next && temp -> next -> row == temp -> row) {
			otemp -> down = wrap(temp -> next);
			temp = temp -> next;
			otemp = otemp -> down;
		}

		if (temp -> next) {
			otemp -> down = wrap(temp -> next);
		}
	}
	
	
}
