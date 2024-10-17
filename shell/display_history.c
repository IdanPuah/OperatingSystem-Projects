#include <stdio.h>
#include "utils.h"


void displayHistory(char historylist[MAX_COMMANDS][MAX_COMMANDS], int commandNumber) {
    for (int i = 0; i < commandNumber; i++) {
        printf("%s\n", historylist[i]);
    }
}
