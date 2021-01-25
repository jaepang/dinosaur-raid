#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int sig) {
    printf("BEEP\n");
}

int main() {
    signal(SIGALRM, handler);
    while(1) {
        alarm(1);
        sleep(1);
    }
}