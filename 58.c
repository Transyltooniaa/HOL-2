#include <stdio.h>
#include <pthread.h>

// Function to be executed by each thread
void *thread_function(void *arg) {
    printf("Thread ID: %ld\n", (long)pthread_self());
    return NULL;
}

// Function to create a thread with error handling
int create_thread(pthread_t *thread, void *(*start_routine)(void *)) {
    if (pthread_create(thread, NULL, start_routine, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }
    return 0;
}

// Function to join a thread with error handling
int join_thread(pthread_t thread) {
    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }
    return 0;
}

int main() {
    pthread_t threads[3];
    int i;

    // Create three threads
    for (i = 0; i < 3; i++) {
        if (create_thread(&threads[i], thread_function) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < 3; i++) {
        if (join_thread(threads[i]) != 0) {
            fprintf(stderr, "Error joining thread %d\n", i);
            return 1;
        }
    }

    return 0;
}
