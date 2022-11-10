#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"

static struct BSTNode* newBST(int val) {
	BSTNode* x = malloc(sizeof(BSTNode));
	x -> value = val;
	x -> right = NULL;
	x -> left = NULL;
	return x;
}

static BSTNode*  _insert(int val, BSTNode* root) {
	if(root == NULL) {	
		return newBST(val);
	}

	else if(val < (root -> value)) {
		root -> left = _insert(val, root -> left);
	}
	else {
		root -> right = _insert(val, root -> right);
	}
	return root;
}

static void _destroy(BSTNode* root) {
	if(root != NULL) {
		_destroy(root -> left);
		_destroy(root -> right);
		free(root);
	}
	root = NULL;
}

static void _fill_array_from_bst(int* array, BSTNode* node, int* i) {
	if(node != NULL) {
		_fill_array_from_bst((array), (node -> left), i);
		*(array + (*i)) = node -> value;
		*i = *i + 1;
		_fill_array_from_bst((array), (node -> right), i);
	}
}


BST create_bst(const int* array, int size) {
	BST tree = {.root = NULL, .size = size};
	for(int i = 0; i < size; i++) {
		tree.root = _insert(*(array + i), (tree.root));
	}
	return tree;
}

void empty_bst(BST* bst) {
	_destroy(bst -> root);
}

void tree_sort_array(int* array, size_t size){
	BST tree = create_bst(array, (int) size);
	int i = 0;
	_fill_array_from_bst(array, tree.root, &i);
	empty_bst(&tree);
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
