#ifndef COPYTREE_H
#define COPYTREE_H

#ifdef __cplusplus
extern "C" {
#endif
#define BUFFER_SIZE 1024

void copy_content(const char *src, const char *dest, int copy_permissions);
void copySymlinks(const char *src, const char *dest, int copy_symlinks, int copy_permissions);
void copy_file(const char *src, const char *dest, int copy_symlinks, int copy_permissions);
void create_directory_recursive(const char *path);
void copy_directory(const char *src, const char *dest, int copy_symlinks, int copy_permissions);

#ifdef __cplusplus
}
#endif

#endif // COPYTREE_H
