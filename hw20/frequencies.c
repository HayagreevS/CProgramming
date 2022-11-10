#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "frequencies.h"

bool calc_frequencies(Frequencies freqs, const char* path, const char** a_error) {
	FILE* file; 
	if((file = fopen(path, "r")) == NULL) {
		*a_error = strerror(errno);
		return false;
	}
	else {
		for(uchar c = fgetc(file); !feof(file); c = (uchar) fgetc(file)) {
			freqs[c]++;
		}
		fclose(file);
		return true;
	}
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
