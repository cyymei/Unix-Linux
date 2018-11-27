#include <stdio.h>
#include <signal.h>
void wakeup();
int main() {
	printf("Sleep 4 seconds...\n");
	signal(SIGALRM, wakeup);
	alarm(4);
	pause();
	printf("return\n");
	return 0;
}
void wakeup() {
	printf("Received from kernel\n");
}