#include "miniunit.h"

int _test_success() {
	mu_start();
	mu_check(1 == 1);
	mu_check(true);
	mu_check(1 == 1 && 2 == 2);
	mu_check(2 == 1 + 1);
	mu_check(1 + 1 == 2);
	mu_check(2 * 2 == 1 * 4);
	mu_end();
}

int main() {
	mu_run(_test_success);
}
