#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define PAGE_SIZE 4096  // Typically 4KB
#define ALLOC_SIZE (PAGE_SIZE * 2)  // Allocate 2 pages

void print_memory_mapping(pid_t cpid, unsigned long addr) {
    char command[256];
    snprintf(command, sizeof(command), "sudo ./pagemap/pagemap %d 0x%lx 0x%lx", cpid, addr, addr + ALLOC_SIZE);
    // printf("%s", command);
    system(command);
}

int main() {
    // Allocate memory using mmap
    unsigned char *mem = mmap(NULL, ALLOC_SIZE, PROT_READ | PROT_WRITE,
                              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    printf("Memory allocated at: %p\n", mem);

    // Fill the memory with a pattern
    memset(mem, 0xAA, ALLOC_SIZE);

    printf("Initial memory state:\n");
    print_memory_mapping(getpid(), (unsigned long)mem);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("\n[Child] Before modification:\n");
        print_memory_mapping(getpid(), (unsigned long)mem);

        // Modify memory in child
        mem[0] = 0xBB;

        printf("\n[Child] After modification:\n");
        print_memory_mapping(getpid(), (unsigned long)mem);

        // Cleanup
        munmap(mem, ALLOC_SIZE);
        exit(0);
    } else {
        // Parent process
        wait(NULL);  // Wait for child to finish
        printf("\n[Parent] After child modifies memory:\n");
        print_memory_mapping(getpid(), (unsigned long)mem);

        // Cleanup
        munmap(mem, ALLOC_SIZE);
    }

    return 0;
}
