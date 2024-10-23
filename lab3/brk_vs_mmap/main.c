#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){
	
	write(1,"aici\n",5);
	int *ptr1=malloc(50);
	int *ptr2=malloc(5000000);

	free(ptr1);
	free(ptr2);

	// Fara PROT_WRITE va da segfault 
	int *ptr3 = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	ptr3[0]=4;
	return 0;
}
