#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"


static void _print_array(int* arr, int size) {
	for(int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}




int main(int argc, char* argv[]) {
	BST test = create_bst((int[]) {1 ,2, 3, 4}, 4);
	assert(test.root -> value == 1);
	empty_bst(&test);

	
	int array[] = {-2, -5, 678887, 46};
	size_t size = sizeof(array) / sizeof(*array);
	tree_sort_array(array, size);
	_print_array(array, size);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */


