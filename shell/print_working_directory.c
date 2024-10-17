#include <stdio.h>
#include <unistd.h>
#include "utils.h"


void printWorkingDirectory() {
    char cwd[MAX_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd failed");
    }
}
