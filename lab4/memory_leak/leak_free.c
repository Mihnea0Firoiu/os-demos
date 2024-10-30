#include <stdlib.h>

int main() {
    
    char *p = malloc(1024);
    p[0] = 'a';

    free(p);

    return 0;
}
