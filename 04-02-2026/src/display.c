#include <stdlib.h>
#include <stdio.h>
#define stdinc
#include "dll.c"

int main () {
	struct DLL dll = create_dll();
	display(dll.HEAD);
}
