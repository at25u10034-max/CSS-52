#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    int size;
    int *data;
    int top;
} Stack;

Stack createstack(int);
void showstack(Stack*);
void freestack(Stack*);

void push(Stack*, int);
int pop(Stack*);
int peek(Stack*);

int size(Stack*);
int isEmpty(Stack*);
int isFull(Stack*);

#endif