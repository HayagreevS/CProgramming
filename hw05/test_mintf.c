#include <stdlib.h>
#include "mintf.h"

int main(int argc, char *argv[]) {
	// Test 00: empty test
	// Expect: ""
	//
	// Test 01: empty string
	//mintf("");
	// Expect: ""
	//
	// Test 02: regular string
	//mintf("Hello");
	// Expect: "Hello");
	// 
	// Test 03: String with int format
	//mintf("%d", 1);
	// Expect "1"
	//
	// Test 04: integer with different base and prefix
	//mintf("%b", 5);
	// Expect "0b101"
	//
	// Test 05: String with format
	//mintf("Hello %d", 1);
	// Expect "Hello 1"
	//
	// Test 06: String with one format, more than one argument
	//mintf("Hello %d", 2, 3);
	// Expect "Hello 2"
	//
	// Test 07: String with >1 format, >1 argument
	//mintf("Hello %d%d", 4, 5);
	// Expect "Hello 45"
	//
	// Test 08: String with format between words
	//mintf("Hello %d World", 1); 
	// Expect "Hello 1 World"
	// 
	// Test 09: String with multiple formats scattered
	//mintf("Hello %d World %d Hello", 1, 2);
	// Expect "Hello 1 World 2 Hello"
	//
	// Test 10: Format with mixed format
	mintf("%$",  1);
	// Expect "%d");
	//
	// Test 10: string/char format
	mintf("%$", 100);
	// Expect "$ string"
	//
	// Test 11: insufficient argument
	mintf("%$", 1000);
	// Expect "1 2 ???????"
	//
	// Test 12: Negative Symbol before prefix
	// Expect "-0b10"
}
