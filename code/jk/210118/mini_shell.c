#include <unistd.h>
#include <string.h>

int main() {
    int i;
    char *cmd, *ptr, *arg[100], path[100];
    size_t size;

    while (1) {
        i = 0;
        getline(&cmd, &size, stdin);
        cmd[strlen(cmd)-1] = '\0';
        ptr = strtok(cmd, " ");
        while(ptr != NULL) {
            arg[i++] = ptr;
            ptr = strtok(NULL, " ");
        }
        arg[i] = NULL;
        sprintf(path, "/bin/%s", arg[0]);
        if(fork() == 0)
            execv(path, arg);
        wait(NULL);
    }
}