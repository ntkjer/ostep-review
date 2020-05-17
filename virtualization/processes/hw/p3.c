#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h> 
#include<fcntl.h>
#include<sys/wait.h>

/*
 * Write another program using fork. The child process should print hello.
 * the parent should print goodbye
 * make the child process print first, can it be done without wait?
 * - No? 
 */


int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello i am the child (pid:%d)\n", (int) getpid());
    } else {
        int rc_wait = wait(NULL);
        printf("goodbye i am the parent of %d (rc_wait:%d) (pid:%d)\n",
                rc, rc_wait, (int) getpid());
    }
    return 0;
}
