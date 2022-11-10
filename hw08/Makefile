ASG_NICKNAME = HW55
BASE_NAME = count_words

EXECUTABLE = test_$(BASE_NAME)
EXECUTABLE_GCOV = $(EXECUTABLE)_gcov

SRC_C = $(BASE_NAME).c
TEST_C = $(EXECUTABLE).c
SRC_H = $(BASE_NAME).h clog.h miniunit.h 
SUBMIT_FILES = $(SRC_C) $(TEST_C) $(SRC_H) Makefile

SHELL = /bin/bash
C_FLAGS_GCOV = $(CFLAGS) -fprofile-arcs -ftest-coverage
CC = gcc
CFLAGS = -g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic

$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE)_dbg $(EXECUTABLE_GCOV) *.c.gcov *.gcda *.gcno

pretest: submit
	264test $(ASG_NICKNAME)

submit: 
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES)

coverage: $(SRC_C) $(TEST_C)
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(C_FLAGS_GCOV)

.PHONY: submit test pretest clean coverage
