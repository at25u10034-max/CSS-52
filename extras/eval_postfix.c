#include <limits.h>
#include <string.h>
#include <stdio.h>

#include "stack.c"

int isop(char c){
	switch (c) {
		case '+': case '-' : case '*': case '/':
			return 1;
		default:
			return 0;
	}
}

int apply(char op, int a, int b){
	switch (op) {
		case '+': 
			return a + b;
		case '-' : 
			return a - b;
		case '*': 
			return a * b;
		case '/':
			if (b == 0) return INT_MIN;
			return a / b;
		default:
			return INT_MIN;
	}
}

int evaluate_postfix(const char * expr){
	printf("Evaluating %s\n", expr);
	size_t l = strlen(expr);
	stack *st = create_stack(l);
	int a, b, t;
	
	for (size_t i = 0; i < l; i++) {
		char c = expr[i];
		if (c >= '0' && c <= '9') {
			push(st, c - '0');
			printf("Pushed: %d\n", c - '0');
		}

		if (isop(c)) {
			if (is_empty(st)) return INT_MIN;
			a = pop(st);
			if (is_empty(st)) return INT_MIN;
			b = pop(st);
			t = apply(c, b, a);
			if (t == INT_MIN) return INT_MIN;

			printf("Pushed: %d %c %d = %d\n", b, c, a, t);
			push(st, t);
		}
	}

	if (is_empty(st)) return INT_MIN;
	printstack(st);
	a = pop(st);
	if (!is_empty(st)) return INT_MIN;
	printf("Value: %d\n", a);
	return a;
}