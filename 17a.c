/*
============================================================================
Name : 17a.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to execute ls -l | wc.
                a. use dup
                b. use dup2
                c. use fcntl
Date: 20 Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>

void main(){
    int pipefd[2];
    pid_t cid;

    if(pipe(pipefd)==-1){
        printf("ERROR");
    }else{
        cid=fork();
        if(cid==0){
            // closing standard input
            close(0);
            // reassigning stdin to pipe reading end;
            // dup will reassign pipefd[0] to 0 as it is the lowest available fd, so now pipefd[0] will act as STDIN
            dup(pipefd[0]);
            close(pipefd[1]); // closing unused pipe writing end
            execlp("wc", "wc", NULL);
        }else{
            close(1); // closing stdout 
            dup(pipefd[1]); // reassigning stdout to pipe writing end
            // dup will reassign pipefd[1] to 1 (STDOUT) as it is the lowest available fd, so now pipefd[1] will act as STDOUT
            close(pipefd[0]); // closing unused reading end

            execlp("ls", "ls", "-l", NULL);
        }
    }
}

/*
============================================================================
Command line: cc 17a.c && ./a.out
Output:     59     524    4034
============================================================================
*/
