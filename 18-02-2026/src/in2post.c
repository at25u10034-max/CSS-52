#include <string.h>
#include "stackll.c"

int prece(char c) {
	switch (c) {
		case '+': 
			return 1;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;

		default:
			return 0;
		}
}

char *infix_to_postfix(const char* infix) {
	size_t l = strlen(infix);
	size_t idx = 0;
	char *postfix = malloc(l + 1);
	Stack *st = create_stack(l);

	for (size_t i = 0; i < l; i++) {
		char c = infix[i];
		if (c == '(') {
			push(st, c);
		} else if (c == ')') {
			while (!is_empty(st) && peek(st) != '(')
				postfix[idx++] = pop(st);
			pop(st); // The actual (
				
		} else if (prece(c)) {
			while (!is_empty(st) && prece(c) - prece(peek(st)) <= 0) {
				postfix[idx++] = pop(st);
			}
			push(st, c);
			
		} else {
			postfix[idx++] = c;
		}
	}

	while (!is_empty(st))
		postfix[idx++] = pop(st);
		

	postfix[idx++] = 0;
	postfix = realloc(postfix, idx);

	printf("Infix: %s\nPostfix: %s\n\n\n", infix, postfix);
	free_stack(st);
	
	return postfix;
	
}
