# Makefile for rvm

OBJS = code.o cycle.o cpu.o
TEST_OBJS = test_type.o test_code.o test_cycle.o
CC = gcc
CFLAGS += -m32


.PHONY: all
all: rvm


.PHONY: test
test: test_rvm
	./test_rvm


rvm: $(OBJS) rvm.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


test_rvm: $(OBJS) $(TEST_OBJS) test_rvm.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


.PHONY: clean
clean:
	rm -f $(OBJS) rvm.o rvm
	rm -f $(TEST_OBJS) test_rvm.o test_rvm
