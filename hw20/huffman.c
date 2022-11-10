#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"

int _comp_tree(const void* node1, const void* node2) {
	if((((TreeNode*)node1) -> frequency) == (((TreeNode*)node2) -> frequency)) {
		if(((TreeNode*)(node2)) -> character != '\0') {
			return (((const TreeNode*)node1) -> character) - (((const TreeNode*)node2) -> character);
		}
		else {
			return 0;
		}
	}
	else {
		return (int)(((const TreeNode*)node1) -> frequency) - (int)(((const TreeNode*)node2) -> frequency);
	}
}

Node* make_huffman_pq(Frequencies freqs) {
	Node* head = NULL;
	for(int i = 0; i < 256; i++) {
		if(freqs[i] > 0 && (i != 10)) {
			TreeNode* tree = malloc(sizeof(*tree));
			*tree = (TreeNode) {.character = (uchar) i, .frequency = freqs[i], .left = NULL, .right = NULL};
			pq_enqueue(&head, tree, _comp_tree);
		}
	}
	return head;
}

TreeNode* make_huffman_tree(Node* head) {
	if(head ==  NULL){
		return NULL;
	}
	else {
		while((head -> next) !=  NULL) {
			TreeNode* tree = malloc(sizeof(*tree));
			Node* left = pq_dequeue(&head);
			Node* right = pq_dequeue(&head);
			*tree = (TreeNode) {.character = (uchar)0, .frequency = (((TreeNode*)(left -> a_value)) -> frequency) + (((TreeNode*)((right) -> a_value)) -> frequency), .left = left -> a_value, .right = right -> a_value};
			pq_enqueue(&head, tree, _comp_tree);
			free(left);
			free(right);
		}
		TreeNode* tree_head = head -> a_value;
		free(pq_dequeue(&head));
		return tree_head;
	}
}

void destroy_huffman_tree(TreeNode** a_root){
	if(*a_root != NULL) {
		destroy_huffman_tree(&((*a_root) -> left));
		destroy_huffman_tree(&((*a_root) -> right));
		free(*a_root);
	}
	*a_root = NULL;
}

void write_coding_table(TreeNode* root, BitWriter* a_writer) {
	if(root != NULL) {
		write_coding_table(root -> left, a_writer);
		write_coding_table(root -> right, a_writer);
		if(root -> character == (uchar)0) {
			//fputc('0', a_writer -> file);
			//fputc(' ', a_writer -> file);
			write_bits(a_writer, 0x00, 1);
		}
		else {
			//fputc('1', a_writer -> file);
			//fputc(' ', a_writer -> file);
			write_bits(a_writer, 0x01, 1);
			write_bits(a_writer, (uchar)root -> character, 8);
		}
	}
}


/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
