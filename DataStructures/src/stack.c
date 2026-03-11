#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "../include/stack.h"

Stack createstack(int size) {
    Stack s = {
        .size = size,
        .data = malloc(size * sizeof(int)),
        .top = -1
    };
    return s;
}

void freestack(Stack* s) {
    free(s->data);
    free(s);
}

void showstack(Stack *s) {
    printf("Stack {\n\tSize: %d\n\tTOP: %d\n\t", s->size, s->top);

    if (isEmpty(s)) {
        printf("CLEAR STACK.\n}\n");
        return;
    }

    printf("TOP -> ");
    for (int i = s -> top; i > 0; i--)
        printf("%d -> ", s->data[i]);

	printf("%d\n", s -> data[0]);
}

int size(Stack *s) {
    return s -> top + 1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == s->size - 1;
}

void push(Stack* s, int c) {
    if (!isFull(s))
        s->data[++s->top] = c;
    else
        fprintf(stderr, "%s\n", "OVERFLOW: Attempt to push into full stack.");
}

int pop(Stack* s) {
    if (!isEmpty(s))
        return s->data[s->top--];
    fprintf(stderr, "%s\n", "UNDERFLOW: Attempt to pop empty stack.");
    return INT_MIN;
}

int peek(Stack* s) {
    if (!isEmpty(s))
        return s->data[s->top];

    fprintf(stderr, "%s\n", "UNDERFLOW: Attempt to peek empty stack.");
    return '\0';
}