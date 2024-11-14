#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Shared variable
int shared_variable = 0;

// Number of iterations for each thread
#define ITERATIONS 1000000

// Function executed by each thread
void* increment(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        // Increment the shared variable without a mutex
        shared_variable++;
    }
    return NULL;
}

int main() {
    pthread_t threads[8];

    // Create 8 threads
    for (int i = 0; i < 8; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }

    // Expected value: 8 * ITERATIONS
    printf("Expected value: %d\n", 8 * ITERATIONS);
    printf("Actual value: %d\n", shared_variable);

    return 0;
}
