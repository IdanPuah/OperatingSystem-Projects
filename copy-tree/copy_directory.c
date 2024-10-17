#include "copytree.h"
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>

void copy_directory(const char *src, const char *dest, int copy_symlinks, int copy_permissions) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;

    if (!(dir = opendir(src))) {
        perror("opendir failed");
        return;
    }

    create_directory_recursive(dest);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char src_path[PATH_MAX];
        char dest_path[PATH_MAX];
        snprintf(src_path, PATH_MAX, "%s/%s", src, entry->d_name);
        snprintf(dest_path, PATH_MAX, "%s/%s", dest, entry->d_name);

        if (stat(src_path, &st) == 0 && S_ISDIR(st.st_mode)) {
            copy_directory(src_path, dest_path, copy_symlinks, copy_permissions);
        } else {
            copy_file(src_path, dest_path, copy_symlinks, copy_permissions);
        }
    }

    closedir(dir);
}
