#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char *command;
    char *args[] = {NULL};
    int status;

    while (1) {
        // Display prompt and get user input
        printf("#cisfun$ ");
        command = (char *) malloc(MAX_COMMAND_LENGTH * sizeof(char));
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Remove trailing newline character
        command[strlen(command) - 1] = '\0';

        // Fork a new process to execute the command
        if (fork() == 0) {
            // Execute the command
            execvp(command, args);
            // If the command couldn't be executed, print an error message and exit
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        } else {
            // Wait for the child process to finish
            wait(&status);
        }

        // Free allocated memory
        free(command);
    }

    return 0;
}
