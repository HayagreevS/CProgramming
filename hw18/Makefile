#ASSIGNMENT 
ASG_NICKNAME = HW18
BASE_NAME_1 = priority_queue
BASE_NAME_2 = frequencies
BASE_NAME_3 = huffman

#EXECUTABLES
EXECUTABLE = test_$(BASE_NAME_3)
EXECUTABLE_GCOV = $(EXECUTABLE)_gcov

#FILENAMES
SRC_C = $(BASE_NAME_1).c $(BASE_NAME_2).c $(BASE_NAME_3).c
TEST_C = test_$(BASE_NAME_3).c
SRC_H = $(BASE_NAME_1).h $(BASE_NAME_2).h $(BASE_NAME_3).h miniunit.h clog.h
SUBMIT_FILES = $(SRC_C) $(TEST_C) $(SRC_H)

#SYSTEM
SHELL = /bin/bash
CC = gcc
CFLAGS = -g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV = -ftest-coverage -fprofile-arcs

$(EXECUTABLE): $(SUBMIT_FILES)
	$(CC) -o $(EXECUTABLE) $(SUBMIT_FILES) $(CFLAGS) 

test: $(EXECUTABLE)
	./$(EXECUTABLE)
	valgrind ./$(EXECUTABLE) -s --track-origins=yes

clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE_GCOV) *.c.gcov *.gcda *.gcno

pretest: submit
	264test $(ASG_NICKNAME)

submit:
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES) Makefile test.txt

coverage: $(SRC_C) $(TEST_C)
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(C_FLAGS_GCOV)


.PHONY: test clean pretest submit coverage
