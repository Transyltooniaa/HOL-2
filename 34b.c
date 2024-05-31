#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){   //executing ls -l and wc
    int fd[2];
    pipe(fd);
    int x=fork();
    if(x==0){
        close(1);
        close(fd[0]);
        dup2(fd[1],1);
        execlp("ls","ls","-l",NULL);
    }
    else{
        close(0);
        close(fd[1]);
        dup2(fd[0],0);
        execlp("wc","wc",NULL);
    }

}