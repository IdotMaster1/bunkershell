/*     Copyright (C) 2023 IdotMaster1

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 200

int entry = 1;
char command[MAX_LENGTH];
char line[200];

// files
char *histfile = ".histfile";

int main() {

    FILE *hf = fopen(histfile, "a"); // Open the histfile in append mode

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

        fprintf(hf, "%s\n", command); // Write the command to histfile
        fflush(hf);

    }

    fclose(hf); // Close the histfile

    return 0;
}