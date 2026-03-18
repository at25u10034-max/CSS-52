#include "../include/binarytree.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX(a,b) (a > b ? a : b) 

// Storage Method: We store in a breadth-first order, vis,
/*
			0
		   / \
	      /   \
	     1     2
	    / \   / \
	   3   4  5  6


	        0
		   / \
	      /   \
	     1     2
	          / \
	          5  6

	   [0 1 2 214... 214.. 5 6]

*/

void free_btree_node(BTreeNode* n) {
	if (n->left)
		free_btree_node(n->left);

	if (n->right)
		free_btree_node(n->left);

	free(n);
}

BTreeNode *create_btree_node (int val) {
	BTreeNode *btn = malloc(sizeof(BTreeNode));
	btn -> val = val;
	btn -> left = btn -> right = NULL;
	return btn;
}

BTreeNode *btree_fromarr(int *vals, int idx, int size) {
	if (idx >= size || vals[idx] == INT_MIN) return NULL;

	BTreeNode *t = create_btree_node(vals[idx]);
	printf("IDX: %d, VAL: %d\n", idx, vals[idx]);
	t->left = btree_fromarr(vals, 2 * idx + 1, size);
	t->right = btree_fromarr(vals, 2 * idx + 2, size);

	return t;
}

int size_btree(BTreeNode* ROOT) {
	if (ROOT == NULL) return 0;
	return 1 + size_btree(ROOT -> left) + size_btree(ROOT -> right);
}

int height(BTreeNode* ROOT) {
	if (!ROOT) return 0;

	int right_h = height(ROOT -> right);
	int left_h = height(ROOT -> left);

	return 1 + MAX(left_h, right_h);
}

// Very Inefficient way.
int *btree_toarr(BTreeNode *ROOT, int *arr, int idx) {
	if (!ROOT) return arr;

	if (!arr) arr = malloc(MAX_SIZE_BTREE * sizeof(int));
	arr[idx] = ROOT -> val;
	btree_toarr(ROOT -> left, arr, 2 * idx + 1);
	btree_toarr(ROOT -> right, arr, 2 * idx + 2);
	return arr;
}


int *inorder(BTreeNode *ROOT, int *arr, int *idx) {
	if (!ROOT) return arr;
	if (!arr) arr = malloc(size_btree(ROOT) * sizeof(int));
	if (!idx) idx = calloc(1, sizeof(int));

	inorder(ROOT -> left, arr, idx);
	arr[(*idx)++] = ROOT -> val;
	inorder(ROOT -> right, arr, idx);

	return arr;
}

int *preorder(BTreeNode *ROOT, int *arr, int *idx) {
	if (!ROOT) return arr;
	if (!arr) arr = malloc(size_btree(ROOT) * sizeof(int));
	if (!idx) idx = calloc(1, sizeof(int));

	arr[(*idx)++] = ROOT -> val;
	preorder(ROOT -> left, arr, idx);
	preorder(ROOT -> right, arr, idx);

	return arr;
}

int *postorder(BTreeNode *ROOT, int *arr, int *idx) {
	if (!ROOT) return arr;
	if (!arr) arr = malloc(size_btree(ROOT) * sizeof(int));
	if (!idx) idx = calloc(1, sizeof(int));

	postorder(ROOT -> left, arr, idx);
	postorder(ROOT -> right, arr, idx);
	arr[(*idx)++] = ROOT -> val;

	return arr;
}


void insert_bst(BTreeNode* ROOT, int val) {
	if (!ROOT) return;
	printf("At val: %d pushing val: %d\n", ROOT -> val, val);

	if (val < ROOT -> val) {
		if (ROOT -> left) return insert_bst(ROOT -> left, val);
		else {
			ROOT -> left = create_btree_node(val);
			return;
		}
	} else {
		if (ROOT -> right) return insert_bst(ROOT -> right, val);
		else {
			ROOT -> right = create_btree_node(val);
			return;
		}
	}
}


void set_leftchild(BTreeNode* n, int val) {
	if (n -> left)
		n -> left -> val = val;
	else 
		n -> left = create_btree_node(val);
}


void set_rightchild(BTreeNode* n, int val) {
	if (n -> right)
		n -> right -> val = val;
	else 
		n -> right = create_btree_node(val);
}
