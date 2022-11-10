#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"

void print_integer(int n, int radix, char* prefix) {
	unsigned int n_abs = 0;
	unsigned int deg = 0;
	unsigned int temp = 0;
	unsigned int div = 0;
	unsigned int val = 0;

	if (n < 0) {
		fputc((char) 45, stdout);
		n_abs = (unsigned int) -1 * n;
	}
	else {
		n_abs = n;
	}

	for (int idx = 0; prefix[idx] != '\0'; idx++) {
		fputc(prefix[idx], stdout);
	}

	temp = n_abs;
	while ((temp / radix) > 0) {
		deg++;
		temp = temp / radix;
	}

	for (int j = deg; j >= 0; j--) {
		div = 1;

		for (int i = 1; i <= j; i++) {
			div = div * radix;
		}

		val = n_abs / div;
		n_abs = n_abs - (val * div);

		if (val < 10) {
			fputc((char)(val + '0'), stdout);
		}
		else {
			fputc((char)(val + 'W'), stdout);
		}
	}
}

void mintf(const char *format, ...) {
	va_list more_args;
	va_start(more_args, format);
	int n;
	char* v;
	unsigned int l;
	
	for (int idx = 0; format[idx] != '\0'; idx++) {
		if (format[idx] == '%') {
			if (format[idx + 1] == 'd') {
				n = va_arg(more_args, int);
				print_integer(n, 10, "");
				idx+=1;
			}
			else if (format[idx + 1] == 'x') {
				n = va_arg(more_args, int);
				print_integer(n, 16, "0x");
				idx+=1;
			}
			else if (format[idx + 1] == 'b') {
				n = va_arg(more_args, int);
				print_integer(n, 2, "0b");
				idx+=1;
			}
			else if (format[idx + 1] == '$') {
				n = va_arg(more_args, int);
				if (n < 0) {
					fputc((char)45, stdout);
					n = n * -1;
				}
				l = n % 100;
				n = (n-l) / 100;
				//fputc((char)36, stdout);
				//printf("\nn:%d\nl:%d\n", n, l);
				print_integer((unsigned int)n, 10,"$");
				fputc((char)46, stdout);
				if ((int) l < 10 && (int) l > -10) {
					print_integer(0,10,"");
				}
				print_integer((unsigned int)l, 10,"");
				idx+=1;
			}
			else if (format[idx + 1] == 's') {
				v = va_arg(more_args, char*);
				for (int odx = 0; v[odx] != '\0'; odx++) {
					fputc(v[odx], stdout);
				}
				idx+=1;
			}
			else if (format[idx + 1] == 'c') {
				n = va_arg(more_args, int);
				fputc((char) n, stdout);
				idx+=1;
			}
			else if (format[idx + 1] == '%') {
				fputc((char) 37, stdout);
				idx+=1;
			} 
			else {
				fputc((char) 37, stdout);
			}
		}
		else {
			fputc(format[idx], stdout);
		}		
	}
	va_end(more_args);
}

