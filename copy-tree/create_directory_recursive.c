#include "copytree.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void create_directory_recursive(const char *path) {
    char *sub_path = strdup(path);
    if (!sub_path) {
        perror("strdup failed");
        return;
    }

    char *last_slash = sub_path + strlen(sub_path) - 1;
    while (*last_slash == '/' && last_slash != sub_path) {
        *last_slash-- = '\0';
    }

    for (char *slash = strchr(sub_path + 1, '/'); slash; slash = strchr(slash + 1, '/')) {
        *slash = '\0';
        struct stat st;
        if (stat(sub_path, &st) == -1 || !S_ISDIR(st.st_mode)) {
            if (mkdir(sub_path, 0755) == -1) {
                perror("mkdir failed");
                free(sub_path);
                return;
            }
        }
        *slash = '/';
    }

    struct stat st;
    if (stat(sub_path, &st) == -1 || !S_ISDIR(st.st_mode)) {
        if (mkdir(sub_path, 0755) == -1) {
            perror("mkdir failed");
        }
    }

    free(sub_path);
}
