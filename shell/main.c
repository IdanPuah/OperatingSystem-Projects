#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    char *original_path = getenv("PATH");

    setPath(argc, argv);
    shell();

    setenv("PATH", original_path, 1);

    return 0;
}
