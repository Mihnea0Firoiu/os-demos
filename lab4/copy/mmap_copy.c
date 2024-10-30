#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SRC_FILENAME	"in.txt"
#define DST_FILENAME	"out.txt"

int main() {
    void *src_p, *dst_p;
    int src_fd, dst_fd;
    struct stat statbuf;

    // Open the files.
    src_fd = open(SRC_FILENAME, O_RDONLY);
	dst_fd = open(DST_FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0644);

    // Use fstat to find size of source.
    fstat(src_fd, &statbuf);

    // Truncate size of destination file to the size of the source file. What happens if you don't do that?
    ftruncate(dst_fd, statbuf.st_size);

    // MMAP the files.
    src_p = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
    if (src_p == MAP_FAILED) {
        perror("Error mapping source file");
        close(src_fd);
        close(dst_fd);
        exit(1);
    }

    dst_p = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, dst_fd, 0);
    if (dst_p == MAP_FAILED) {
        perror("Error mapping destination file");
        munmap(src_p, statbuf.st_size);
        close(src_fd);
        close(dst_fd);
        exit(1);
    }

    // Copy the src file.
    memcpy(dst_p, src_p, statbuf.st_size);

    // Unmap the files.
    munmap(src_p, statbuf.st_size);
	munmap(dst_p, statbuf.st_size);

    // Close the files.
    close(src_fd);
	close(dst_fd);
    return 0;
}
