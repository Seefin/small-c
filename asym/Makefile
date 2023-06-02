CC=clang
EXE=keygen
CFLAGS=-I./lib/ -Wall -Wextra -std=c11 -pedantic -ggdb

.PHONY: all
all: $(EXE)

keygen: keygen.c keygen.h lib/BigInt.o
	$(CC) $(CFLAGS) -o keygen keygen.c lib/BigInt.o

lib/BigInt.o: lib/BigInt.c lib/BigInt.h
	$(CC) $(CFLAGS) -c -o lib/BigInt.o lib/BigInt.c

.PHONY: clean
clean:
	rm -rfv $(EXE) lib/BigInt.o

.PHONY: install
install: $(EXE)
	cp -v $(EXE) ~/.local/bin/
