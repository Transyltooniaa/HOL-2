#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

// Function to read the CPU's time stamp counter (TSC)
static inline uint64_t rdtsc() {
    uint32_t hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)lo) | ((uint64_t)hi << 32);
}

int main() {

    // Get the CPU cycles before and after performing 100 getppid() system calls
    // start and end are 64-bit unsigned integers
    uint64_t start, end;
    int i;

    // Get the start time in CPU cycles. 
    // rdtsc() is an inline assembly function that reads the CPU's time stamp counter (TSC)
    start = rdtsc(); // 

    // Perform 100 getppid() system calls
    for (i = 0; i < 100; ++i) {
        getppid();
    }   

    // Get the end time in CPU cycles
    end = rdtsc(); 

    // Calculate elapsed time in CPU cycles
    uint64_t elapsed_cycles = end - start;

    // Print the elapsed time
    printf("Time taken for 100 getppid() calls: %llu CPU cycles\n", elapsed_cycles);

    return 0;
}


// The error suggests that the output constraint =a used in the assembly code is invalid.
//  This likely indicates an incompatibility between the assembly code and the compiler or platform.