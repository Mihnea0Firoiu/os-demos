CC = gcc
FLAGS = -Wall -pedantic

.PHONY: all pipes fd

all: pipes fd

pipes: pipes.c
	$(CC) $(FLAGS) $^ -o $@

fd: fd.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm pipes fd
