#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    int lsToGrep[2];
    int grepToWc[2];
    pipe(lsToGrep);  //creating a pipe

    int x=fork();       //fork
    if(x==0){
        close(1);  //closing stdout
        close(lsToGrep[0]);     //close read end
        dup2(lsToGrep[1],1);            //duplicating the write end to stdout
        execlp("ls","ls","-l",NULL);
    }
    else{
        pipe(grepToWc);    //creating a pipe
        close(0);  //closing stdin
        int y=fork();
        if(y!=0){   //parent
            close(1);    //closing stdout
            close(lsToGrep[1]);   //closing write end of prev pipe
            close(grepToWc[0]);  //closing read end of new pipe
            dup2(lsToGrep[0],0);   //duplicating the read end to stdin
            dup2(grepToWc[1],1);   //duplicating the write end to stdout
            execlp("grep","grep","^d",NULL);  //executing grep ^d

        }
        else{
            close(lsToGrep[1]);         //closing write end for child
            close(lsToGrep[0]);         //closing read end for child for prev pipe
            close(grepToWc[1]);         //closing write end of new pipe for child
            dup2(grepToWc[0],0);        //duplicating the read end to stdin
            execlp("wc","wc",NULL);         //executing wc
        }
    }
}