#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	int data;
	struct Node *next;	
};


struct Node *create_node() {
    int t;
    struct Node *temp = NULL;
    scanf("%d", &t);
    temp = malloc(sizeof(struct Node));
    if (!temp) {
        fprintf(stderr, "ERROR!! No space in RAM.");
    }
        
    temp -> data = t;
    temp -> next = NULL;
    return temp;
}


struct Node* create_list() {
	struct Node* HEAD = NULL, *temp = NULL, *new = NULL; 
	int n;
	printf("Enter Size: ");
	scanf("%d", &n);

	printf("Enter Data: ");
	for (int i = 0; i < n; i++) {
		new = create_node();
		if (!HEAD)
			HEAD = temp = new;
		temp -> next = new;
		new -> next = HEAD;
		temp = new;
	}

	return HEAD;
}


struct Node *insert_top(struct Node *HEAD, struct Node *new) {
	struct Node *temp = HEAD;
	while (temp -> next != HEAD) temp = temp -> next;
	temp -> next = new;
	new -> next = HEAD;
	HEAD = new;
	return HEAD;
}

struct Node *insert_bottom(struct Node *HEAD, struct Node *new) {
	struct Node *temp = HEAD;
	while (temp -> next != HEAD) temp = temp -> next;
	temp -> next = new;
	new -> next = HEAD;
	return HEAD;
}

struct Node *delete_top(struct Node *HEAD) {
	struct Node *temp = HEAD;
	while (temp -> next != HEAD) temp = temp -> next;

	if (temp == temp -> next) {
		free(HEAD);
		return NULL;
	}
	
	temp -> next = HEAD -> next;
	HEAD -> next = NULL;
	free(HEAD);
	HEAD = temp -> next;
	return HEAD;
}

struct Node *delete_bottom(struct Node *HEAD) {
	struct Node *temp = HEAD, *next;
	while (temp -> next -> next != HEAD) temp = temp -> next;

	if (temp == temp -> next) {
		free(HEAD);
		return NULL;
	}
	
	next = temp -> next;
	next->next = NULL;
	free(next);
	temp -> next = HEAD;
	return HEAD;
}

void display(struct Node *HEAD) {
	struct Node *temp = HEAD;

	if (!temp) {
		printf("NULL\n");
		return;
	}
	
	while (temp -> next != HEAD) {
		printf(" %d -> ", temp -> data);
		temp = temp -> next;
	}
	printf(" %d -> ", temp -> data);
	printf(" ^ (loop)\n");
}


const char* MESSAGE = "Enter Option:\n\
\n\t(1) Insert @ Top.\
\n\t(2) Insert @ Bottom.\
\n\t(3) Delete @ Top.\
\n\t(4) Delete @ Bottom.\
\n\t(5) Display Circular List.\n\
\n\t(0) Exit.\
\n\nOption: ";


int main () {
	struct Node *HEAD = create_list(), *temp;
	int n, flag = 1;

	while (flag) {
		printf("%s", MESSAGE);
		scanf("%d", &n);
		switch (n) {
			case 0:
				flag = 0;
				break;
			case 1:
				printf("Enter Data: ");
				temp = create_node();
				if (!HEAD) {
					HEAD = temp;
					HEAD -> next = HEAD;
				} else {
					HEAD = insert_top(HEAD, temp);
				}
				break;
				
			case 2:
				printf("Enter Data: ");
				temp = create_node();
				if (!HEAD) {
					HEAD = temp;
					HEAD -> next = HEAD;
				} else {
					insert_bottom(HEAD, temp);
				}
				break;

			case 3:
				if (!HEAD) {
					printf("Cannot Delete from Empty List.\n");
				} else {
					HEAD = delete_top(HEAD);
				}
				break;

			case 4:
				if (!HEAD) {
					printf("Cannot Delete from Empty List.\n");
				} else {
					HEAD = delete_bottom(HEAD);
				}
				break;
					
			case 5:
				display(HEAD);
				break;
		}
	}
}
