CC = gcc
FLAGS = -Wall -pedantic

.PHONY: all scanf_printf malloc_calloc fopen

all: scanf_printf malloc_calloc fopen

scanf_printf: scanf_printf.c
	$(CC) $(FLAGS) scanf_printf.c -o scanf_printf

malloc_calloc: malloc_calloc.c
	$(CC) $(FLAGS) malloc_calloc.c -o malloc_calloc

fopen: fopen.c
	$(CC) $(FLAGS) fopen.c -o fopen

clean:
	rm scanf_printf malloc_calloc fopen
