#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h> 
#include<fcntl.h>
#include<sys/wait.h>

/*
 * Write a program that uses wait for the child process. 
 * what does wait return? wait returns the child before parent
 * What happens if you use wait in the child? 
 * parent will return before the child
 */


int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        int rc_wait = wait(NULL);
        printf("hello i am the child (pid:%d) (rc_wait:%d)\n", (int) getpid(), rc_wait);
    } else {
        printf("goodbye i am the parent (pid:%d)\n",
                (int) getpid());
    }
    return 0;
}
