#ifndef SORTS_H
#define SORTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct BSTNode {
	int value;
	struct BSTNode* left;
	struct BSTNode* right;
} BSTNode;

typedef struct BST{
	struct BSTNode* root;
	int size;
} BST;

void tree_sort_array(int* array, size_t size);
BST create_bst(const int* array, int size);
void empty_bst(BST* a_bst);

#endif /* SORTS_H */
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
