#include <stdio.h>
#include <signal.h>

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
        child_code();
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
    int child_status;
    int high_8, low_7, bit_7;
    int wait_ret;
    wait_ret = wait(&child_status);
    printf("newpid: %d, now pid: %d returns: %d\n", newpid, getpid(), wait_ret);
    high_8 = child_status >> 8;
    low_7 = child_status & 0b01111111;
    bit_7 = child_status & 0b01000000;
    printf("exit: %d, sig: %d, core: %d\n", high_8, low_7, bit_7);
}