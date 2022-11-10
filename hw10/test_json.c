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

int _test_();
int _test_2();
int _test_3();
int _test_4();
int _test_5();
int _test_6();
int _test_7();

int main(int argc, char* argv[]) {
	mu_run(_test_);
	mu_run(_test_2);
	mu_run(_test_3);
	mu_run(_test_4);
	mu_run(_test_5);
	mu_run(_test_6);
	mu_run(_test_7);
	return EXIT_SUCCESS;
}

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

