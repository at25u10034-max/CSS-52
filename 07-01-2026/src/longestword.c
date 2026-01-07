#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* longest_word(char* instr) {
	char* longstr = malloc(1);
	char* word = malloc(1024);
	int idx = 0, wlen = 0;
	char c = 1;

	*longstr = 0;
	while (c) {
		c = instr[idx++];
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			word[wlen++] = c;
		} else {
			if (strlen(word) > strlen(longstr)) {
				free(longstr);
				longstr = word;
				// printf("Longword: %s\n", longstr);
			} else {
				// printf("Shortword: %s, longstr: %s\n", word, longstr);
				free(word);
			}
			word = malloc(1024);
			wlen = 0;

		};
	}

	return longstr;
	
}

int main() {
	char* string = malloc(1024);

	printf("Enter string: ");
	fgets(string, 1024, stdin);

	printf("Longest Word: %s\n", longest_word(string));
	
	return 0;
}
