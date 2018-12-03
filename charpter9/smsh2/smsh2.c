#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

extern char* next_cmd(FILE* fp);
extern char** split_line(char* line);
int main() {
    char* lines = next_cmd(stdin);
    char** arg = split_line(lines);
    excute_args(arg);
    while(*arg != NULL) {
        char** temp = arg;
        temp++;
        free(*arg);
        arg = temp;
    }
    return 0;
}