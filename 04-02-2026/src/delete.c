#include <stdlib.h>
#include <stdio.h>
#define stdinc
#include "dll.c"

int main () {
	struct DLL dll = create_dll();
	struct DLL_Node *n = dll.HEAD;

	int key;
	printf("Enter Key: ");
	scanf("%d", &key);

	while (n-> data != key)  {
		n = n -> next;

		if (!n) {
			printf("Not found.");
			return -1;
		}
	}

	// Edge cases: IT is HEAD or TAIL
	if (!n->prev) {
		n = dll.HEAD;
		dll.HEAD = dll.HEAD -> next;
		dll.HEAD -> prev = NULL;
		n -> next = n -> prev = NULL;
		free(n);
		display (dll.HEAD);
		return 0;
	}

	if (!n->next) {
		n = dll.TAIL;
		dll.TAIL = dll.TAIL -> prev;
		dll.TAIL -> next = NULL;
		n -> next = n -> prev = NULL;
		free(n);
		display (dll.HEAD);
		return 0;
	}
	
	n -> prev -> next = n -> next;
	n -> next -> prev = n -> prev;
	n -> next = n -> prev= NULL;
	free(n);
	display(dll.HEAD);

	return 0;
}
