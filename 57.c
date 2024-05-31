#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/sysinfo.h>

// sysctl for MacOS

int main() {
    // a. Maximum length of arguments in the exec family of functions.
    printf("a. Maximum length of arguments in exec family of functions: %ld\n", sysconf(_SC_ARG_MAX));

    // b. Maximum number of simultaneous processes per user ID.
    printf("b. Maximum number of simultaneous processes per user ID: %ld\n", sysconf(_SC_CHILD_MAX));

    // c. Number of clock ticks (jiffies) per second.
    printf("c. Number of clock ticks (jiffies) per second: %ld\n", sysconf(_SC_CLK_TCK));

    // d. Maximum number of open files.
    struct rlimit rlim;
    if (getrlimit(RLIMIT_NOFILE, &rlim) == 0) {
        printf("d. Maximum number of open files: %ld\n", rlim.rlim_max);
    } else {
        perror("getrlimit");
    }

    // e. Size of a page.
    printf("e. Size of a page: %ld bytes\n", sysconf(_SC_PAGESIZE));

    // f. Total number of pages in physical memory.
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        printf("f. Total number of pages in physical memory: %ld\n", info.totalram / info.mem_unit);
    } else {
        perror("sysinfo");
    }

    // g. Number of currently available pages in physical memory.
    if (sysinfo(&info) == 0) {
        printf("g. Number of currently available pages in physical memory: %ld\n", info.freeram / info.mem_unit);
    } else {
        perror("sysinfo");
    }

    return 0;
}
