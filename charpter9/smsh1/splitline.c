#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFSIZE 200

char* next_cmd(FILE* fp);
char** split_line(char* line);
bool is_delim(char c);

int main() {
    char* lines;
    lines = next_cmd(stdin);
    printf("%s\n", lines);
    return 0;
}

char* next_cmd(FILE* fp) {
    int   sapce;
    char  c;
    char* buf;
    int   pos;

    sapce = 0;
    pos   = 0;

    while((c = getc(fp)) != EOF) {
        if (pos + 1 >= sapce) {
            if (sapce == 0) {
                buf = (char*)malloc(BUFSIZE * sizeof(char));
            } else {
                buf = realloc(buf, (BUFSIZE + sapce) * sizeof(char));
            }
            sapce += BUFSIZE;
            if (buf == NULL)  {
                perror("realloc memory failed!");
                exit(1);
            }
        }
        if (c == '\n')
            break;

        buf[pos++] = c;
    }

    if (c == EOF || pos == 0)
        return NULL;

    buf[pos] = '\0';

    return buf;
}

bool is_delim(char c) {
    if (c == ' ' || c == '\t')
        return true;
    return false;
}

char** split_line(char* line) {
    char** args;
    char* cp;
    int argpos;
    char singarg[BUFSIZE];
    int sigpos;
    int argspos;


    if (line == NULL)
        return NULL;

    cp      = line;
    sigpos  = 0;
    argspos = 0;
    *args   = (char*)malloc(BUFSIZE * sizeof(char));
    //singarg = (char*)malloc(BUFSIZE * sizeof(char));

    while(cp != NULL) {
        if(is_delim(*cp)) {
            if (sigpos == 0) {
                cp++;
            } else {
                args[argpos++] = singarg;
                sigpos = 0;
            }
        }
        if (*cp = '\0')
            break;
        singarg[sigpos++] = *cp;

    }

    return args;
}