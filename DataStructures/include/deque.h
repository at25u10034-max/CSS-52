#include <stdio.h>

#ifndef DEQUE_H
#define DEQUE_H

enum DequeMode {
	UNRESTRICTED,
	INPUT_RESTRICTED,
	OUTPUT_RESTRICTED
};

typedef struct Deque {
	const size_t size;
	ssize_t REAR;
	ssize_t FRONT;
	const enum DequeMode mode;
	int *data;
} Deque;

Deque createdeque(int, enum DequeMode);
void freedeque(Deque*);
void showdeque(Deque*);

void enqueue_front(Deque*, int);
void enqueue_rear(Deque*, int);
int dequeue_front(Deque*);
int dequeue_rear(Deque*);
int front(Deque*);
int back(Deque*);
int at(Deque*, int);

int size(Deque*);
int isEmpty(Deque*);
int isFull(Deque*);

#endif