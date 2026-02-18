#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifndef __LL
#define __LL
typedef struct Node {
	int val;
	struct Node* next;
} Node;

Node *newnode(int c) {
	Node *n = malloc(sizeof(Node));
	if (!n) {
		printf("FATAL ERROR! Could not allocate memory.");
		exit(1);
	}

	n -> next = NULL;
	n -> val = c;

	return n;
}

void free_list(Node *n) {
	if (!n) return;
	if (n -> next)
		free(n -> next);

	free(n);
}

#endif

#ifndef __STACK
#define __STACK
typedef struct stack {
    Node *TOP;
} Stack;





/* Initialize stack */
Stack* create_stack() {
    Stack* st = malloc(sizeof(Stack));
    st -> TOP = NULL;
    return st;
}

void printstack(Stack *st) {
	Node *t = st -> TOP;
	if (!t) {
		printf("NULL\n");
		return;
	}
	
	while (t -> next) {
		printf("%d <- ", t -> val);
		t = t -> next;
	}
	printf("%d\n", t -> val);
}

int is_empty(Stack* st) {
    return st -> TOP == NULL;
}

void push(Stack* st, int c) {
	Node *n = newnode(c);
    if (!is_empty(st))
        n -> next = st -> TOP;
    st -> TOP = n;
}

int pop(Stack* st) {
    if (!is_empty(st)) {
    	Node *t = st -> TOP;
    	int val = t -> val;
    	st -> TOP = t -> next;
    	free(t);
    	return val;
    }
    fprintf(stderr, "WARNING: POPPING EMPTY STACK!\n");
    return INT_MIN;
}

int peek(Stack* st) {
    if (!is_empty(st))
        return st->TOP->val;
        
    fprintf(stderr, "WARNING: PEEKING EMPTY STACK!\n");
    return INT_MIN;
}

void free_stack(Stack* st) {
	if (!st) return;
    free_list(st->TOP);
    free(st);
}
#endif
