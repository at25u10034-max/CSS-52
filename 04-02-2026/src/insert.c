#include <stdlib.h>
#include <stdio.h>
#define stdinc
#include "dll.c"

int main () {
	struct DLL dll = create_dll();
	int pos;
	printf("Enter Position: ");
	
	scanf("%d", &pos);
	struct DLL_Node* temp = dll.HEAD, *new;

	// Edge cases: size = 0 and size = 1, insert at 0; insert at last;
	printf("Size of DLL: %d\n", dll.size);
	
	if (dll.size == 0) {
		if (pos == 0) {
			printf("Enter data:");
			dll.HEAD = dll.TAIL = create_node();
			display(dll.HEAD);
			return 0;
		} else {
			printf("Index out of range.");
			return 1;	
		}
	}

	if (dll.size == 1) {
		if (pos == 1) {
			printf("Enter data:");
			dll.TAIL = create_node();
			dll.HEAD->next = dll.TAIL;
			dll.TAIL -> prev = dll.HEAD;
			dll.size++;
			display(dll.HEAD);
			return 0;
		} else if (pos == 0) {
			printf("Enter data:");
			dll.HEAD = create_node();
			dll.HEAD->next = dll.TAIL;
			dll.TAIL->prev = dll.HEAD;
			dll.size++;
			display(dll.HEAD);
			return 0;
		} else {
			printf("Index out of range.");
			return 1;
		}	
	}

	if (pos == 0) {
		printf("Enter data:");
		new = create_node();
		new -> next = dll.HEAD;
		dll.HEAD -> prev = new;
		dll.HEAD = new;
		dll.size++;
		display(dll.HEAD);
		return 0;
	}

	if (pos == dll.size) {
		printf("Enter data:");
		new = create_node();
		new -> prev = dll.TAIL;
		dll.TAIL -> next = new;
		dll.TAIL = new;
		dll.size++;
		display(dll.HEAD);
		return 0;
	}

	pos--;
	while (pos-- && temp->next)
		temp = temp -> next;
	
	if (!temp->next && pos != 0) {
		return printf("Index out of range"), 1;
	}

	printf("Enter data:");
	new = create_node();

	new -> next = temp -> next;
	new -> prev = temp;
	temp -> next = new;
	display (dll.HEAD);
}
