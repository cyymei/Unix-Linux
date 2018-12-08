#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "smsh2.h"


int main() {
    char* cmdline;
    char** args;
    int result;
    while((cmdline = next_cmd(stdin)) != NULL) {
        if((args = split_line(cmdline)) != NULL) {
            result = process(args);
        }
        if (builtin_commands(args, result)) {

        }
        char** temp_arg = args;
        while(*args != NULL) {
            char** temp = args;
            temp++;
            free(*args);
            args = temp;
        }
        free(temp_arg);
    }
    return 0;
}
