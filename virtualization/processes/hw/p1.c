/*
 *Write a program that calls fork().
  have the main process access a var and set its val to something. 
  1. what val is the var in the child process?
     - The value is the same since heap and stack and static data is copied over to child. 
     - This includes var x and its val, which is stored in an address space. 
  2. What happens to the var when both the child and parent change the value of x?
    - Depends!
    -If we increment before we check for rc val, address space and x val points to same thing.
    -If we increment when we check, the process alreadt received its own copy of address space and x = x and not x`
    -If we increment both, they receive different values. The address spaces are independent so x != `x
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
    printf("called main (pid:%d)\n", (int) getpid());
    int x;
    x = 100;
    int rc = fork();
    x += 3;
    if (rc < 0) {
        printf("fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Hello i am the child (pid:%d), x val is:%d\n", (int) getpid(), x);
        char *myargs[3];
        myargs[0] = strdup("ls");
        myargs[1] = strdup("./");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
        printf("this shouldnt visible");
    } else {
        int rc_wait = wait(NULL);
        printf("hello i am the parent of %d (rc_wait:%d) (pid:%d) and x val is:%d\n",
                rc, rc_wait, (int) getpid(), x);
   }
   return 0;
}
