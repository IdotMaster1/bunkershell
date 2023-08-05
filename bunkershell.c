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
#include <sys/types.h>
#include <sys/wait.h>

#include "bunkershell.h"

int main() {

    FILE *hf = fopen(histfile, "a"); // Open the histfile in append mode

    while (1) {

    printf("$ ");

        // Get text from the terminal
        fgets(command, MAX_LENGTH, stdin);

        // Remove the trailing newline character from the command
        command[strcspn(command, "\n")] = 0;

        // tokenize the command
        token = strtok(command, " ");
        while (token != NULL){
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }

        // set the last part of "args" to NULL, as needed by execvp
        args[arg_count] = NULL;

        if (fork() == 0) {
            if (strncmp(command, "cd ", 3) == 0) {
                char *dir = command + 3; // get the directory
                if (chdir(dir) == 0) {
                    printf("Changed directory to: %s\n", dir);
                } else {
                    perror(chdir);
                }
            } else {
                execvp(args[0], args);
            }
        }

        fprintf(hf, "%s\n", command); // Write the command to histfile
        fflush(hf);

    }

    fclose(hf); // Close the histfile

    return 0;
}