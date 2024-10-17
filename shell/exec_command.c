#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execCommand(char **const args) {
    pid_t pid = fork();
    int stat;
    if (pid < 0) {
        perror("fork failed");
    }
    if (pid == 0) { // child
        execvp(args[0], args);
        perror("execvp failed");
        _exit(1);
    } else if (pid > 0) {
        wait(&stat);
    }
}
