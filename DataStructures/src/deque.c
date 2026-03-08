#include "../include/deque.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


// HELPER - Modular Add
int wnext(int a, int size) {
	return (a + 1) % size;
}

int wprev(int a, int size) {
	return (size + a - 1) % size;
}


// IMPLEMENTATION

Deque createdeque(int size, enum DequeMode mode) {
	Deque q = {
		.size = size, 
		.REAR = -1, 
		.FRONT = -1, 
		.mode = mode
	};

	q.data = calloc(size, sizeof(int));
	return q;
}


void freedeque(Deque *q) {
	free(q -> data);
	free(q);
}

void showdeque(Deque* q) {
	printf("Deque {\n\tSize: %d\n\tREAR: %d\n\t", q->size, q->REAR);

	if (isEmpty(q)) {
		printf("CLEAR QUEUE.\n}\n");
		return;
	}

	printf("FRONT: ");
	for (int i = q->FRONT; i != (q -> REAR); i = wnext(i, q->size))
		printf("%d <- ", q->data[i]);

	printf("%d <- REAR\n}\n", q->data[q->REAR]);
}




int isFull(Deque* q) {
	return wnext(q->REAR, q->size) == q -> FRONT;
}

int isEmpty(Deque* q) {
	return q -> REAR == -1;
}

int size(Deque* q) {
	if (isEmpty(q)) return 0;
	if (q -> REAR >= q -> FRONT)
		return q-> REAR - q-> FRONT + 1;
	else
		return q -> REAR - q -> FRONT + q -> size + 1;
}




void enqueue_rear(Deque* q, int val) {
	if (isFull(q)) {
		fprintf(stderr, "%s\n", "OVERFLOW: Deque is Full!");
		return;
	}

	q -> REAR = wnext(q->REAR, q->size);
	q -> data[q -> REAR] = val;

	if (q -> FRONT == -1) q->FRONT = q->REAR;
}

int dequeue_front(Deque* q) {
	if (isEmpty(q)) {
		fprintf(stderr, "%s\n", "UNDERFLOW: Deque is Empty!");
		return INT_MIN;
	}

	int d = q -> data[q->FRONT];
	
	if (q -> FRONT == q -> REAR)
		q -> FRONT = q -> REAR = -1;
	else 
		q -> FRONT = wnext(q -> FRONT, q -> size);
	

	return d;
}




void enqueue_front(Deque* q, int val) {
	if ( q -> mode & INPUT_RESTRICTED) {
		fprintf(stderr, "ENQUEUE FRONT IS RESTRICTED!\n");
		return;
	}

	if (isFull(q)) {
		fprintf(stderr, "%s\n", "OVERFLOW: Deque is Full!");
		return;
	}

	q -> FRONT = wprev(q->FRONT, q->size);
	q -> data[q -> FRONT] = val;

	if (q -> REAR == -1) q-> REAR = q -> FRONT;
}


int dequeue_rear(Deque* q) {
	if ( q -> mode & OUTPUT_RESTRICTED ) {
		fprintf(stderr, "DEQUEUE REAR IS RESTRICTED!\n");
		return INT_MIN;
	}

	if (isEmpty(q)) {
		fprintf(stderr, "%s\n", "UNDERFLOW: Deque is Empty!");
		return INT_MIN;
	}

	int d = q -> data[q->REAR];
	
	if (q -> FRONT == q -> REAR)
		q -> FRONT = q -> REAR = -1;
	else 
		q -> REAR = wprev(q -> REAR, q -> size);
	

	return d;
}




int front(Deque* q) {
	if (isEmpty(q)) {
		fprintf(stderr, "%s\n", "Deque is Empty!");
		return INT_MIN;
	}

	return q -> data[q->FRONT];
}


int back(Deque* q) {
	if (isEmpty(q)) {
		fprintf(stderr, "%s\n", "Deque is Empty!");
		return INT_MIN;
	}

	return q -> data[q->REAR];
}