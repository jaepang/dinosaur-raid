#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>

char bc[20] = "/usr/bin/bc";
char echo[20] = "/usr/bin/echo";

int main() {
    int n, fd[2];
    char *argecho[3] = {"echo", "124 * (42 + 3) % 17", 0};
    char *argbc[2] = {"bc", 0};
    pid_t pid;

    if(pipe(fd) < 0)    
        exit(1);
    if((pid=fork()) < 0)
        exit(2);

    if(pid > 0) { // parent
        close(fd[0]);
        dup2(fd[1], 1);
        execv(echo, argecho);
    } else { // child
        close(fd[1]);
        dup2(fd[0], 0);
        execv(bc, argbc);
    }
    
    return 0;
}