#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {

        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process executing 'ls' command...\n");
        char *args[] = {"ls", "-l", "-a", NULL};
        execvp("ls", args);

        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process waiting for child to complete...\n");
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally.\n");
        }
    }

    return 0;
}
