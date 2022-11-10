#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "clog.h"
#include "json.h"

static void append(Node** a_head, Node** a_tail) {
	Node* new_tail = malloc(sizeof(*new_tail));
	new_tail -> next = NULL;
	if(*a_head == NULL) {
		*a_head = new_tail;
	}
	else {
		(*a_tail) -> next = new_tail;
	}
	*a_tail = new_tail;
}

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
	while(isspace(**a_pos)) {
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
	else if (**a_pos == '[') {
		a_element -> type = ELEMENT_LIST;
		return parse_list(&(a_element -> as_list), a_pos);
	}
	else {
		return false;
	}
}

bool parse_string(char** a_string, char const** a_pos) {
	bool found;
	int length = 0;

	for(int i = 1; ((*(*a_pos + i)) != '\0'); i++) {
		if(*(*a_pos + i) == '"') {
			if(length > -1){
				length = i;
			}
		}
		else if((*(*a_pos + i) == '\n') || (*(*a_pos + i) == '\t')) {
			if(length < 1) {
				length = -i;
			}
		}
	}

	if (length == 0) {
		found = false;
		for(int x = 1; *(*a_pos + x) != '\0'; x++) {
			length++;
		}
		*a_pos = *a_pos + length;
	} 
	else if(length > 0) {
		found = true;
		*a_string = malloc(sizeof(*a_string) * (length - 1));
		for(int j = 0; j < length - 1; j++) {
			*(*a_string + j) = *(*a_pos + j + 1);
		}
		*a_pos = *a_pos + length + 1;
	}
	else if(length < 0) {
		found = false;
		*a_pos = *a_pos - length + 1;
	}
	return found;
}


void free_element(Element element) {
	if(element.type == ELEMENT_STRING){
		free(element.as_string);
	}
	else if (element.type == ELEMENT_LIST) {	
		//assert(((element -> as_list) -> element).type == ELEMENT_INT);
		while(element.as_list != NULL) {
			Node* new = (element.as_list) -> next;
			free_element(element.as_list -> element);
			free(element.as_list);
			element.as_list = new;
		}
		assert(element.as_list == NULL);
		
		/*
		for(Node* curr = element.as_list; curr != NULL; curr = curr -> next) {
			free_element(curr -> element);
			free(curr);
		}
		*/
	 }
}

void print_element(Element element) {
	if (element.type == ELEMENT_INT) {
		printf("%d", (element.as_int));
	} 
	else if (element.type == ELEMENT_STRING) {
		if(element.as_string != NULL) {
			printf("\"%s\"", (element.as_string));
		}
	}
	else if (element.type == ELEMENT_LIST) {
		printf("[");
		for(Node* curr = element.as_list; curr != NULL; curr = curr -> next) {
			print_element(curr -> element);
			if(curr -> next != NULL) {
				printf(",");
			}
		}
		printf("]");
	}
}

bool parse_list(Node** a_head, char const** a_pos) {
	bool found;
	int count = 0;
	int length = 0;
	
	if(**a_pos != '[') {
		found = false;
		*a_pos = *a_pos + 1;
	}

	for(int i = 1; *(*a_pos + i) != '\0'; i++) {
		if (*(*a_pos + i) == '[') {
			count++;
		} 
		else if (*(*a_pos + i) == ']') {
			count--;
		}
		else if ((*(*a_pos + i) == ',') && (count == 0)) {
			length++;
		}
	}
	
	if(*(*a_pos + 1) == ']') {
		*a_head = NULL;
		count = 1000;
		found = true;
		*a_pos = *a_pos + 2;
	}

	if(count == -1) {
		found = true;
		Node* head = NULL;
		Node* tail = NULL;
		append(&head, &tail);
		*a_pos = *a_pos + 1;
		found = parse_element(&(head -> element), a_pos);
		for(int i = 0; (i < length) && found; i++) {
			append(&head, &tail);
			while(**a_pos != ',') {
				*a_pos = *a_pos + 1;
			}
			*a_pos = *a_pos + 1;
			found = parse_element(&(tail -> element), a_pos);
		}
		if(found){
			while(**a_pos != ']') {
				*a_pos = *a_pos + 1;
			}
			*a_pos = *a_pos + 1;
			*a_head = head;
		}
		else {
			while(head != NULL) {
				Node* new = head -> next;
				if (((head -> element).as_string != NULL) || ((head -> element).as_list != NULL)) {
					free_element(head -> element);
				}
				free(head);
				head = new;
			}
			tail = NULL;
		}
	}
	else if (count != 1000) {
		found = false;
	}
	//assert(found);
	//assert(((*a_head) -> element).type  == ELEMENT_STRING);
	return found;
}




