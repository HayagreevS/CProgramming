#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "miniunit.h"
#include "clog.h"
#include "json.h"

/*
int _test_();
int _test_2();
int _test_3();
int _test_4();
int _test_5();
int _test_6();
int _test_7();


typedef struct {
	bool is_success;
	union {
		Element element;
		long int error_idx;
	};
}ParseResult;

static ParseResult _parse_json(char* s) {
	Element element;
	char const* pos = s;
	bool is_success = parse_element(&element, &pos);
	if(is_success) {
		return (ParseResult) {.is_success = is_success, .element = element};
	} 
	else {
		return (ParseResult) {.is_success = is_success, .error_idx = pos - s};
	}
}

static int _test_string() {
	mu_start();
	ParseResult result = _parse_json("\"abc\"");
	mu_check(result.is_success);
	if(result.is_success) {
		mu_check(result.element.type == ELEMENT_STRING);
		mu_check(strcmp(result.element.as_string, "abc") == 0);
		mu_check(strlen(result.element.as_string) == 3);
		free_element(result.element);
	}
	mu_end();
}

*/

static int _test_parse_element_int_neg() {
	mu_start();
	Element element;
	char const* input = "-2";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == -2);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	mu_end();
}

static int _test_parse_element_int_oddballs() {
	mu_start();
	Element element;
	char const* input = " 4 A";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 4);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == ' ');
	mu_end();
}

static int _test_parse_string_valid_multiple_chars() {
	mu_start();
	char* result;
	char const* input = "\"ABC\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	//mu_check_strings_equal("ABC", result);
	mu_check(pos == input + 5);
	mu_check(*pos == '\0');
	free(result);
	mu_end();
}


static int _test_parse_string_valid() {
	mu_start();
	char* result;
	char const* input = "\"\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	//mu_check_strings_equal("", result);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	free(result);

	input = "\"A\"";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 3);
	//mu_check(*pos == '\n');
	free(result);
	mu_end();
}

static int _test_parse_list() {
	mu_start();
	Element element;
	char const* input = "[\"AB\"3424, 656565, \"\n\"]";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	//print_element(element);
	fputc('\n', stdout);
	//mu_check(element.type == ELEMENT_LIST);
	//mu_check(pos = input + 6);
	//mu_check(*pos == '5');
	//assert(((element.as_list) -> element).type == ELEMENT_STRING);
	//printf("%d", (element.as_list) -> element.as_int);
	//free_element(element);
	mu_end();
}

static int _test_parse_list2() {
	mu_start();
	Element element;
	char const* input = "[[]]";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	//print_element(element);
	fputc('\n', stdout);
	//mu_check(element.type == ELEMENT_LIST);
	//mu_check(pos = input + 6);
	//mu_check(*pos == '5');
	//assert(((element.as_list) -> element).type == ELEMENT_STRING);
	//printf("%d", (element.as_list) -> element.as_int);
	free_element(element);
	mu_end();
}

/*
static void _test_print_element() {
	Element element;
	char const* input = "123";
	parse_element(&element, &input);
	printf("Testing parse_element(&element, \"123\")\n");
	printf(" - Expected: 123\n");
	printf(" - Actual:   ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);
	//printf("%d", is_success);
}
*/

int main(int argc, char* argv[]) {
	/*mu_run(_test_);
	mu_run(_test_2);
	mu_run(_test_3);
	mu_run(_test_4);
	mu_run(_test_5);
	mu_run(_test_6);
	mu_run(_test_7);*/
	mu_run(_test_parse_element_int_neg);
	mu_run(_test_parse_element_int_oddballs);
	mu_run(_test_parse_string_valid_multiple_chars);
	mu_run(_test_parse_string_valid);
	mu_run(_test_parse_list);
	mu_run(_test_parse_list2);
	//mu_run(_test_string);
	//_test_print_element();
	return EXIT_SUCCESS;
}

/*
int _test_() {
	mu_start();
	int result;
	char* input = "0";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 1);
	mu_check(result == 0);
	mu_end();
}

int _test_2() {
	mu_start();
	int result;
	char* input = "-2";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos = input + 2);
	mu_check(result == -2);
	mu_end();
}

int _test_3() {
	mu_start();
	int result;
	char* input = "-A2";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check(pos = input + 1);
	mu_end();
}

int _test_4() {
	mu_start();
	int result;
	char* input = "15";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos = input + 2);
	mu_check(result == 15);
	mu_end();
}

int _test_5() {
	mu_start();
	int result;
	char* input = "1500";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos = input + 4);
	mu_check(result == 1500);
	mu_end();
}

int _test_6() {
	mu_start();
	int result;
	char* input = "-2147483647";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(result == -2147483647);
	printf("%d", result);
	mu_end();
}

int _test_7() {
	mu_start();
	int result;
	char* input = "-2A54";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos = input + 2);
	mu_check(result == -2);
	printf("%d", result);
	mu_end();
}

*/
