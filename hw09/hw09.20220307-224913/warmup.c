 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>

char* my_strdup(const char* original) {
	// TODO
	int len = 0;
	do {
		len++;
	} while(original[len - 1] != '\0');
	char* copy = malloc(len * sizeof(*copy));
	for(int i = 0; i < len; i++){
		*(copy + i) = original[i];
	}
	return copy;
}

int main(int argc, char *argv[]) {
	char s[] = "abc\n";
	fputs(s, stdout);  // Should print "abc" followed by a newline ('\n')

	char* t = my_strdup(s);
	fputs(t, stdout);  // Should print "abc" followed by a newline ('\n')
	free(t);

	return EXIT_SUCCESS;
}
