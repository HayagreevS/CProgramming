#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"

int _comp_tree(const void* node1, const void* node2) {
	if((((TreeNode*)node1) -> frequency) == (((TreeNode*)node2) -> frequency)) {
		return (((const TreeNode*)node1) -> character) - (((const TreeNode*)node2) -> character);
	}
	else {
		return (int)(((const TreeNode*)node1) -> frequency) - (int)(((const TreeNode*)node2) -> frequency);
	}
}

Node* make_huffman_pq(Frequencies freqs) {
	Node* head = NULL;
	for(int i = 0; i < 256; i++) {
		if(freqs[i] > 0) {
			TreeNode* tree = malloc(sizeof(*tree));
			*tree = (TreeNode) {.character = (uchar) i, .frequency = freqs[i], .left = NULL, .right = NULL};
			pq_enqueue(&head, tree, _comp_tree);
		}
	}
	return head;
}






/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
