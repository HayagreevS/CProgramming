#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miniunit.h"
#include "smintf.h"

int main(int argc, char* argv[]) {
	char* actual = smintf("%%", 10);
	fputs(actual, stdout);
	free(actual);
	return EXIT_SUCCESS;
}

