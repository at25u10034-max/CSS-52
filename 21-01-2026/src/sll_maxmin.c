#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define _IGNORE_MAIN
#include "sll.c"

int main() {
	struct Node *HEAD = NULL, *TAIL = NULL, *temp;
	create_list(&HEAD, &TAIL);

	int max = HEAD -> data, min = HEAD -> data; 
	temp = HEAD;
	while (temp) {
		if (temp -> data > max)
			max = temp -> data;
		else if (temp -> data < min)
			min = temp -> data;
		temp = temp -> next;
	}
	printf("Max: %d\nMin: %d\n", max, min);
}
