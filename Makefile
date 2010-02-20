# Makefile for rvm

OBJS = code.o
TEST_OBJS = code_test.o type_test.o
CC = gcc
CFLAGS += -m32


.PHONY: all
all: rvm


.PHONY: test
test: rvm_test
	./rvm_test


rvm: $(OBJS) rvm.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


rvm_test: $(OBJS) $(TEST_OBJS) rvm_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


.PHONY: clean
clean:
	rm -f $(OBJS) rvm.o rvm
	rm -f $(TEST_OBJS) rvm_test.o rvm_test
