CC=clang
EXE=keygen
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

.PHONY: all
all: $(EXE)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -rfv $(EXE)

.PHONY: install
install: $(EXE)
	cp -v $(EXE) ~/.local/bin/
