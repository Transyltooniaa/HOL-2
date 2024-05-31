#include <stdio.h>
#include <pthread.h>
#include <dispatch/dispatch.h> // Include for dispatch semaphores
#include <unistd.h>

// Semaphores
dispatch_semaphore_t semaphore_A;
dispatch_semaphore_t semaphore_B;

// Function for thread 1
void *thread_function_1(void *arg) {
    dispatch_semaphore_wait(semaphore_A, DISPATCH_TIME_FOREVER); // Acquire semaphore A
    printf("Thread 1 acquired semaphore A\n");
    sleep(1); // Introduce delay to simulate work

    dispatch_semaphore_wait(semaphore_B, DISPATCH_TIME_FOREVER); // Attempt to acquire semaphore B
    printf("Thread 1 acquired semaphore B\n");

    // Critical section
    // Do something with both resources

    dispatch_semaphore_signal(semaphore_B); // Release semaphore B
    dispatch_semaphore_signal(semaphore_A); // Release semaphore A

    pthread_exit(NULL);
}

// Function for thread 2
void *thread_function_2(void *arg) {
    dispatch_semaphore_wait(semaphore_B, DISPATCH_TIME_FOREVER); // Acquire semaphore B
    printf("Thread 2 acquired semaphore B\n");
    sleep(1); // Introduce delay to simulate work

    dispatch_semaphore_wait(semaphore_A, DISPATCH_TIME_FOREVER); // Attempt to acquire semaphore A
    printf("Thread 2 acquired semaphore A\n");

    // Critical section
    // Do something with both resources

    dispatch_semaphore_signal(semaphore_A); // Release semaphore A
    dispatch_semaphore_signal(semaphore_B); // Release semaphore B

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Initialize semaphores
    semaphore_A = dispatch_semaphore_create(1);
    semaphore_B = dispatch_semaphore_create(1);

    // Create threads
    pthread_create(&thread1, NULL, thread_function_1, NULL);
    pthread_create(&thread2, NULL, thread_function_2, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Dispatch semaphores do not require destruction

    return 0;
}


// In this program there are 2 cases:
// 1. Deadlock: If thread 1 acquires semaphore A and thread 2 acquires semaphore B, both threads will be blocked waiting for the other semaphore to be released. This results in a deadlock.
// if thread1 aquires both semaphore A and B, and thread2 aquires both semaphore B and A, then deadlock will occur.