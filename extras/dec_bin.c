#include <math.h>
#include "stack.c"

char *dec_bin(int dec) {
	if (dec == 0) return "0";
	size_t bits = log2(dec) + 1;
	stack *st = create_stack(bits);
	char *bin = malloc(bits + 1);

	if (!bin)
		printf("Ded, %zu \n", bits);
	int i = 0;
	while (dec) {
		push(st, dec % 2);
		dec /= 2;
	}

	while (!is_empty(st))
		bin[i++] = pop(st) + '0';

	printf("%s\n", bin);
	bin[bits] = '\0';
	return bin;
}