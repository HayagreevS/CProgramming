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

void _destroy(void* tree) {
	free((TreeNode*)tree);
}

int _test_huffman() {
	mu_start();
	Frequencies freq;
	_make_freq(freq);
	const char* error;
	calc_frequencies(freq, "test.txt", &error);
	//_print_freq(freq);
	Node* head = NULL;
	head = make_huffman_pq(freq);
	for(Node* curr = head; curr != NULL; curr = curr -> next) {
		printf("\nQueue1: %c\n", (char)(((TreeNode*)(curr -> a_value)) ->  character));
	}
	destroy_list(&head, _destroy);
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test_huffman);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
