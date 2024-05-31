#include <stdio.h>
#include <sys/resource.h>

void print_resource_limit(int resource) {
    struct rlimit rlim;
    
    // Get resource limit
    if (getrlimit(resource, &rlim) == 0) {
        printf("Resource: ");
        switch (resource) {

            // RLIMIT_CORE: Maximum size of core dump file a process can create when it terminates abnormally (in bytes)
            case RLIMIT_CORE:
                printf("Core file size (bytes)\n");
                break;

            // RLIMIT_CPU: Maximum amount of CPU time a process can consume (in seconds). When the soft limit is reached, the process receives a SIGXCPU signal and is sent a SIGKILL signal when the hard limit is reached.
            case RLIMIT_CPU:
                printf("CPU time (seconds)\n");
                break;

            // RLIMIT_DATA: Maximum size of the data segment of a process (in bytes)
            case RLIMIT_DATA:
                printf("Data segment size (bytes)\n");
                break;

            // RLIMIT_FSIZE: Maximum size of a file that a process can create (in bytes)
            case RLIMIT_FSIZE:
                printf("File size (bytes)\n");
                break;

            // RLIMIT_NOFILE: Maximum number of open files a process can have
            case RLIMIT_NOFILE:
                printf("Number of open files\n");
                break;

            // RLIMIT_STACK: Maximum size of the stack segment of a process (in bytes)
            case RLIMIT_STACK:
                printf("Stack size (bytes)\n");
                break;

            // Default case
            default:
                printf("Unknown resource\n");
                break;
        }

        // Print soft and hard limits
        // Soft limit: Current limit for the resource. It can be increased or decreased by the process within the constraints of the hard limit.
        // Hard limit: Maximum value that the soft limit can be set to
        printf("Soft limit: %llu\n", rlim.rlim_cur);
        printf("Hard limit: %llu\n", rlim.rlim_max);
    } else {
        printf("Failed to get resource limit\n");
    }
}

int main() {
    // Print resource limits for various resources
    print_resource_limit(RLIMIT_CORE);
    print_resource_limit(RLIMIT_CPU);
    print_resource_limit(RLIMIT_DATA);
    print_resource_limit(RLIMIT_FSIZE);
    print_resource_limit(RLIMIT_NOFILE);
    print_resource_limit(RLIMIT_STACK);

    return 0;
}


// Resource limits, often referred to as resource ulimits, are constraints imposed by the operating system on the amount of resources a process can consume. 