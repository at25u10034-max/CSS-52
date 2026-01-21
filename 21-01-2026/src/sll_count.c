#include <stdio.h>
#include <stdlib.h>

#define _IGNORE_MAIN
#include "sll.c"

int main() {
	struct Node *HEAD = NULL, *TAIL = NULL, *temp;
	create_list(&HEAD, &TAIL);

	int count = 0; 
	temp = HEAD;
	while (temp) {
		count++;
		temp = temp -> next;
	}
	printf("Number of Nodes: %d\n", count);
}
