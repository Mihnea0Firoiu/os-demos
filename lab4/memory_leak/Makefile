CC = gcc
FLAGS = -Wall -pedantic

.PHONY: all definitely_lost leak_free still_reachable

all: definitely_lost leak_free still_reachable

definitely_lost: definitely_lost.c
	$(CC) $(FLAGS) $^ -o $@

leak_free: leak_free.c
	$(CC) $(FLAGS) $^ -o $@

still_reachable: still_reachable.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm definitely_lost still_reachable leak_free
