#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h> 
#include<fcntl.h>
#include<sys/wait.h>

/*
 * Write a program that opens a file with open() and then calls fork()
 * Can both the child and parent access the open fd returned by open()?
 * - No. The first process, which is the child, blocks fd from parent.
 * What happens when they are writing to the file concurrently?
 * -
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {
        pid_t rc = fork();
        if (rc < 0) {
                    // fork failed; exit
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            printf("child calls printf().");
            close(STDOUT_FILENO); 
        }
            return 0;
            
}
