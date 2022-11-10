#ASSIGNMENT 
ASG_NICKNAME = HW19
BASE_NAME = bit_writer

#EXECUTABLES
EXECUTABLE = test_$(BASE_NAME)
EXECUTABLE_GCOV = $(EXECUTABLE)_gcov

#FILENAMES
SRC_C = $(BASE_NAME).c
TEST_C = test_$(SRC_C)
SRC_H = $(BASE_NAME).h 
SUBMIT_FILES = $(SRC_C) $(TEST_C) $(SRC_H) clog.h miniunit.h

#SYSTEM
SHELL = /bin/bash
CC = gcc
CFLAGS = -g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV = -ftest-coverage -fprofile-arcs

$(EXECUTABLE): $(SUBMIT_FILES)
	$(CC) -o $(EXECUTABLE) $(SUBMIT_FILES) $(CFLAGS)

test: $(EXECUTABLE)
	./$(EXECUTABLE)
	valgrind ./$(EXECUTABLE) -s

clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE_GCOV) *.c.gcov *.gcda *.gcno

pretest: submit
	264test $(ASG_NICKNAME) 

submit:
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES) Makefile warmup.c test.txt

coverage: $(SRC_C) $(TEST_C)
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(C_FLAGS_GCOV)


.PHONY: test clean pretest submit coverage
