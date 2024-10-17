#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"



void getInput(char **args) {
    char buffer[MAX_LENGTH];
    if (fgets(buffer, MAX_LENGTH, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    }

    char *token = strtok(buffer, " ");
    int i = 0;
    while (token != NULL && i < MAX_COMMANDS - 1) {
        args[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
        if (args[i] == NULL) {
            perror("malloc failed");
            exit(1);
        }
        strcpy(args[i], token);
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
}
