#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc >0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello i am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc"); //wc prog
        myargs[1] = strdup("p3.c"); // arg: file to count
        myargs[2] = NULL; //NULL terminates stdin stream to os.args
        execvp(myargs[0], myargs); //execute the prog
        printf("you should NOT be seeing this message!");
    } else {
       int rc_wait = wait(NULL);
       printf("hello, i am parent of %d (rc_wait:%d) (pid:%d)\n",
               rc, rc_wait, (int) getpid());
    }
    return 0;
}
