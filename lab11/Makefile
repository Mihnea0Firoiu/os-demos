CC = gcc
FLAGS = -Wall -pedantic

.PHONY: epoll_server client

all: epoll_server client

epoll_server: epoll_server.c
	$(CC) $(FLAGS) $^ -o $@

client: client.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm epoll_server client
