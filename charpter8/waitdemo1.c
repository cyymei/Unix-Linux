#include <stdio.h>

#define DELAY 2

void child_code();
void parent_code(int);

int main() {
    int ret_from_fork, mypid;
    mypid = getpid();
    printf("Before: my pid is %d\n", mypid);

    ret_from_fork = fork();
    sleep(1);
    if (ret_from_fork == -1) {
        perror("fork failed!");
    } else if (ret_from_fork == 0) {
        printf("child pid: %d\n", getpid());
        child_code();;
    } else {
        printf("parent pid: %d\n", getpid());
        parent_code(ret_from_fork);
    }
    return 0;
}

void child_code() {
    printf("child_code\n");
    sleep(DELAY);
    exit(17);
}

void parent_code(int newpid) {
    printf("parent_code\n");
    int wait_ret;
    wait_ret = wait(NULL);
    printf("newpid: %d, now pid: %d returns: %d\n", newpid, getpid(), wait_ret);
}