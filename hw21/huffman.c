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

void _instant(table tab) {
	for(int i = 0; i < 256; i++) {
		tab[i].bits = 0x00;
		tab[i].num_bits = 0;
	}
}

/*
void _print_bits(uint8_t byte) {
	for(int i = 8; i > 0; i--) {
		printf("%d", (byte >> (i - 1)) & (0xff >> 7));
	}
}

void _print_tab(table tab) {
	for(int i = 0; i < 256; i++) {
		printf("\nTABLE CHAR %c TABLE BITS:", (uchar) i);
		_print_bits(tab[i].bits);
		printf("\n TABLE LEN: %d\n", tab[i].num_bits);
	}
}
*/

void write_path(TreeNode* root, BitWriter* a_writer, uint8_t code, int len, table tab) {	
	if (root != NULL) {
		write_path(root -> left, a_writer, (code << 1), len + 1, tab);
		write_path(root -> right, a_writer, (code << 01) | 0x01, len + 1, tab);
		if(root -> character != (uchar) 0) {
			tab[(uchar)root -> character].bits = code;
			tab[(uchar)root -> character].num_bits = len - 1;
		}
	}
}

void write_compressed(TreeNode* root, BitWriter* a_writer, uint8_t* uncompressed_bytes) {
    table tab;
	_instant(tab);
	write_path(root, a_writer, 0x00, 1, tab);
	for(int i = 0; uncompressed_bytes[i] != '\0'; i++) {
		//printf("\nCHAR: %c BIT:", uncompressed_bytes[i]);
		//_print_bits(tab[(uchar)uncompressed_bytes[i]].bits);
		//printf(" LEN: %d\n", tab[(uchar)uncompressed_bytes[i]].num_bits);
		write_bits(a_writer, tab[(uchar)uncompressed_bytes[i]].bits, tab[(uchar)uncompressed_bytes[i]].num_bits);
	}
	//_print_tab(tab);
}


/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
