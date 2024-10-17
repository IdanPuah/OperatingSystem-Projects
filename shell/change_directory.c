#include <stdio.h>
#include <unistd.h>
#include "utils.h"

void changeDirectory(char *path) {
    if (chdir(path) == -1) {
        perror("cd failed");
    }
}
