#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h> 
#include<fcntl.h>
#include<sys/wait.h>

/*
 * Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful
 * when we want more finegrained access as to which child process we would want to wait on in the context of the current process 
 * wait is syntactical sugar for waitpid call: waitpid(-1, &status, 0)
*/


int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        int rc_wait = waitpid(-1, NULL, 0);
        printf("hello i am the child (pid:%d) (rc_wait:%d)\n", (int) getpid(), rc_wait);
    } else {
        printf("goodbye i am the parent (pid:%d)\n",
                (int) getpid());
    }
    return 0;
}
