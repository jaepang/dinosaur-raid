#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int is_child = 0;
pid_t child_pid;
pid_t parent_pid;

void handler(int sig) {
    pid_t id;
    if(is_child) {
        for(int i=0; i<5; i++) {
            printf("BEEP\n");
            sleep(1);
        }
        printf("I'm Alive!\n");
        kill(parent_pid, SIGUSR2);
        exit(1);
    }
    else {
        pause();
    }
}

void usrHandler(int sig) {
    exit(0);
}

int main() {
    pid_t pid;
    signal(SIGINT, handler);
    signal(SIGUSR2, usrHandler);
    pid = fork();
    if(pid == 0) {
        is_child = 1;
    }
    else {
        parent_pid = pid;
    }
    while(1) {
        sleep(1);
    }
    return 0;
}
