#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miniunit.h"
#include "smintf.h"

int test_basic();

int main(int argc, char* argv[]) {
	mu_run(test_basic);	
	char* actual = smintf("%$", 100);
	fputs(actual, stdout);
	free(actual);
	return EXIT_SUCCESS;
}

int test_basic() {
	mu_start();
	mu_check_smintf("", "", 10);
	mu_check_smintf("test", "%s", "test");
	mu_check_smintf("10", "%d", 10);
	mu_check_smintf("$1.00", "%$", 100);
	mu_check_smintf("0b101", "%b", 5);
	mu_end();
}


