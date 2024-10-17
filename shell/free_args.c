#include <stdlib.h>
#include "utils.h"

void freeArgs(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}
