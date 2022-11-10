#include <stdbool.h>
#include <string.h>
#include "clog.h"

#ifndef __MINIUNIT_H__

#define mu_start() int __mu__first_line_num = 0

#define mu_check(condition) 											\
	do {																\
		if ((condition) == 0 && __mu__first_line_num == 0) { 			\
			__mu__first_line_num = __LINE__;							\
		}																\
	} while(0)															

#define mu_run(func)													\
	do {																\
		func();															\
		if (func() == 0) {												\
			logf_green("Test passed: %s\n", #func);						\
		}																\
		else if (func() >= 1) {										\
			logf_red("Test failed: %s at line %d\n", #func, func());	\
		}																\
	} while(0)

#define mu_end() return __mu__first_line_num

#define mu_check_strings_equal(s1, s2) mu_check(strcmp((s1), (s2)) == 0)

#define mu_check_smintf(expected, ...)			\
	do {										\
		char* actual = smintf(__VA_ARGS__);		\
		mu_check_strings_equal((expected), (actual));	\
		free(actual);							\
	} while(0)

#endif
