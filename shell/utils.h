#ifndef UTILS_H
#define UTILS_H

#define MAX_COMMANDS 100
#define MAX_LENGTH 100


void execCommand(char **const args);
void freeArgs(char **args);
void getInput(char **args);
void setPath(int argc, char *argv[]);
void changeDirectory(char *path);
void printWorkingDirectory();
void displayHistory(char historylist[MAX_COMMANDS][MAX_COMMANDS], int commandNumber);
void shell();

#endif // UTILS_H
