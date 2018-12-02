#include <stdlib.h>

extern void excute_args(char** arglist) {
    int pid, exitstatus;

    pid = fork();
    switch(pid) {
        case -1: {
            perror("fork failed!");
            exit(1);
            break;
        }
        case 0: {
            execvp(arglist[0], arglist);
            perror("execute failed");
            exit(1);
            break;
        }
        default: {
            while(wait(&exitstatus) != pid)
                ;
            // printf("child exit with status: %d, %d\n", exitstatus >> 8, exitstatus & 0377);
            break;
        }
    }
}