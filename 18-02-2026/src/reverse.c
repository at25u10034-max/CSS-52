#include "sll.c"
#include "stacknode.c"


int main () {
	size_t n;
	Node *HEAD = NULL;

	Stack* st = create_stack();
	
	printf("Enter Size:");
	scanf("%zu", &n);
	printf("Enter Elements: ");

	for (size_t i = 0; i < n; i++) {
		HEAD = insert_end(HEAD);
		printf("HEAD: %d\n", HEAD -> data);
		showlist(HEAD);
	}

	printf("Original List: ");
	showlist(HEAD);

	Node *t = HEAD, *tt;
	if (!t) {
		printf("Reversed List: ");
		showlist(HEAD);
		return 0;
	}
	
	while (t && t -> next) {
		push(st, t);
		t = t -> next;
	}

	HEAD = t;
	while (!is_empty(st)) {
		tt = pop(st);
		t -> next = tt;
		t = tt;
		tt -> next = NULL;
	}

	printf("Reversed List: ");
	showlist(HEAD);
	return 0;
	
}
