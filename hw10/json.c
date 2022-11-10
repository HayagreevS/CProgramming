#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "clog.h"

bool parse_int(int* a_value, char** a_pos){
	bool found = false;
	unsigned int temp = 0;
	int neg = 1;
	if (**a_pos == 45) {
		neg = -1;
	}
	do {
		if(**a_pos - 48 >= 0 && **a_pos - 48 <= 9){
			temp = temp*10 + ((**(a_pos)) - 48);
			found = true;
		}
		*a_pos = *a_pos + 1;
	} while((**a_pos - 48) >= 0 && (**a_pos - 48) <= 9);
	if (found) {
		*a_value = neg * temp;
	}
	return found;
}

