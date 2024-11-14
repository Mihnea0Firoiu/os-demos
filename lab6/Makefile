CC = gcc
FLAGS = -Wall -pedantic

.PHONY: all fork threads

all: fork threads

fork: fork.c
	$(CC) $(FLAGS) $^ -o $@

threads: threads.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm fork threads
