#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "sll.c"

#ifndef __STACK
#define __STACK

struct nodew {
    Node *node;
    struct nodew *next;
};

typedef struct stack {
    struct nodew *TOP;
} Stack;





/* Initialize stack */
Stack* create_stack() {
    Stack* st = malloc(sizeof(Stack));
    st -> TOP = NULL;
    return st;
}

int is_empty(Stack* st) {
    return st -> TOP == NULL;
}

void push(Stack* st, Node *n) {
	struct nodew *t = malloc(sizeof(struct nodew));
	t -> node = n;
	
    if (!is_empty(st))
        t -> next = st -> TOP;
    st -> TOP = t;
}

Node * pop(Stack* st) {
    if (!is_empty(st)) {
    	struct nodew *t = st -> TOP;
    	Node *tt = t->node;
    	st -> TOP = t -> next;
    	free(t);
    	return tt;
    }
    fprintf(stderr, "WARNING: POPPING EMPTY STACK!\n");
    return NULL;
}

Node * peek(Stack* st) {
    if (!is_empty(st))
        return st->TOP->node;
        
    fprintf(stderr, "WARNING: PEEKING EMPTY STACK!\n");
    return NULL;
}

void freew(struct nodew *node) {
	if (!node) return;
	freew(node -> next);
	free(node);
}

void free_stack(Stack* st) {
	if (!st) return;
    freew(st->TOP);
    free(st);
}
#endif
