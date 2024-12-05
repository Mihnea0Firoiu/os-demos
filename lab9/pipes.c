#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();

    if (pid == -1) {
        // Error forking
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        close(pipefd[1]); // Close the write end of the pipe

        // Read data from the pipe
        ssize_t numBytes = read(pipefd[0], buffer, BUFFER_SIZE);
        if (numBytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the data read from the pipe
        buffer[numBytes] = '\0';
        printf("Child received: %s\n", buffer);

        close(pipefd[0]); // Close the read end of the pipe
    } else {
        // Parent process
        close(pipefd[0]); // Close the read end of the pipe

        // Generate some data
        char data[] = "Hello from the parent process!";

        // Write data to the pipe
        if (write(pipefd[1], data, strlen(data)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]); // Close the write end of the pipe

        // Wait for the child process to complete
        wait(NULL);
    }

    return 0;
}
