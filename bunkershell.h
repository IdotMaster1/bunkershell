#ifndef HEADER_FILE
#define HEADER_FILE

#define MAX_LENGTH 200

int entry = 1;
char command[MAX_LENGTH];
char *token;
char *args[MAX_LENGTH];
char line[MAX_LENGTH];
int arg_count = 0;

// file realated things
char *histfile = ".histfile";

#endif