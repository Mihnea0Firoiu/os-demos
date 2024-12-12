CC = gcc
FLAGS = -Wall -pedantic

.PHONY: all server server_unix client client_unix

all: server server_unix client client_unix

server: server.c
	$(CC) $(FLAGS) $^ -o $@

client: client.c
	$(CC) $(FLAGS) $^ -o $@

server_unix: server_unix.c
	$(CC) $(FLAGS) $^ -o $@

client_unix: client_unix.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm server client client_unix server_unix
