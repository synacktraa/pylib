BIN=gcc
CFLAGS=-g -Wall -Werror -Wextra
SAFELIB=src/safe.c
TESTDIR=test

all:

replace: $(TESTDIR)/replace.c $(SAFELIB)
	$(BIN) $(CFLAGS) $^ -o _replace

split: $(TESTDIR)/split.c $(SAFELIB)
	$(BIN) $(CFLAGS) $^ -o _split

join: $(TESTDIR)/join.c $(SAFELIB)
	$(BIN) $(CFLAGS) $^ -o _join

readline: $(TESTDIR)/readline.c $(SAFELIB)
	$(BIN) $(CFLAGS) $^ -o _readline

readlines: $(TESTDIR)/readlines.c $(SAFELIB)
	$(BIN) $(CFLAGS) $^ -o _readlines

read: $(TESTDIR)/read.c $(SAFELIB)
	$(BIN) $(CFLAGS) $^ -o _read

input: $(TESTDIR)/input.c $(SAFELIB)
	$(BIN) $(CFLAGS) $^ -o _input
