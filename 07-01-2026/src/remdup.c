#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* remdup(char* instr) {
	char* outstr = malloc(1024);
	int map[256] = {0}; 
	int idx = 0, idxo = 0;
	char c = 1;

	while (c) {
		c = instr[idx++];
		if (!map[(int) c]) {
			map[(int) c]++;
			outstr[idxo++] = c;
		};
	}

	return outstr;
	
}

int main() {
	char* string = malloc(1024);

	printf("Enter string: ");
	fgets(string, 1024, stdin);

	printf("Non duplicate string: %s\n", remdup(string));
	
	return 0;
}
