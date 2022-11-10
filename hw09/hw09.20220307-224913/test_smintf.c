#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miniunit.h"
#include "smintf.h"

int test_basic();
int test_med();

int main(int argc, char* argv[]) {
	mu_run(test_basic);	
	mu_run(test_med);
	mintf("");
	mintf("%%%%seventy", -100);
	mintf("\n\n%c\n\n\n", "c");
	mintf("\n\n%s: %x\n\n", "string and hexa", -16);
	mintf("%$", -1002);
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

int test_med() {
	mu_start();
	mu_check_smintf("string 5 decimal 0x1 hexa", "string %d decimal %x hexa", 5, 1);
	mu_check_smintf("-0b1", "%b", -1);
	mu_check_smintf("c", "%c", "c");
	mu_check_smintf("string and hexa: -0x10", "%s: %x", "string and hexa", -16);
	mu_end();
}


