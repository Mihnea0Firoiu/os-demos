CC = gcc
LDFLAGS_STATIC = -static

.PHONY: all main

all: main main_static main_dynamic

main: main.c

main_static: main.c
	$(CC) $(LDFLAGS_STATIC) -o $@ $^

main_dynamic: main.c
	$(CC) -o $@ $^

clean:
	rm -f main_static main_dynamic main
