#ASSIGNMENT 
ASG_NICKNAME = EC01
BASE_NAME = sorts

#EXECUTABLES
EXECUTABLE = test_$(BASE_NAME)
EXECUTABLE_GCOV = $(EXECUTABLE)_gcov

#FILENAMES
SRC_C = $(BASE_NAME).c
TEST_C = test_$(SRC_C)
SRC_H = $(BASE_NAME).h 
SUBMIT_FILES = $(SRC_C) $(TEST_C) $(SRC_H) 

#SYSTEM
SHELL = /bin/bash
CC = gcc
CFLAGS = -g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV = $(CFLAGS) -fprofile-arcs -ftest-coverage

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
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES)

coverage: $(SRC_C) $(TEST_C)
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(C_FLAGS_GCOV)
	./$(EXECUTABLE_GCOV)

.PHONY: test clean pretest submit coverage
