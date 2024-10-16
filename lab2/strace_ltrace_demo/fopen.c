#include <stdio.h>

int main() {
    FILE* f = fopen("test.txt", "w");

    fprintf(f, "Ceva\n");
    fclose(f);
    return 0;
}
