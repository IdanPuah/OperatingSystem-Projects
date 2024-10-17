#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

void setPath(int argc, char *argv[]) {
    int new_path_len = 0;
    for (int i = 1; i < argc; i++) {
        new_path_len += strlen(argv[i]) + 1; // +1 for the colon
    }

    char *current_path = getenv("PATH");
    if (current_path) {
        new_path_len += strlen(current_path) + 1; // +1 for the colon
    }

    char *new_path = malloc(new_path_len + 1); // +1 for the null terminator
    if (!new_path) {
        perror("malloc");
        exit(1);
    }

    new_path[0] = '\0'; // Initialize to an empty string
    for (int i = 1; i < argc; i++) {
        if (i > 1) {
            strcat(new_path, ":");
        }
        strcat(new_path, argv[i]);
    }

    if (current_path) {
        strcat(new_path, ":");
        strcat(new_path, current_path);
    }

    setenv("PATH", new_path, 1);
    free(new_path);
}
