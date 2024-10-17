#include "copytree.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>

void copySymlinks(const char *src, const char *dest, int copy_symlinks, int copy_permissions) {
    struct stat stat_buf;

    if (lstat(src, &stat_buf) == -1) {
        perror("lstat failed");
        return;
    }

    if (S_ISLNK(stat_buf.st_mode)) {
        char link_target[PATH_MAX + 1];
        ssize_t link_size = readlink(src, link_target, PATH_MAX);
        if (link_size == -1) {
            perror("readlink failed");
            return;
        }

        link_target[link_size] = '\0';
        const char *prefix = "/wsl/localhost/Ubuntu";
        char *adjusted_path = link_target;
        if (strncmp(link_target, prefix, strlen(prefix)) == 0) {
            adjusted_path = link_target + strlen(prefix);
        }

        int fd_src = open(adjusted_path, O_RDONLY);
        if (fd_src == -1) {
            perror("open source file failed");
            return;
        }

        int dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (dest_fd == -1) {
            perror("open new file failed");
            close(fd_src);
            return;
        }

        char buffer[BUFFER_SIZE];
        ssize_t read_bytes;
        while ((read_bytes = read(fd_src, buffer, sizeof(buffer))) > 0) {
            if (write(dest_fd, buffer, read_bytes) != read_bytes) {
                perror("write error");
                close(dest_fd);
                close(fd_src);
                return;
            }
        }

        close(dest_fd);
        close(fd_src);
    } else {
        copy_content(src, dest, copy_permissions);
    }
}
