CC = gcc
FLAGS = -Wall -pedantic

.PHONY: all fork_exec cow_demo

all: fork_exec cow_demo

fork_exec: fork_exec.c
	$(CC) $(FLAGS) $^ -o $@

cow_demo: cow_demo.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm fork_exec cow_demo
