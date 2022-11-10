#include <assert.h>
#include "bit_writer.h"

typedef  unsigned char uchar;

BitWriter open_bit_writer(const char* path) {
	return (BitWriter) {.file = fopen(path, "w"), .current_byte = 0, .num_bits_left = 8};
}

/*void _write_to_file(uint8_t byte, FILE* path) {
	for(int i = 8; i > 0; i--) {
		fputc(48 + ((byte >> (i - 1)) & (0xff >> 7)), path);
	}
	//fputc(' ', path);
}*/

void write_bits(BitWriter* a_writer, uint8_t bits, uint8_t num_bits_to_write) {
	//assert(num_bits_to_write >= 0 && num_bits_to_write <= 8);
	//assert(a_writer->num_bits_left >= 1 && a_writer->num_bits_left <= 8);
	if(a_writer -> num_bits_left > num_bits_to_write) {
		uint8_t temp = bits << (8 - num_bits_to_write);
		temp = temp >> (8 - a_writer->num_bits_left);
		a_writer -> current_byte = (a_writer -> current_byte) | temp;
		a_writer -> num_bits_left = a_writer -> num_bits_left - num_bits_to_write;
	} 
	else if(a_writer -> num_bits_left == num_bits_to_write) {
		uint8_t part1 = bits & (0xff >> (8 - a_writer -> num_bits_left));
		//part1 = part1 >> (a_writer -> num_bits_left);
		a_writer -> current_byte = (a_writer -> current_byte) | part1;
		fputc(a_writer -> current_byte, a_writer -> file);
		a_writer -> current_byte = 0x00;
		a_writer -> num_bits_left = 8 - num_bits_to_write + a_writer -> num_bits_left;
	}
	else {
		uint8_t part1 = bits << (8 - num_bits_to_write);
		part1 = part1 >> (8 - a_writer -> num_bits_left);
		uint8_t part2 = bits << (8 - num_bits_to_write + a_writer -> num_bits_left);
       	a_writer -> current_byte = (a_writer -> current_byte) | part1;
		fputc(a_writer -> current_byte, a_writer -> file);
		a_writer -> current_byte = part2;
		a_writer -> num_bits_left = 8 - num_bits_to_write + a_writer -> num_bits_left;
	}
	//assert(a_writer->num_bits_left >= 1 && a_writer->num_bits_left <= 8);
}

void flush_bit_writer(BitWriter* a_writer) {
	if(a_writer -> num_bits_left < 8) {
		fputc(a_writer -> current_byte, a_writer -> file);
		a_writer -> current_byte = 0;
		a_writer -> num_bits_left = 8;
	}
}

void close_bit_writer(BitWriter* a_writer) {
	flush_bit_writer(a_writer);
	fclose(a_writer -> file);
	a_writer -> file = NULL;
}


#define __BIT_WRITER_C_V1__
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab colorcolumn=96: */
