CC = gcc
FLAGS = -Wall -pedantic

.PHONY: all hello_c hello_go

all: hello_c hello_go

hello_c: helloworld.c
	$(CC) $(FLAGS) helloworld.c -o helloworld

hello_go: hello_world.go
	go build hello_world.go

clean:
	rm helloworld hello_world
