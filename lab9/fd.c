#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILENAME "output.txt"
#define BUFFER_SIZE 256

int main() {
    int fd1, fd2;
    char buffer1[] = "Hello from file descriptor 1\n";
    char buffer2[] = "Hello from file descriptor 2\n";

    // Open the file with the first file descriptor
    fd1 = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1) {
        perror("open fd1");
        exit(EXIT_FAILURE);
    }

    // Duplicate the file descriptor
    fd2 = dup(fd1);
    if (fd2 == -1) {
        perror("dup");
        close(fd1);
        exit(EXIT_FAILURE);
    }

    // Write to the file using the first file descriptor
    if (write(fd1, buffer1, strlen(buffer1)) == -1) {
        perror("write fd1");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // Write to the file using the second file descriptor
    if (write(fd2, buffer2, strlen(buffer2)) == -1) {
        perror("write fd2");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // Close both file descriptors
    close(fd1);
    close(fd2);

    printf("Data written to '%s'. Check the file for the result.\n", FILENAME);
    return 0;
}
