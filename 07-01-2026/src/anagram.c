#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool ana(char* string1, char* string2) {
	int map[256] = {0}; 
	int idx = 0;
	char c = 1;
	
	while (c) {
		c = string1[idx++];
		map[(int) c]++; 
	}

	idx = 0;
	c = 1;
	while (c) {
		c = string2[idx++];
		map[(int) c]--; 
	}

	for (size_t i = 0; i < 256; i++)
		if (map[i])
			return false;

	return true;
}

int main() {
	char* string1 = malloc(1024);
	char* string2 = malloc(1024);

	printf("Enter string 1: ");
	fgets(string1, 1024, stdin);

	printf("Enter string 2: ");
	fgets(string2, 1024, stdin);

	if (ana(string1, string2))
		printf("\n\nAnagrams.");
	else
		printf("\n\nNOT Anagrams.");
		
	return 0;
}
