#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 200

int entry = 1;
char command[MAX_LENGTH];
char line[200];

int main() {
    while (1) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s$ ", cwd);
        } else {
            perror("getcwd() error");
            return 1;
        }

        // Get text from the terminal
        fgets(command, MAX_LENGTH, stdin);

        // Remove the trailing newline character from the command
        command[strcspn(command, "\n")] = 0;

        // Handle "cd" (change directory) command
        if (strncmp(command, "cd ", 3) == 0) {
            char *dir = command + 3; // get the directory
            if (chdir(dir) == 0) {
                printf("Changed directory to: %s\n", dir);
            } else {
                printf("Directory not found!\n");
            }
        } else {
            FILE *output = popen(command, "r");
            if (output) {
                while (fgets(line, 199, output)) {
                    printf("%5d: %s", entry++, line);
                }
                pclose(output);
            } else {
                printf("Error executing command.\n");
            }
        }
    }
    return 0;
}
