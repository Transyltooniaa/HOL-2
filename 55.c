#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h> // Added for strerror()

int main() {
    struct rlimit rlim;

    // Get and print old limits
    printf("Old limits for RLIMIT_CPU:\n");
    if (getrlimit(RLIMIT_CPU, &rlim) == 0) {
        printf("Soft limit: %llu\n", rlim.rlim_cur);
        printf("Hard limit: %llu\n", rlim.rlim_max);
    } else {
        fprintf(stderr, "Failed to get old limits: %s\n", strerror(errno));
        return 1;
    }

    // Set new limits
    rlim.rlim_cur = 2;
    rlim.rlim_max = 3;

    if (setrlimit(RLIMIT_CPU, &rlim) != -1) {
        // Get and print new limits
        printf("\nNew limits for RLIMIT_CPU:\n");
        if (getrlimit(RLIMIT_CPU, &rlim) == 0) {
            printf("Soft limit: %llu\n", rlim.rlim_cur);
            printf("Hard limit: %llu\n", rlim.rlim_max);
        } else {
            fprintf(stderr, "Failed to get new limits: %s\n", strerror(errno));
            return 1;
        }
    } else {
        fprintf(stderr, "Failed to set new limits: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
