#include "../../DataStructures/include/binarytree.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


#define MAX(a, b) (a > b ? a : b) 

// HELPERS
void printarr(int* arr, int size) {

	if (size == 0) {
		printf("[< empty >]");
		return;
	}
		
	printf("[");
	int i;
	for (i = 0; i < size - 1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d]", arr[i]);
}


int count_leaves(BTreeNode* ROOT) {
	if (!ROOT) return 0;
	if (!ROOT -> left && !ROOT->right) return 1;
	return count_leaves(ROOT -> left) + count_leaves(ROOT -> right);
}

void test_tree(BTreeNode* ROOT) {
	printf("Size of Tree: %d\n", size_btree(ROOT));
	printf("Height of Tree: %d\n", height(ROOT));
	printf("Number of Leaves: %d\n", count_leaves(ROOT));

	int n = size_btree(ROOT);
	printf("Inorder:"); printarr(inorder(ROOT, NULL, NULL), n); printf("\n");
	printf("Preorder:"); printarr(preorder(ROOT, NULL, NULL), n); printf("\n");
	printf("Postorder:"); printarr(postorder(ROOT, NULL, NULL), n); printf("\n");
}



int main() {
	int n, t, *arr;
	printf("Enter Number of nodes: ");
	scanf("%d", &n);

	arr = malloc(MAX_SIZE_BTREE * sizeof(int));
	for (int i = 0; i < MAX_SIZE_BTREE; i++) arr[i] = INT_MIN;
	printf("Enter Elements: ");
	for (int i = 0; i < n; i++) 
		scanf("%d", &arr[i]);

	test_tree(btree_fromarr(arr, 0, n));

	printf("Enter Number of nodes of BST: ");
	scanf("%d", &n);
	printf("Enter ROOT Element: ");
	scanf("%d", &t);
	BTreeNode* BST = create_btree_node(t);

	for (int i = 0; i < n - 1; i++) {
		printf("Enter: ");
		scanf("%d", &t);
		insert_bst(BST, t);
	}

	test_tree(BST);
	return 0;
}

