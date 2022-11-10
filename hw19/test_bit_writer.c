#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include "clog.h"
#include "miniunit.h"
#include "bit_writer.h"

int _test_bit_writer_main() {
	mu_start();
	BitWriter writer = open_bit_writer("test.txt");
	write_bits(&writer, 0x05, 3);
	write_bits(&writer, 0xF3, 3);
	write_bits(&writer, 0x01, 5);
	write_bits(&writer, 0x01, 2);
	write_bits(&writer, 0x20, 6);
	write_bits(&writer, 0x13, 5);
	close_bit_writer(&writer);
   	assert(writer.current_byte == 0);
	assert(writer.num_bits_left = 8);
	mu_end();
}

int _test_bit_writer_v2() {
	mu_start();
	BitWriter writer = open_bit_writer("test2.txt");
	write_bits(&writer, 0xFF, 8);
	write_bits(&writer, 0x58, 2);
	write_bits(&writer, 0x99, 6);
	write_bits(&writer, 0x44, 3);
	close_bit_writer(&writer);
	mu_end();
}


int main(int argc, char* argv[]) {
	mu_run(_test_bit_writer_main);
	mu_run(_test_bit_writer_v2);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
