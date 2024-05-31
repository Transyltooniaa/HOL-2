#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>

// Create a FIFO file using mknod

int main() 
{
    printf("Enter file name");
    char filename[100];
    scanf("%s",filename);
    mknod(filename,S_IFIFO|0644,0);   //create a fifo file   in 0644 mode i.e. read and write permission for owner and read permission for others


}