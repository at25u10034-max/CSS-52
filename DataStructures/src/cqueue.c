#include "../include/queue.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


// HELPER - Modular Add
int wnext(int a, int size) {
	return (a + 1) % size;
}



// IMPLEMENTATION

Queue createqueue(int size) {
	Queue q = {.size = size, .REAR = -1, .FRONT = -1};
	q.data = calloc(size, sizeof(int));

	return q;
}

void freequeue(Queue *q) {
	free(q -> data);
	free(q);
}

void showqueue(Queue* q) {
	printf("Queue {\n\tSize: %d\n\tREAR: %d\n\t", q->size, q->REAR);

	if (isEmpty(q)) {
		printf("CLEAR QUEUE.\n}\n");
		return;
	}

	printf("FRONT: ");
	for (int i = q->FRONT; i != (q -> REAR); i = wnext(i, q->size))
		printf("%d <- ", q->data[i]);

	printf("%d <- REAR\n}\n", q->data[q->REAR]);
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

void enqueue(Queue* q, int val) {
	if (isFull(q)) {
		fprintf(stderr, "%s\n", "OVERFLOW: Queue is Full!");
		return;
	}

	q -> REAR = wnext(q->REAR, q->size);
	q -> data[q -> REAR] = val;

	if (q -> FRONT == -1) q->FRONT = q->REAR;
}


int dequeue(Queue* q) {
	if (isEmpty(q)) {
		fprintf(stderr, "%s\n", "UNDERFLOW: Queue is Empty!");
		return INT_MIN;
	}

	int d = q -> data[q->FRONT];
	
	if (q -> FRONT == q -> REAR)
		q -> FRONT = q -> REAR = -1;
	else 
		q -> FRONT = wnext(q -> FRONT, q -> size);
	

	return d;
}

int peek(Queue* q) {
	if (isEmpty(q)) {
		fprintf(stderr, "%s\n", "Queue is Empty!");
		return INT_MIN;
	}

	return q -> data[q->FRONT];
}