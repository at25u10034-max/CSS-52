#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *next;	
};

// Prototypes
struct Node *create();
void showlist(struct Node*);
void insert(struct Node *prev, struct Node *new);
struct Node *insert_start(struct Node*);
struct Node *insert_end(struct Node*);
struct Node *insert_pos(struct Node**, struct Node**, int size);
struct Node *insert_after(struct Node*, int);
struct Node *delete_start(struct Node*);
struct Node *delete_end(struct Node*);
struct Node *delete_pos(struct Node**, struct Node**, int size);

void gc(struct Node *HEAD);

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


void showlist_r (struct Node *n) {
	if (n) {
		showlist_r (n->next);
		printf("%d \n", n -> data);
	} else
		printf("(null)\n");
}


// Insertion Functions

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

struct Node *insert_after(struct Node *n, int val) {
	if (!n) {
		fprintf(stderr, "Empty List cannot be searched.");
		return NULL;
	}
		
	struct Node *new, *next;
	while (n -> data != val) {
		if (!n->next) {
			fprintf(stderr, "Not found.\n");
			return NULL;
		}
		n = n -> next;
	}
	printf("Enter data: ");
	new = create();
	next = n->next;
	n -> next = new;
	new -> next = next;

	return new;
}

struct Node *insert_pos(struct Node **HEAD_P, struct Node **TAIL_P, int size) {
	struct Node *new, *temp, *next;
	int t;
	printf("Enter position: ");
	scanf("%d", &t);
	temp = *HEAD_P;


	if (t == size || t == -1) {
		printf("Enter data: ");
		*TAIL_P = insert_end(*TAIL_P);
		if (size == 0)
			*HEAD_P = *TAIL_P;
		return *TAIL_P;
	}

	if (t < 0) 
		t += size + 1;

	if (t == 0) {
		printf("Enter data: ");
		*HEAD_P = insert_start(*HEAD_P);
		
		if (size == 0)
			*TAIL_P = *HEAD_P;
			
		return *HEAD_P;
	}
	
	t--;
	while (t) {
		if (temp->next == NULL) {
			fprintf(stderr, "Index Out of Range.\n");
			return NULL;
		}
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


// Deletion Functions
struct Node *delete_start(struct Node *n) {
	if (!n)
		return NULL;

	if (!n->next) {
		free(n);
		return NULL;
	}
		
	struct Node *next = n->next;
	n -> next = NULL;
	free(n);
	return next;
}

struct Node *delete_end(struct Node *HEAD) {
	struct Node *n = HEAD;
	if (!n) 
		return NULL;

	if(!n->next) {
		free(n);
		return NULL;
	}
	
	while (n->next && n -> next -> next) {
		n = n->next;
	}
	free(n -> next);
	n -> next = NULL;
	return n;
}


struct Node *delete_pos(struct Node **HEAD_P, struct Node **TAIL_P, int size) {
	struct Node *prev, *next;
	int t;
	printf("Enter position: ");
	scanf("%d", &t);
	prev = *HEAD_P;


	if (t < 0) 
		t += size;

	if (t == 0) {
		*HEAD_P = delete_start(*HEAD_P);
		return *HEAD_P;
	}

	if (t == size - 1) {
		*TAIL_P = delete_end(*TAIL_P);
		return *TAIL_P;
	}
	
	t--;
	while (t) {
		if (prev->next == NULL) {
			fprintf(stderr, "Index Out of Range.\n");
			return NULL;
		}
		prev = prev -> next;
		t--;
	}

	next = prev -> next;
	if (next) {
		prev -> next = prev -> next -> next;
		free(next);
	} else
		fprintf(stderr, "Index out of Range.\n");
	return NULL;
}



// Program Flow Functions

int create_list(struct Node **HEAD_P, struct Node **TAIL_P) {
	int n;
	printf("Enter number of nodes: ");
	scanf("%d", &n);

	if (n) printf("Enter data: ");	
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

void gc (struct Node *n) {
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


#ifndef _IGNORE_MAIN

const char* MESSAGE = "Enter Option:\n\
\n\t(1) Insert Node at Beginning.\
\n\t(2) Insert Node at End.\
\n\t(3) Insert Node at Given Position.\
\n\t(4) Insert Node after Given Value.\
\n\t(5) Delete Node at Beginning.\
\n\t(6) Delete Node at End.\
\n\t(7) Delete Node at Given Position.\
\n\t(8) Show elements in reverse order.\
\n\t(0) Exit.\
\n\nOption: ";

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
				if (size == 0)
					HEAD = TAIL = create();
				else
					HEAD = insert_start(HEAD);
				size++;
				if (size == 1)
					TAIL = HEAD;
				showlist(HEAD);
				break;
				
			case 2:
				printf("Enter data: ");
				if (size == 0) 
					HEAD = TAIL = create();
				else
					TAIL = insert_end(TAIL);
				size++;
				showlist(HEAD);
				break;
				
			case 3:
				if (size == 0) {
					printf("Empty List. Enter HEAD Data: ");
					HEAD = TAIL = create();
				} else
					insert_pos(&HEAD, &TAIL, size);
				size++;
				showlist(HEAD);
				break;

			case 4:
				printf("Insert After: ");
				scanf("%d", &t);
				insert_after(HEAD, t);
				showlist(HEAD);
				break;

			case 5:
				HEAD = delete_start(HEAD);
				if (HEAD == NULL)
					TAIL = NULL;
				if (size) size--;
				showlist(HEAD);
				break;

			case 6:
				TAIL = delete_end(HEAD);
				if (TAIL == NULL)
					HEAD = NULL;
				if (size) size--;
				showlist(HEAD);
				break;

			case 7:
				delete_pos(&HEAD, &TAIL, size);
				if (TAIL == NULL || HEAD == NULL) {
					HEAD = NULL;
					TAIL = NULL;
				}
				if (size) size--;
				showlist(HEAD);
				break;

			case 8:
				showlist_r(HEAD);
				break;


		}
	}
}

#endif



