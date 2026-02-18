#include <stdio.h>
#include <stdlib.h>

#ifndef __LL
#define __LL
typedef struct Node {
	int data;
	struct Node *next;	
} Node;

struct Node *create() {
	int t;
	struct Node *temp = NULL;
	scanf("%d", &t);
	temp = malloc(sizeof(struct Node));
	if (!temp) {
		fprintf(stderr, "ERROR!! No space in RAM.");
	}
		
	temp -> data = t;
	temp -> next = NULL;
}


void showlist (struct Node *n) {
	while (n) {
		printf ("%d -> ", n -> data);
		n = n -> next;
	}
	printf("NULL\n");
}


// Insertion Functions
struct Node *insert_start(struct Node *HEAD) {
	struct Node *temp = create();
	temp -> next = HEAD;
	return temp;
}

struct Node *insert_end(struct Node *HEAD) {
	struct Node *TAIL = HEAD;
	if (!TAIL) 
		return insert_start(NULL);
		
	while (TAIL -> next)
		TAIL = TAIL -> next;
		
	struct Node *temp = create();
	TAIL -> next = temp;
	return HEAD;
}


// Program Flow Functions
void free_list (struct Node *n) {
	if (n == NULL)
		return;

	struct Node* next = n -> next;
	while (n) {
		free(n);
		n = next;
		if (n)
			next = n -> next;
	}
}

#endif
