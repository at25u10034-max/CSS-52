#include <stdlib.h>
#include <stdio.h>
#define stdinc
#include "dll.c"

int main () {
	struct DLL dll = create_dll();
	struct DLL_Node *p1 = dll.HEAD, *p2 = dll.TAIL;
	int flag = 1;
	
	while (p1 && p2 && p1 -> prev != p2 && p1 != p2) {
		if (p1 -> data != p2 -> data) {
			flag = 0;
			break;
		}
		p1 = p1 -> next;
		p2 = p2 -> prev;
	}

	if (flag) {
		printf("It is a Palindrome.\n");
	} else {
		printf("It is not a Palindrome.\n");
	}
}
