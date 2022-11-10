#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "clog.h"
#include "miniunit.h"
#include "huffman.h"


static int _cmp_int(const void* a, const void* b) {
	return(*(int*) a - *(int*)b);
}

static void _des_int(void* a) {
}



static int _cmp_string(const void* a, const void* b) {
	size_t len_a = strlen(a);
	size_t len_b = strlen(b);
	return (len_a  - len_b);
}

static void _des_string(void* str) {
	free(str);
}

static void _test_queue_int() {
	Node* head = NULL;
	int x0 = 1;
	int x1 = 20;
	int x2 = 25; 
	int x3 = 4;
	int x4 = -6;

	pq_enqueue(&head, &x0, _cmp_int);
	pq_enqueue(&head, &x1, _cmp_int);
	pq_enqueue(&head, &x2, _cmp_int);
	pq_enqueue(&head, &x3, _cmp_int);
	pq_enqueue(&head, &x4, _cmp_int);

	for(Node* curr = head; curr != NULL; curr = curr -> next) {
		printf("[%d] ", *(int*)(curr -> a_value));
	}

	destroy_list(&head, _des_int);	
}


static void _test_queue_str() {
	Node* str_head = NULL;
	char* string1 = malloc(6*sizeof(*string1));
	char* string2 = malloc(10*sizeof(*string2));
	char* string3 = malloc(6*sizeof(*string3));
	//char* string4 = malloc(6*sizeof(*string4));

	strcpy(string1,"hello");
	strcpy(string2,"lengthtee");
	strcpy(string3,"words");
	//strcpy(string4, "HEllo");

	pq_enqueue(&str_head, string1, _cmp_string);
	pq_enqueue(&str_head, string2, _cmp_string);
	pq_enqueue(&str_head, string3, _cmp_string);
	//pq_enqueue(&str_head, string4, _cmp_string);

	//printf("%d", _cmp_string(&string1, &string3));

	for(Node* curr = str_head; curr!= NULL; curr = curr -> next) {
		printf("\n%s\n", (char*)(curr -> a_value));
	}

	destroy_list(&str_head, _des_string);

}

static void _test_push_int() {
	Node* head = NULL;
	int x0 = 76;
	int x1 = 234;
	int x2 = 23;
	stack_push(&head, &x0);
	stack_push(&head, &x1);
	stack_push(&head, &x2);
	free(stack_pop(&head));
	free(stack_pop(&head));
	free(stack_pop(&head));
	stack_pop(&head);
	assert(head == NULL);
	for(Node* curr = head; curr != NULL; curr = curr -> next) {
		printf("[%d] ", *(int*)(curr -> a_value));
	}

	destroy_list(&head, _des_int);
}


int main(int argc, char* argv[]) {	
	_test_queue_int();
	_test_queue_str();
	_test_push_int();
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
