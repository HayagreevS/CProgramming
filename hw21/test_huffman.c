#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"
#include "miniunit.h"
#include "clog.h"

void _make_freq(Frequencies freq) {
	for(int i = 0; i < 256; i++) {
		freq[i] = 0;
	}
}

/*void _print_freq(Frequencies freq) {
	for(int i = 0; i < 256; i++) {
		printf("%ld", freq[i]);
	}
}*/

uint8_t* _content(const char* path){
	FILE* file;
	if((file = fopen(path, "r")) != NULL) {
		fseek(file, 0L, SEEK_END);
		int len = ftell(file);
		fseek(file, 0L, SEEK_SET);
		uint8_t* input = malloc(sizeof(input) * len);
		int i = 0;
		for(uchar c = fgetc(file); !feof(file); c = (uchar) fgetc(file)) {
			input[i] = c;
			i++;
		}
		return input;
	}
	else {
		return NULL;
	}
}

void _destroy(void* tree) {
	free((TreeNode*)tree);
}

void _print_tree(TreeNode* tree) {
	if(tree != NULL) {
		_print_tree(tree -> left);
		_print_tree(tree -> right);
		printf("\nTree: %c, Frequency: %ld\n", (tree -> character), tree -> frequency);
	}
}

int _test_huffman() {
	mu_start();
	Frequencies freq;
	_make_freq(freq);
	const char* error;
	calc_frequencies(freq, "input.txt", &error);
	//_print_freq(freq);
	Node* head = NULL;
	head = make_huffman_pq(freq);
	for(Node* curr = head; curr != NULL; curr = curr -> next) {
		printf("\nQueue: %c, Freq:%ld\n", (char)(((TreeNode*)(curr -> a_value)) ->  character), ((TreeNode*)(curr -> a_value)) -> frequency);
	}
	TreeNode* tree_head = make_huffman_tree(head);
	_print_tree(tree_head);
	BitWriter writer = open_bit_writer("output.txt");
	//write_coding_table(tree_head, &writer);
	uint8_t* input = _content("input.txt");
	write_compressed(tree_head, &writer, input);
	destroy_huffman_tree(&tree_head);
	close_bit_writer(&writer);
	free(input);
	mu_end();
}

int _test_huffman_2() {
	mu_start();
	Node* head = NULL;
	TreeNode* tree_head = make_huffman_tree(head);
	_print_tree(tree_head);
	mu_end();
}

int _test_huffman_3() {
	mu_start();
	Frequencies freq;
	_make_freq(freq);
	const char* error;
	calc_frequencies(freq, "input.txt", &error);
	//_print_freq(freq);
	Node* head = NULL;
	head = make_huffman_pq(freq);
	for(Node* curr = head; curr != NULL; curr = curr -> next) {
		printf("\nQueue: %c, Freq:%ld\n", (char)(((TreeNode*)(curr -> a_value)) ->  character), ((TreeNode*)(curr -> a_value)) -> frequency);
	}
	TreeNode* tree_head = make_huffman_tree(head);
	_print_tree(tree_head);
	BitWriter writer = open_bit_writer("output2.txt");
	write_coding_table(tree_head, &writer);
	//uint8_t* input = _content("input.txt");
	//write_compressed(tree_head, &writer, input);
	destroy_huffman_tree(&tree_head);
	close_bit_writer(&writer);
	//free(input);
	mu_end();

}
int main(int argc, char* argv[]) {
	mu_run(_test_huffman);
	mu_run(_test_huffman_2);
	mu_run(_test_huffman_3);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
