#include <stdlib.h>
#include <stdio.h>
#define stdinc
#include "dll.c"


int display_r (struct DLL_Node *TAIL) {
	if (!TAIL)
		return printf("NULL\n") * 0;
		
	struct DLL_Node* temp = TAIL;
	printf("NULL <-");
	
	while (temp -> prev) {
		printf(" %d <->", temp -> data);
		temp = temp -> prev;

	}

	printf(" %d <- NULL\n", temp-> data);
	return 0;
}


int main () {
	struct DLL dll = create_dll();
	display(dll.HEAD);
	display_r(dll.TAIL);
}
