#include "copytree.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void copy_content(const char *src, const char *dest, int copy_permissions) {
    int dest_fd;
    int src_fd;
    struct stat stat_buf;

    if ((dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        perror("open new file failed");
        return;
    }

    if ((src_fd = open(src, O_RDONLY)) == -1) {
        perror("open new file failed");
        close(dest_fd);
        return;
    }

    // Check the size of the file
    if (fstat(src_fd, &stat_buf) == -1) {
        perror("fstat failed");
        close(src_fd);
        close(dest_fd);
        return;
    }

    off_t file_size = stat_buf.st_size;

    // Allocate memory to store the file
    char *buffer = (char *)malloc(file_size);
    if (buffer == NULL) {
        perror("malloc failed");
        close(src_fd);
        close(dest_fd);
        return;
    }

    // Read from src to buffer
    ssize_t bytes_read = read(src_fd, buffer, file_size);
    if (bytes_read == -1) {
        perror("read failed");
        free(buffer);
        close(src_fd);
        close(dest_fd);
        return;
    }

    // Write to dest
    ssize_t bytes_write = write(dest_fd, buffer, file_size);
    if (bytes_write == -1) {
        perror("write failed");
        free(buffer);
        close(src_fd);
        close(dest_fd);
        return;
    }

    // Copy permissions if requested
    if (copy_permissions) {
        if (fchmod(dest_fd, stat_buf.st_mode) == -1) {
            perror("fchmod failed");
        }
    }

    free(buffer);
    close(src_fd);
    close(dest_fd);
}
