#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void write_message(const char *message, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s\n", message);
        usleep((rand() % 100) * 1000); // Random delay between 0 and 99 milliseconds
    }
}

void acquire_lock() {
    while (open("lockfile.lock", O_CREAT | O_EXCL | O_WRONLY, 0644) == -1) {
        usleep(1000); // Sleep for 1 millisecond before retrying
    }
}

void release_lock() {
    remove("lockfile.lock");
}



int main(int argc, char *argv[]){
    int forkNumber = argc - 3;
    pid_t pid;
    int status;
    char *message;
    // printf("argc: %d\n", argc);
    int numberOfTimes = atoi(argv[argc-1]);

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <message1> <message2> ... <count>", argv[0]);
        return 1;
    }
    //initial all the fork
    for (int i = 0; i < forkNumber; i++){
        pid = fork();
        if (pid < 0){
            perror("frok faild");
            exit(EXIT_FAILURE);
        }
        if (pid == 0){
            // child process
            message = argv[i+1];
            acquire_lock();
            write_message(message, numberOfTimes);
            release_lock();
            exit(0);
        }
        else{
            // parent process
            wait(&status);
        }
    }
   
    
    message = argv[argc-2];
    acquire_lock();
    write_message(message, numberOfTimes);
    release_lock();
    
    return 0;
}