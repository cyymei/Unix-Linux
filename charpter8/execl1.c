#include <stdlib.h>
#include <stdio.h>
int main() {
    char* arglist[3];
    arglist[0] = "ls";
    arglist[1] = "-l";
    arglist[2] = 0;
    execvp("ls", arglist);
    return 0;
}