#ifndef BTREE_H
#define BTREE_H

#define MAX_SIZE_BTREE 16384

typedef struct BTreeNode {
	int val;
	struct BTreeNode *left;
	struct BTreeNode *right;
	struct BTreeNode *parent;
	
} BTreeNode;

BTreeNode *btree_fromarr(int*, int idx, int size);
BTreeNode *create_btree_node(int val);
void free_btree_node(BTreeNode*);

void set_leftchild(BTreeNode*, int);
void set_rightchild(BTreeNode*, int);

int size_btree(BTreeNode*);
int height(BTreeNode*);
int *btree_toarr(BTreeNode*, int*, int idx);

int *inorder(BTreeNode*, int*, int *idx);
int *preorder(BTreeNode*, int*, int *idx);
int *postorder(BTreeNode*, int*, int *idx);

void insert_bst(BTreeNode*, int);

#endif
