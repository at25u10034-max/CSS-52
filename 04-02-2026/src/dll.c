
#ifndef stdinc
	#define stdinc
	#include <stdio.h>
	#include <stdlib.h>
#endif
	
struct DLL_Node {
	int data;
	struct DLL_Node *prev;
	struct DLL_Node *next;
};

struct DLL {
	struct DLL_Node *HEAD;
	struct DLL_Node *TAIL;
	int size;
};


struct DLL_Node *create_node() {
	struct DLL_Node *n = malloc(sizeof(struct DLL_Node));
	scanf("%d", &n->data);
	n->next = n->prev = NULL;
	return n;
}

struct DLL_Node *append(struct DLL* dll) {
	struct DLL_Node *new = create_node();
	dll->TAIL -> next = new;
	new -> prev = dll->TAIL;
	return new;
} 


struct DLL create_dll() {
	struct DLL dll = {};
	int size;
	printf("Enter size of Data: ");
	scanf("%d", &size);
	dll.size = size;

	printf("Enter Data: ");
	for (int i = 0; i < size; i++) {
		if (!dll.HEAD)
			dll.HEAD = dll.TAIL = create_node();
		else
			dll.TAIL = append(&dll);
	}

	return dll;
}

int display (struct DLL_Node *HEAD) {
	if (!HEAD)
		return printf("NULL\n") * 0;
		
	struct DLL_Node* temp = HEAD;
	printf("NULL ->");
	
	while (temp -> next) {
		printf(" %d <->", temp -> data);
		temp = temp -> next;

	}

	printf(" %d -> NULL\n", temp-> data);
	return 0;
}
