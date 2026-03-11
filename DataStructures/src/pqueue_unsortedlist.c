#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/pqueue.h"


// HELPER - Modular Add
int wnext(int a, int size) {
	return (a + 1) % size;
}


int wprev(int a, int size) {
	return (size + a - 1) % size;
}


// IMPLEMENTATION

Queue createqueue(int size) {
	Queue q = {.size = size, .REAR = -1, .FRONT = -1};
	q.data = calloc(size, sizeof(struct weighted));

	return q;
}

void freequeue(Queue *q) {
	free(q -> data);
	free(q);
}

void showqueue(Queue* q) {
	printf("Queue {\n\tSize: %zu\n\tREAR: %zd\n\tFRONT: %zd\n\t", q->size, q->REAR, q -> FRONT);

	if (isEmpty(q)) {
		printf("CLEAR QUEUE.\n}\n");
		return;
	}

	printf("FRONT: ");
	for (int i = q->FRONT; i != (q -> REAR); i = wnext(i, q->size))
		printf("%d [P: %d] <- ", q->data[i].val, q->data[i].weight);

	printf("%d [P: %d] <- REAR\n}\n", q->data[q->REAR].val, q->data[q->REAR].weight);
}

int isFull(Queue* q) {
	return wnext(q->REAR, q->size) == q -> FRONT;
}

int isEmpty(Queue* q) {
	return q -> REAR == -1;
}

int size(Queue* q) {
	if (isEmpty(q)) return 0;
	if (q -> REAR >= q -> FRONT)
		return q-> REAR - q-> FRONT + 1;
	else
		return q -> REAR - q -> FRONT + q -> size + 1;
}

void enqueue(Queue* q, int val, int weight) {
	struct weighted element = {val, weight};

	if (isFull(q)) {
		fprintf(stderr, "%s\n", "OVERFLOW: Queue is Full!");
		return;
	}

	q -> REAR = wnext(q->REAR, q->size);
	q -> data[q -> REAR] = element;

	if (q -> FRONT == -1) q->FRONT = q->REAR;
}


int dequeue(Queue* q) {
	int max_idx = q -> FRONT;
	if (isEmpty(q)) {
		fprintf(stderr, "%s\n", "UNDERFLOW: Queue is Empty!");
		return INT_MIN;
	}

	for (int i = wnext(q -> FRONT, q->size); i != wnext(q -> REAR, q->size); i = wnext(i, q->size)) {
		if (q -> data[i].weight > q -> data[max_idx].weight)
			max_idx = i;
	}

	int d = q -> data[max_idx].val;
	
	for (int i = max_idx; i != q->REAR; i = wnext(i, q->size))
		q->data[i] = q->data[wnext(i, q->size)];

	q->data[q -> REAR].val = 0;
	q->data[q -> REAR].weight = 0;

	if (q -> FRONT == q -> REAR)
		q -> FRONT = q -> REAR = -1;
	else
		q -> REAR = wprev(q->REAR, q->size);
	

	return d;
}

int peek(Queue* q) {
	if (isEmpty(q)) {
		fprintf(stderr, "%s\n", "Queue is Empty!");
		return INT_MIN;
	}

	return q -> data[q->FRONT].val;
}