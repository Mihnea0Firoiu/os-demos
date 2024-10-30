CC = gcc
FLAGS = -Wall -pedantic

.PHONY: all mmap_copy

all: mmap_copy

mmap_copy: mmap_copy.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm mmap_copy
