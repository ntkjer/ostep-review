#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h> 
#include<fcntl.h>
#include<sys/wait.h>

/*
 * write a program that calls fork() then exec to run /bin/ls
 * try different variants of the exec command 
 * why are there different variants of the same exec call?
 * There are different variants of the same call because each one accepts different types.
 * execvp accepts a vector with the last item as the NULL terminator.
 * execl accepts a list of args with the first being the path to the program, n args, and NULL as [-1].
 * execle falls in the same category as above, as well as the execlp call.
 * execv and execvp are basically the same
 *E: The versions with an 'e' at the end let you additionally pass an array of char* that are a set of strings added to the spawned processes environment before the exec'ed program launches. Yet another way of passing parameters, really.

P: The versions with 'p' in there use the environment variable PATH to search for the executable file named to execute. The versions without the 'p' require an absolute or relative file path to be prepended to the filename of the executable if it is not in the current working directory
 */


int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello i am the child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("/bin/ls");
        myargs[1] = strdup(".");
        myargs[2] = NULL;
        execvpe(myargs[0], myargs);
        //execl("/bin/ls", ".", NULL);
        //execlp("/bin/ls", ".", NULL);
    } else {
        int rc_wait = wait(NULL);
        printf("goodbye i am the parent of %d (rc_wait:%d) (pid:%d)\n",
                rc, rc_wait, (int) getpid());
    }
    return 0;
}
