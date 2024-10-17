#include "copytree.h"

void copy_file(const char *src, const char *dest, int copy_symlinks, int copy_permissions) {
    if (copy_symlinks) {
        copySymlinks(src, dest, copy_symlinks, copy_permissions);
    } else {
        copy_content(src, dest, copy_permissions);
    }
}
