#include <stdlib.h>
#include <stdio.h>

#ifndef __STACK
#define __STACK
typedef struct stack {
    int size;
    int *arr;
    int top;
} stack;



/* Initialize stack */
stack* create_stack(int size) {
    stack* s = (stack*)malloc(sizeof(stack));
    s->size = size;
    s->arr = malloc(size * sizeof(int));
    s->top = -1;
    return s;
}

void printstack(stack *st) {
	for (int i = st -> top; i > 0 ; i--) {
		printf("%d <- ", st->arr[i]);
	}
	printf("%d\n", st -> arr[0]);
}

int is_empty(stack* s) {
    return s->top == -1;
}

int is_full(stack* s) {
    return s->top == s->size - 1;
}

void push(stack* s, int c) {
    if (!is_full(s))
        s->arr[++s->top] = c;
}

int pop(stack* s) {
    if (!is_empty(s))
        return s->arr[s->top--];
    return '\0';
}

int peek(stack* s) {
    if (!is_empty(s))
        return s->arr[s->top];
    return '\0';
}

void free_stack(stack* s) {
    free(s->arr);
    free(s);
}
#endif
