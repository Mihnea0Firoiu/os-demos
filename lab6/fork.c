#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    pid_t ppid;
    pid_t my_pid;

    printf("Test - \n");

    pid = fork();

    // child
    if (pid == 0) {

        sleep(5);

        ppid = getppid();
        my_pid = getpid();

        printf("child, child pid %d, pid %d, ppid %d\n", pid, my_pid, ppid);

        exit(0);

    //parent
    } else if (pid > 0) {
        
        ppid = getppid();
        my_pid = getpid();

        printf("parent, child pid %d, pid %d, ppid %d\n", pid, my_pid, ppid);
   
        // wait(NULL);
    } else {
        // error (see man)
        exit(1);
    }
}
