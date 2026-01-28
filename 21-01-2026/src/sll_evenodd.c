#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define _IGNORE_MAIN
#include "sll.c"

int main() {
	struct Node *HEAD = NULL, *TAIL = NULL, *temp;
	create_list(&HEAD, &TAIL);

	int even = 0, odd = 0;
	temp = HEAD;
	while (temp) {
		if (temp -> data % 2)
			even++;
		else 
			odd++;
		temp = temp -> next;
	}
	printf("Even: %d nos.\nOdd: %d nos.\n", even, odd);
}
