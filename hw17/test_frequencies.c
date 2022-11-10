#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "frequencies.h"
#include "miniunit.h"
#include "clog.h"

static void _assign_arr(Frequencies freq) {
	for(int i = 0; i < 256; i++){
		freq[i] = 0;
	}
}

static void _print(Frequencies freq) {
	for(int i = 0; i < 256; i++) {
		printf("%ld\n", freq[i]);
	}
}

static int _test_success(){
	mu_start();
	const char* a_error = "";
	Frequencies freq;
	_assign_arr(freq);
	calc_frequencies(freq, "test.txt", &a_error);
	_print(freq);
	mu_end();
}

static int _test_fail(){
	mu_start();
	const char* a_error = "";
	Frequencies freq;
	calc_frequencies(freq, "tert.txt", &a_error);
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test_success);
	mu_run(_test_fail);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
