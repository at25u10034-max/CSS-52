#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool palin(char* instr) {
	int len = strlen(instr);
	int lastidx = len - 1;
	int firstidx = 0;
	char first, last;
	
	while (lastidx != firstidx && firstidx < len && lastidx >= 0) {
		while ((first = instr[firstidx]) == ' ' || last == '\n')
			firstidx++;

		while ((last = instr[lastidx]) == ' ' || last == '\n')
			lastidx--;

		last = tolower(last);
		first = tolower(first);
		// printf("LAST: %c; FIRST: %c;", last, first);
		if (last != first) 
			return false;
			
		firstidx++;
		lastidx--;
	} 

	return true;
}

int main() {
	char* string1 = malloc(1024);
	
	printf("Enter string: ");
	
	fgets(string1, 1024, stdin);
	
	if (palin(string1))
		printf("\n\nPalindrome.");
	else
		printf("\n\nNOT Palindrome.");
		
	return 0;
}
