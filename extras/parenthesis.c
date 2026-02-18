#define __incl_paren

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.c"

char pairof(char p) {
	switch (p) {
		case ')' : return '(';
		case ']' : return '[';
		case '}' : return '{';

		default: return 0;
	}
}

int is_closer (char p) {
	switch (p) {
		case ')':
		case ']':
		case '}':
			return 1;

		default:
			return 0;
	}
}

int is_opener (char p) {
	switch (p) {
		case '(':
		case '[':
		case '{':
			return 1;

		default:
			return 0;
	}
}

int is_balanced(const char* expr) {
	printf("Checking Balanced status of %s.", expr);
	size_t l = strlen(expr);
	stack *st = create_stack(l);
	for (size_t i = 0; i < l; i++) {
		char c = expr[i];
		if (is_closer(c)) {
			if(is_empty(st) || peek(st) != pairof(c)) return 0;
			pop(st);
		}

		if (is_opener(c)) push(st, c);
		
	}

	return is_empty(st);
	
};