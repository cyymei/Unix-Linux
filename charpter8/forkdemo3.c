#include <stdio.h>

int main() {
    int ret_from_fork, mypid;
    mypid = getpid();
    printf("Before: my pid is %d\n", mypid);

    ret_from_fork = fork();
    sleep(1);
    if (ret_from_fork == -1) {
        perror("fork failed!");
    } else if (ret_from_fork == 0) {
        printf("Child, pid is %d\n", getpid());
    } else {
        printf("Parent, pid is %d\n", getpid());
    }
    return 0;
}