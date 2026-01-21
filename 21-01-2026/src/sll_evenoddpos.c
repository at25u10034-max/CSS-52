#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define _IGNORE_MAIN
#include "sll.c"

int main() {
	struct Node *HEAD = NULL, *TAIL = NULL, *temp;
	create_list(&HEAD, &TAIL);


	temp = HEAD;
	printf("ODD Elements:");
	
	while (temp) {
		printf("%d ", temp -> data);
		if (!temp -> next)
			break;
		temp = temp -> next -> next;
	}

	printf("\nEVEN Elements:");
	if (HEAD) {
		
		temp = HEAD -> next;
		while (temp && temp -> next) {
			printf("%d ", temp -> data);
			temp = temp -> next -> next;
		}
	}

	
}
