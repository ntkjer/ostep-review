#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        //fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        //child process
        printf("hello i am child (pid:%d)\n", (int) getpid());
    } else {
        //parent goes this path 
        printf("hello i am the parent of %d (pid: %d)\n", rc, (int) getpid());
    }
    return 0;
}
