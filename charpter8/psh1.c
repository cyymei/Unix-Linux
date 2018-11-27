#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define ARGLEN 10  /*lines*/
#define ARGMAX 100

char* make_string(char* buf);
void execute_(char* arglist[]);

int main() {
    char* argbuf = (char*)malloc(ARGMAX * sizeof(char));
    char* arglist[ARGLEN];
    int argline;

    argline = 0;
    while (argline < ARGLEN) {
        printf("Arg[%d]: ", argline);
        if(fgets(argbuf, ARGLEN, stdin) != NULL && *argbuf != '\n') {
            arglist[argline] = make_string(argbuf);
            printf("%s\n", argbuf);
            argline++;
        } else {
            if (argline > 0) {
                arglist[argline] = NULL;
                int i;
                for (i = 0; i < argline; i++) {
                    printf("arg[%d]%s\n", i, arglist[i]);
                }
                execute_(arglist);
            }
        }
    }

    free(argbuf);
    return 0;

}

char* make_string(char* buf) {
    buf[strlen(buf)] = '\0';
    return buf;
}

void execute_(char* arglist[]) {
    execvp(arglist[0], arglist);
    perror("execute failed");
    exit(1);
}

