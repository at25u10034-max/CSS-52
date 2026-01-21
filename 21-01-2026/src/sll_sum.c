#include <stdio.h>
#include <stdlib.h>

#define _IGNORE_MAIN
#include "sll.c"

int main() {
	struct Node *HEAD = NULL, *TAIL = NULL, *temp;
	create_list(&HEAD, &TAIL);

	int sum = 0; 
	temp = HEAD;
	while (temp) {
		sum += temp -> data;
		temp = temp -> next;
	}
	printf("Sum of Nodes: %d\n", sum);
}
