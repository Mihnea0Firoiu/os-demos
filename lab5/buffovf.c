#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define OP(c) c ^ 119

char flag[] = { 40, 40, 17, 27, 67, 16, 40, 25, 24, 3, 40, 4, 18, 20, 2, 5, 18, 40, 22, 3, 40, 22, 27, 27, 40, 40, 119 };

void for_the_win() {
	for (int i = 0; OP(flag[i]); ++i) {
		printf("%c", OP(flag[i]));
	}
	printf("\n");
}

void acquire_info() {
	char name[13];

	printf("what's ur name?\n");
	gets(name);

	printf("bye\n");
}

int main(int argc, char **argv) {

	acquire_info();

	printf("func addr was: %p\n", for_the_win);

	return 0;
}
