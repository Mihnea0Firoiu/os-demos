#include <stdio.h>
#include <pthread.h>

// Define a thread-local variable using __thread
__thread int thread_local_var = 0;

// Function to be executed by each thread
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    // Each thread modifies its thread-local variable
    thread_local_var = thread_id;

    printf("Thread %d: thread_local_var = %d\n", thread_id, thread_local_var);

    // Perform some computation
    for (int i = 0; i < 5; i++) {
        thread_local_var += 1;
        printf("Thread %d: thread_local_var after increment = %d\n", thread_id, thread_local_var);
    }

    return NULL;
}

int main() {
    const int NUM_THREADS = 3;
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: Execution complete.\n");
    return 0;
}
