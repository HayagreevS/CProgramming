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
	int array[] = {4, 3, 2, 1};
	size_t size = sizeof(array) / sizeof(*array);
	quick_sort_array(array, size);
	_print_array(array, size);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */


