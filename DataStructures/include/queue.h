#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
	const size_t size;
	ssize_t REAR;
	ssize_t FRONT;
	int *data;
} Queue;

Queue createqueue(int);
void freequeue(Queue*);
void showqueue(Queue*);

void enqueue(Queue*, int);
int dequeue(Queue*);
int peek(Queue*);

int size(Queue*);
int isEmpty(Queue*);
int isFull(Queue*);

#endif