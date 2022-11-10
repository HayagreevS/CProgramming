#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "clog.h"
#include "json.h"

bool parse_int(int* a_value, const char** a_pos) {
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

bool parse_element(Element* a_element, const char** a_pos) {
	while(**a_pos == 32) {
		*a_pos = *a_pos + 1;
	}
	if(isdigit(**a_pos) || (**a_pos == '-')) {
		a_element -> type = ELEMENT_INT;
		return parse_int(&(a_element -> as_int), a_pos);
	}
	else if (**a_pos == '"') {
		a_element -> type = ELEMENT_STRING;
		return parse_string(&(a_element -> as_string), a_pos);
	}
	else {
		return false;
	}
}

bool parse_string(char** a_string, char const** a_pos) {
	bool found = false;
	int length = 0;

	if (**a_pos != '"'){
		found = false;
	} else {
		for(int i = 1; *(*a_pos + i) != '\0'; i++) {
			if(*(*a_pos + i) == '"') {
			found = true;
			}
			else {
				length++;
			}
		}
	}

	if(found) {
		*a_string = malloc(sizeof(*a_string) * length);
		*a_pos = *a_pos + 1;
		for(int j = 0; j < length; j++) {
			*(*a_string + j) = **a_pos;
			*a_pos = *a_pos + 1;
		}
		*a_pos = *a_pos + 1;
		}
	return found;
}


void free_element(Element element) {
	if(element.type == ELEMENT_STRING){
		free(element.as_string);
	}
}

void print_element(Element element) {
	if (element.type == ELEMENT_INT) {
		printf("%d", (element.as_int));
	} 
	else if (element.type == ELEMENT_STRING) {
		printf("\"%s\"", (element.as_string));
	}
}
