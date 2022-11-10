#include <unistd.h>
#include <stdio.h>

#ifndef __CLOG_H__
#define __CLOG_H__

#ifndef NDEBUG
	#define logf_ printf

	#define logf_red(string, ...) 			\
		do {								\
			if (isatty(STDOUT_FILENO)) {	\
				printf("\x1b[31m"); 		\
				printf(string, __VA_ARGS__);\
				printf("\x1b[0m"); 			\
			}								\
			else {							\
				printf(string, __VA_ARGS__);\
			}								\
		} while(0);

	#define logf_green(string, ...) 		\
		do {								\
			if (isatty(STDOUT_FILENO)) {	\
				printf("\x1b[32m"); 		\
				printf(string, __VA_ARGS__);\
				printf("\x1b[0m"); 			\
			}								\
			else {							\
			printf(string, __VA_ARGS__);\
			}								\
		} while(0);

	#define logf_yellow(string, ...) 			\
		do {								\
			if (isatty(STDOUT_FILENO)) {	\
				printf("\x1b[33m"); 		\
				printf(string, __VA_ARGS__);\
				printf("\x1b[0m"); 			\
			}								\
			else {							\
			printf(string, __VA_ARGS__);\
			}								\
		} while(0);

	#define logf_blue(string, ...) 			\
		do {								\
			if (isatty(STDOUT_FILENO)) {	\
				printf("\x1b[34m"); 		\
				printf(string, __VA_ARGS__);\
				printf("\x1b[0m"); 			\
			}								\
			else {							\
				printf(string, __VA_ARGS__);\
			}								\
		} while(0);

	#define logf_magenta(string, ...) 			\
		do {								\
			if (isatty(STDOUT_FILENO)) {	\
				printf("\x1b[35m"); 		\
				printf(string, __VA_ARGS__);\
				printf("\x1b[0m"); 			\
			}								\
			else {							\
				printf(string, __VA_ARGS__);\
			}								\
		} while(0);

	#define logf_cyan(string, ...) 			\
		do {								\
			if (isatty(STDOUT_FILENO)) {	\
				printf("\x1b[36m"); 		\
				printf(string, __VA_ARGS__);\
				printf("\x1b[0m"); 			\
			}								\
			else {							\
				printf(string, __VA_ARGS__);\
			}								\
		} while(0);

	#define log_int(n) printf("%s == %d\n", #n, n);

	#define log_char(n) printf("%s == \'%c\'\n", #n, n);

	#define log_str(n) printf("%s == \"%s\"\n", #n, n);

	#define log_addr(n) printf("%s == %p\n", #n, (void*)n);

	#define log_float(n) printf("%s == %.016f\n", #n, n);

	#define log_bool(n) printf("%s == %s\n", #n, (n?"true":"false"));

#else
	#define logf_(...) 
	#define logf_red(...)
	#define logf_green(...)
	#define logf_yellow(...)
	#define logf_blue(...)
	#define logf_magenta(...)
	#define logf_cyan(...)
	#define log_int(...)
	#define log_char(...)
	#define log_str(...)
	#define log_addr(...)
	#define log_float(...)
	#define log_bool(...)
#endif
#endif
