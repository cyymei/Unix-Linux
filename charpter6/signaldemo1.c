#include <signal.h>
#include <stdio.h>
void f() {
	printf("hello!\n");
}
int main() {
	int i;
	signal(SIGINT, SIG_IGN);
	for (i = 0; i < 10; i++) {
		printf("world!\n");
		sleep(2);
	}
	return 0;
}