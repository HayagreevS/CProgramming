#include "print_integer.h"
#include <limits.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	print_integer(378, 20, "");
	print_integer(1, 2, "");
	print_integer(16, 16, "");
	print_integer(15, 16, "");
	print_integer(10, 11, "$");
	print_integer(100000, 16, "----$$$$--");
	print_integer(-32, 20, "$$");
	print_integer(7500, 10, "");
	print_integer(8, 10, "");
	print_integer(35, 36, "");
	print_integer(INT_MIN, 15, "");
	print_integer(INT_MAX, 19, "");
	return EXIT_SUCCESS;
}
