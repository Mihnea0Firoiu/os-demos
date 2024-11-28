CC = gcc
FLAGS = -Wall -pedantic

.PHONY: all threads tls

all: threads tls

threads: threads.c
	$(CC) $(FLAGS) $^ -o $@

tls: tls.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm threads tls
