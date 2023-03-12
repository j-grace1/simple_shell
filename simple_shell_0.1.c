#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    char buffer[BUFFER_SIZE];
    char *args[2];
    int status;

    while (1) {
        // Display prompt
        printf("#cisfun$ ");

        // Get user input
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            break;
        }

        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Execute command
        args[0] = buffer;
        args[1] = NULL;

        if (fork() == 0) {
            execve(args[0], args, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            wait(&status);
        }
    }

    return 0;
}