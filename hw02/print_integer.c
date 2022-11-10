#include "print_integer.h"
#include <stdio.h>

void print_integer(int n, int radix, char* prefix) {
	unsigned int n_abs;
	unsigned int deg = 0;
	unsigned int temp;
	unsigned int div;
	unsigned int val;

	if (n < 0) {
		fputc((char) 45, stdout);
		n_abs = (unsigned int) -1 * n;
	}
	else {
		n_abs = n;
	}

	for(int idx = 0; prefix[idx] != '\0'; idx++) {
		fputc(prefix[idx], stdout);
	}
	
	temp = n_abs;
	while((temp / radix) > 0) {
		deg++;
		temp = temp / radix;
	}

	for(int j = deg; j >= 0; j--) {
		div = 1;

		for(int i = 1; i <= j; i++) {
			div = div * radix;
		}

		val = n_abs / div;
		n_abs = n_abs - (val * div);

		if (val < 10) {
			fputc((char)(val + '0'), stdout);
		}
		else {
			fputc((char)(val - 10 + 'a'), stdout);
		}
	}
}
