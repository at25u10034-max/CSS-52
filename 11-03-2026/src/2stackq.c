#include <stdio.h>
#include <stdlib.h>

#include "../../DataStructures/include/stack.h"

typedef struct Queue {
	const size_t size;
	Stack FWD;
	Stack BACK;
} Queue;

Queue createqueue(int size) {
	Queue q = {.size = size};
	q.FWD = createstack(size);
	q.BACK = createstack(size);

	return q;
};


void freequeue(Queue* q) {
	freestack(&q->FWD);
	freestack(&q->BACK);
	free(q);
};

void showqueue(Queue* q) {
	showstack(&q->FWD);
};

void enqueue(Queue* q, int val) {
	int v;
	while(!isEmpty(&q->FWD)) {
		v = pop(&q->FWD);
		push(&q->BACK, v);
	}
	
	push(&q->FWD, val);

	while(!isEmpty(&q->BACK))
		push(&q->FWD, pop(&q->BACK));
};

int dequeue(Queue* q) {
	int d;
	while(!isEmpty(&q->FWD))
		push(&q->BACK, pop(&q->FWD));

	d = pop(&q->BACK);

	while(!isEmpty(&q->BACK))
		push(&q->FWD, pop(&q->BACK));

	return d;
};

int peekq(Queue* q) {
	int d;
	while(!isEmpty(&q->FWD))
		push(&q->BACK, pop(&q->FWD));

	d = peek(&q->BACK);

	while(!isEmpty(&q->BACK))
		push(&q->FWD, pop(&q->BACK));

	return d;
};

int sizeq(Queue* q) {
	return size(&q -> FWD);
};

int isEmptyq(Queue* q) {
	return isEmpty(&q -> FWD);
};

int isFullq(Queue* q) {
	return isFull(&q -> FWD);
};
