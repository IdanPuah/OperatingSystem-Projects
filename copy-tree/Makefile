CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c copy_content.c copy_symlinks.c copy_file.c create_directory_recursive.c copy_directory.c
OBJ = $(SRC:.c=.o)
TARGET = copytree

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
