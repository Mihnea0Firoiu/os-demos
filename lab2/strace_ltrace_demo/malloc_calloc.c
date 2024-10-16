#include <stdio.h>
#include <stdlib.h>

int main() {
    
    char *buf = malloc(1000000 * sizeof(char));
    
    for (int i = 0; i < 1000000; i++) {
        buf[i] = i;
    }

    free(buf);
    
    return 0;
}
