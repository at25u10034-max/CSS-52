#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stackll.c"





const char *MENU = "Select Operation:\n\
\n\t1. Push\
\n\t2. Pop\
\n\t3. Peek\
\n\t4. Display\
\n\t5. Exit\
\n\n\
Option: ";

int main() {
	int flag = 1;
	int opt, v;
	Stack *st = create_stack();
	while (flag) {
		printf("%s", MENU);
		scanf("%d", &opt);

		switch (opt) {
			case 1:
				printf("Enter Element: ");
				scanf("%d", &v);
				push(st, v);
				break;
			case 2:
				v = pop(st);
				if (v != INT_MIN) printf("Popped Value: %d\n\n", v);
				break;
			case 3:
				v = peek(st);
				if (v != INT_MIN) printf("Top Value: %d\n\n", v);
				break;
			case 4:
				printf("Stack: ");
				printstack(st);
				break;
			case 5:
				flag = 0;
				break;
						
		}
	}
}
