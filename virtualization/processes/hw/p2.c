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


int main(int argc, char *argv[]) {
    int rc = fork();
    int fd = open("./input.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    write(fd, "First \n", strlen("First \n"));
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        write(fd, "child line\n", strlen("child line \n"));
        printf("fd for child:%d\n", fd);
    } else {
        write(fd, "parent line\n", strlen("parent line\n"));
        printf("fd for parent:%d\n", fd);
    }

    FILE *fp;
    fp = fopen("./input.txt", "r");
    int ch;
    printf("file contents: \n");
    while((ch= fgetc(fp)) != EOF) {
        printf("%c",ch);
    }
    printf("\n");
    fclose(fp);
    close(fd);
    return 0;
}
