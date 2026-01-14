#include <stdlib.h>
#include <string.h>

#define __main__
#include "bsort_gen.c"
#define N_STR 4

char *strs[4] = {
	"banana",
	"apple",
	"grape",
	"mango"
};

int comp(void* e1, void* e2) {
	char* c1 = (char*) e1;
	char* c2 = (char*) e2;

	return strcmp(c1, c2);
} 

int main() {
	
	char **pointerarr = malloc(sizeof(char*) * 4);
	pointerarr[0] = strs[0];
	pointerarr[1] = strs[1];
	pointerarr[2] = strs[2];
	pointerarr[3] = strs[3];
	 
	bsort(N_STR, (void**) pointerarr, comp);

	for (int i = 0; i < N_STR; i++) {
		printf("%s\n", pointerarr[i]);
	}
}
