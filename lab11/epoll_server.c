#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024
#define PORT 12345

int main() {
    int server_fd, epoll_fd, new_client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    struct epoll_event event, events[MAX_EVENTS];

    char buffer[BUFFER_SIZE];

    // Create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set server socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Bind server socket
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen on the socket
    if (listen(server_fd, 10) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Create epoll instance
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Add server socket to epoll instance
    event.events = EPOLLIN;
    event.data.fd = server_fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
        perror("epoll_ctl");
        close(server_fd);
        close(epoll_fd);
        exit(EXIT_FAILURE);
    }

    // Add stdin to epoll instance
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        perror("epoll_ctl (stdin)");
        close(server_fd);
        close(epoll_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d. Type 'exit' to shut down.\n", PORT);

    // Event loop
    while (1) {
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1) {
            perror("epoll_wait");
            close(server_fd);
            close(epoll_fd);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < num_events; i++) {
            if (events[i].data.fd == server_fd) {
                // Accept new client connections
                new_client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                if (new_client_fd == -1) {
                    perror("accept");
                    continue;
                }

                event.events = EPOLLIN | EPOLLET;
                event.data.fd = new_client_fd;

                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_client_fd, &event) == -1) {
                    perror("epoll_ctl");
                    close(new_client_fd);
                    continue;
                }

                printf("New client connected: FD=%d\n", new_client_fd);

            } else if (events[i].data.fd == STDIN_FILENO) {
                // Handle stdin input
                if (fgets(buffer, BUFFER_SIZE, stdin)) {
                    if (strncmp(buffer, "exit", 4) == 0) {
                        printf("Shutting down server...\n");
                        close(server_fd);
                        close(epoll_fd);
                        return 0;
                    }
                }

            } else if (events[i].events & EPOLLIN) {
                // Handle client input
                int client_fd = events[i].data.fd;
                int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);

                if (bytes_read <= 0) {
                    if (bytes_read == 0) {
                        printf("Client disconnected: FD=%d\n", client_fd);
                    } else {
                        perror("read");
                    }
                    close(client_fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
                } else {
                    buffer[bytes_read] = '\0';
                    printf("Received from client FD=%d: %s\n", client_fd, buffer);

                    // Echo message back to client
                    if (write(client_fd, buffer, bytes_read) == -1) {
                        perror("write");
                        close(client_fd);
                        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
                    }
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    return 0;
}
