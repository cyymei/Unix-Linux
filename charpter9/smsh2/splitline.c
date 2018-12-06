#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFSIZE 200
#define SINGBUF 15

bool is_delim(char c);

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
                buf = malloc(BUFSIZE * sizeof(char));
                memset(buf, 0, sizeof(buf));
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
    char*  cp;
    int    argpos;
    char*  singarg;
    int    sigpos;
    int    argspos;

    cp      = line;
    sigpos  = 0;
    argpos = 0;
    args   = malloc(BUFSIZE * sizeof(char));
    singarg = (char*)malloc(SINGBUF * sizeof(char));

    while(cp != NULL) {
        while(is_delim(*cp)) {
            if (sigpos == 0) {
                cp++;
            } else {
                singarg[sigpos++] = '\0';
                args[argpos++] = singarg;
                singarg = (char*)malloc(SINGBUF * sizeof(char));
                memset(singarg, 0, sizeof(singarg));
                sigpos = 0;
            }
        }
        if (*cp == '\0') {
            args[argpos++] = singarg;
            break;
        }
        singarg[sigpos++] = *cp;
        cp++;
    }
    free(line);

    args[argpos] = NULL;

    return args;
}

