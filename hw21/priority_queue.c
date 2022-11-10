#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "priority_queue.h"
#include "huffman.h"


Node* pq_enqueue(Node** a_head, void* a_value, int (*cmp_fn)(const void*, const void*)) {
	Node* new_node = malloc(sizeof(*new_node));
	*new_node = (Node) {.a_value = a_value, .next = NULL};
	//printf("\n a_val: %c\n", ((TreeNode*)a_value) -> character);
	if(*a_head == NULL) {
		*a_head = new_node;
	}
	else {
		if(cmp_fn((*a_head) -> a_value, new_node -> a_value) > 0) {	
			new_node -> next = (*a_head);
			*a_head = new_node;
		}
		else {
			new_node -> next = (*a_head) -> next;
			(*a_head) -> next = new_node;
			Node* curr = (*a_head);
			while((new_node -> next != NULL) && (cmp_fn((new_node -> next) -> a_value, new_node -> a_value) <= 0)) {
				curr -> next = new_node -> next;
				new_node -> next = (new_node -> next) -> next;
				curr = curr -> next;
				curr -> next = new_node;
			}
		}
	}
	return new_node;  // STUB -- remove this line when filling in the body of pq_enqueue(…).
}


Node* pq_dequeue(Node** a_head) {
	Node* new_node = *a_head;
	if(*a_head != NULL) {
		*a_head = (*a_head) -> next;
		new_node -> next = NULL;
	}
	return new_node;  // STUB -- remove this line when filling in the body of pq_dequeue(…).
}


Node* stack_push(Node** a_head, void* a_value) {
	Node* new = malloc(sizeof(*new));
	*new = (Node) {.a_value = a_value, .next = *a_head};
	*a_head = new;
	return new;  // STUB -- remove this line when filling in the body of stack_push(…).
}


Node* stack_pop(Node** a_head) {
	return pq_dequeue(a_head);  // STUB -- remove this line when filling in the body of stack_pop(…).
}


void destroy_list(Node** a_head, void (*destroy_value_fn)(void*)) {
	while(*a_head != NULL) {
		Node* temp = stack_pop(a_head);
		destroy_value_fn(temp -> a_value);
		free(temp);
	}
}


#define HUFFMAN_C_V1
