#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include "smintf.h"
#include "clog.h"
#define HW09_BONUS

static void _get_output(const char* format, int type, va_list args, int* len, char* add, int* pos);
static void _output_(char out, int type, int* len, char* add, int* pos);
static void _dollar_(int num, int type, int* len, char* add, int* pos);
static void _base_convert(int num, int base, char* prefix, int type, int* len, char* add, int* pos);
static void _string_out(char *s, int type, int* len, char* add, int* pos);

char* smintf(const char* format, ...) {
	va_list args_1, args_2;
	va_start(args_1, format);
	va_copy(args_2, args_1);
	int len = 0;
	int pos = 0;
	_get_output(format, 1, args_1, &len, 0, 0);
	char* output = malloc((len + 1) * sizeof(*output));
	_get_output(format, 2, args_2, 0, output, &pos);
	output[pos] = (char)'\0';
	va_end(args_1);
	va_end(args_2);
	return output;
}

void mintf(const char* format, ...) {
	va_list(more_args);
	va_start(more_args, format);
	_get_output(format, 0, more_args, 0, 0, 0);
	va_end(more_args);
}

void _get_output(const char *format, int type, va_list args, int* len, char* add, int* pos) {
	int n;
	char* s;
	for(int idx = 0; format[idx] != '\0'; idx++) {
		if (format[idx] == '%') {
			if (format[idx + 1] == 'd') {
				n = va_arg(args, int);
				_base_convert(n, 10, "", type, len, add, pos);
			}
			else if (format[idx + 1] == 'b') {
				n = va_arg(args, int);
				_base_convert(n, 2, "0b", type, len, add ,pos);
			}
			else if (format[idx + 1] == 'x') {
				n = va_arg(args, int);
				_base_convert(n, 16, "0x", type, len, add, pos);
			}
			else if (format[idx + 1] == '$') {
				n = va_arg(args, int);
				_dollar_(n, type, len, add, pos);
			}
			else if (format[idx + 1] == 's') {
				s = va_arg(args, char*);
				_string_out(s, type, len, add, pos);
			}
			else if (format[idx + 1] == 'c') {
				s = va_arg(args, char*);
				_string_out(s, type, len, add, pos);
			}
			else if (format[idx + 1] == '%') {
				n = va_arg(args, int);
				_output_('%', type, len, add, pos);
			}
			else {
				_output_('%', type, len, add, pos);
				idx-=1;
			}
			idx+=1;
		} 
		else {
			_output_(format[idx], type, len, add, pos);
		}
	}
}

void _base_convert(int num, int base, char* prefix, int type,  int* len, char* add, int* pos){
	unsigned int abs_num = 0;
	unsigned int deg = 0;
	unsigned int temp = 0;
	unsigned int div = 0;
	unsigned int val = 0;

	if (num < 0) {
		_output_('-', type, len, add, pos);
		abs_num = (unsigned int) -1 * num;
	}
	else {
		abs_num = num;
	}

	for (int idx = 0; prefix[idx] != '\0'; idx++) {
		_output_(prefix[idx], type, len, add, pos);
	}

	temp = abs_num;
	while ((temp / base) > 0) {
		deg++;
		temp = temp / base;
	}

	for (int pow = deg; pow >= 0; pow--) {
		div = 1;

		for (int dig = 1; dig <= pow; dig++) {
			div = div * base;
		}

		val = abs_num / div;
		abs_num = abs_num - (val * div);

		if (val < 10) {
			_output_((char)(val + '0'), type, len, add, pos);
		}
		else {
			_output_((char)(val + 'W'), type, len, add, pos);
		}
	}
}

void _output_(char out, int type, int* len, char* add, int* pos) {
	if (type == 0) {
		fputc(out, stdout);
	}

	else if (type == 1) {
		(*len) = *len + 1;;
	}

	else if (type == 2) {
		*(add + *pos) = (char) out;
		*pos+=1;
	}
}

void _dollar_(int num, int type, int* len, char* add, int* pos) {
	unsigned int num_abs;
	int dec;

	if(num < 0) {
		_output_('-', type, len, add, pos);
		num_abs = (unsigned int) -1 * num;
	} else {
		num_abs = num;
	}

	dec = num_abs % 100;
	num_abs = (num_abs - dec) / 100;

	_base_convert((unsigned int) num_abs, 10, "$", type, len, add, pos);
	_output_('.', type, len, add, pos);
	if ((int)dec < 10 && (int)dec > -10) {
		_output_('0', type, len, add, pos);
	}
	_base_convert((unsigned int) dec, 10, "", type, len, add, pos);
}

void _string_out(char* s, int type, int* len, char* add, int* pos) {
	for (int idx = 0; s[idx] != '\0'; idx++) {
		_output_(s[idx], type, len, add, pos);
	}
}






