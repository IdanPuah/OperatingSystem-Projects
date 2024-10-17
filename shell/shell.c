#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void shell() {
    char historylist[MAX_COMMANDS][MAX_COMMANDS];
    int commandNumber = 0;
    for (int i = 0; i < MAX_COMMANDS; i++) {
        char **args = (char **)malloc(MAX_COMMANDS * sizeof(char *));
        printf("$ ");
        fflush(stdout);
        getInput(args);

        strcpy(historylist[commandNumber], args[0]); // Add command to history
        commandNumber++;

        if (strcmp(args[0], "history") == 0) {
            displayHistory(historylist, commandNumber);
        } else if (strcmp(args[0], "pwd") == 0) {
            printWorkingDirectory();
        } else if (strcmp(args[0], "cd") == 0) {
            changeDirectory(args[1]);
        } else if (strcmp(args[0], "exit") == 0) {
            exit(0);
        } else {
            execCommand(args);
        }

        freeArgs(args);
    }
}
