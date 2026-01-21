#include <stdio.h>
#include <stdlib.h>

const char* MESSAGE = "Enter Option:\n\
\n\t(1) Insert Node at Beginning.\
\n\t(2) Insert Node at End.\
\n\t(3) Insert Node at Given Position.\
\n\t(4) Delete Node at End.\
\n\t(5) Delete Node at Given Position.\
\n\t(0) Exit.\
\n\nOption: ";

struct Node {
	int data;
	struct Node *next;	
};

struct Node *create();
void showlist(struct Node *HEAD);
void insert(struct Node *prev, struct Node *new);
struct Node *insert_end(struct Node *TAIL);
struct Node *insert_start(struct Node *HEAD);
struct Node *insert_pos(struct Node **HEAD, struct Node **TAIL, int size);

void gc(struct Node *HEAD);

struct Node *create() {
	int t;
	struct Node *temp = NULL;
	scanf("%d", &t);
	temp = malloc(sizeof(struct Node));
	temp -> data = t;
	temp -> next = NULL;
}

void insert(struct Node *prev, struct Node *new) {
	struct Node *next = prev -> next;
	prev -> next = new;
	new -> next = next; 
}

struct Node *insert_end(struct Node *TAIL) {
	struct Node *temp = create();
	insert(TAIL, temp);
	return temp;
}

struct Node *insert_start(struct Node *HEAD) {
	struct Node *temp = create();
	temp -> next = HEAD;
	return temp;
}

struct Node *insert_pos(struct Node **HEAD_P, struct Node **TAIL_P, int size) {
	struct Node *new, *temp, *next;
	int t;
	printf("Enter position: ");
	scanf("%d", &t);
	temp = *HEAD_P;

	if (t < 0) t += size + 1;
	while (t < 0) t += size;
	if (t <= 0) {
		printf("Enter data: ");
		*HEAD_P = insert_start(*HEAD_P);
		return *HEAD_P;
	}

	if (t == size) {
		printf("Enter data: ");
		*TAIL_P = insert_end(*TAIL_P);
		return *TAIL_P;
	}
	
	t--;
	while (t) {
		if (temp->next == NULL)
			break;
		temp = temp -> next;
		t--;
	}
	printf("Enter data: ");
	new = create();

	next = temp -> next;
	temp -> next = new;
	new -> next = next;
	
	return new;
}


void showlist (struct Node *HEAD) {
	while (HEAD) {
		printf ("%d -> ", HEAD -> data);
		HEAD = HEAD -> next;
	}
	printf("NULL\n");
}


int create_list(struct Node **HEAD_P, struct Node **TAIL_P) {
	int n;
	printf("Enter number of nodes: ");
	scanf("%d", &n);

	printf("Enter data: ");
	
	for (int i = 0; i < n; i++) {
		if (*TAIL_P)
			*TAIL_P = insert_end(*TAIL_P);
		else 
			*TAIL_P = *HEAD_P = create();		
	}
		
	printf("\n\n");
	printf("Linked List:\n");
	showlist(*HEAD_P);

	return n;
	
}


#ifndef _IGNORE_MAIN
int main() {
	int t;
	struct Node *HEAD = NULL, *TAIL = NULL;
	int size = create_list(&HEAD, &TAIL);
	
	int flag = 1;
	while (flag) {
		fputs(MESSAGE, stdout);
		scanf("%d", &t);

		switch (t) {
			case 0:
				gc(HEAD);
				flag = 0;
				break;
			case 1:
				printf("Enter data: ");
				HEAD = insert_start(HEAD);
				size++;
				showlist(HEAD);
				break;
			case 2:
				printf("Enter data: ");
				TAIL = insert_end(TAIL);
				size++;
				showlist(HEAD);
				break;
			case 3:
				insert_pos(&HEAD, &TAIL, size);
				size++;
				showlist(HEAD);
				break;


		}
	}
}

#endif



void gc (struct Node *HEAD) {
	if (HEAD -> next) 
		gc(HEAD -> next);

	free(HEAD);
}
