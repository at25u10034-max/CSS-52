#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack {
	int size;
	int* data;
	int TOP;
} stack_t;


bool isEmpty(stack_t *s) {
	return s->TOP < 0;
}

bool isFull(stack_t *s) {
	return s->TOP == s->size;
}

void push(stack_t *s, int v) {
	if (isFull(s))
		printf("STACK OVERFLOW. (Size = %d).\n", s->size);
	else
		s->data[++s->TOP] = v;
}

int pop(stack_t *s) {
	if (isEmpty(s)) 
		printf("STACK UNDERFLOW.\n");
	else
		return s->data[s->TOP--];
}

int peek(stack_t *s) {
	if (isEmpty(s)) 
		printf("STACK UNDERFLOW.\n");
	else
		return s->data[s->TOP];
}

stack_t *create(int size) {
	stack_t *s = malloc(sizeof(stack_t));

	s->size = size;
	s->data=malloc(size * sizeof(int));
	s->TOP = -1;
}

void display(stack_t *s) {
	if (isEmpty(s)) {
		printf("EMPTY!!\n\n");
		return;
	} 
	for (int i = s->TOP; i >= 0; i--) {
		printf("%d\n", s->data[i]);
	}
}

const char* MESSAGE = "Enter Option:\n\
\n\t(1) Display.\
\n\t(2) Push.\
\n\t(3) Pop.\
\n\t(4) IsEmpty.\
\n\t(5) IsFull.\n\
\n\t(0) Exit.\
\n\nOption: ";

int main() {
	int size;
	printf("Enter Size: ");
	scanf("%d", &size);
	stack_t *s = create(size);
	
	int n, flag = 1, t;
	bool b;
	while (flag) {
		printf("%s", MESSAGE);
		scanf("%d", &n);
		switch (n) {
			case 0:
				flag = 0;
				break;
			case 1:
				display(s);
				break;
			
			case 2:
				printf("Enter Data: ");
				scanf("%d", &t);
				push(s, t);
				break;

			case 3:
				b = isEmpty(s);
				t = pop(s);
				if (!b)
					printf("Popped Element: %d\n", t);
				break;

			case 4:
				if (isEmpty(s))
					printf("Stack is Empty.\n\n");
				else 
					printf("Stack is not Empty.\n\n");
				break;
					
			case 5:
				if (isFull(s))
					printf("Stack is Full.\n\n");
				else 
					printf("Stack is not Full.\n\n");
		}
	}
}
