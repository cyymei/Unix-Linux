#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

#define INPUTLEN 100

void countdown();
int set_clock(int m_seconds);
void inthandler(int s);
void quithandler(int s);
int main(int ac, char* av[]) {
	char input[INPUTLEN];
	int nchars;

	signal(SIGINT, inthandler);
	signal(SIGQUIT, quithandler);

	do {
		printf("\nType a message\n");
		nchars = read(0, input, INPUTLEN - 1);
		if (nchars == -1)
			perror("Read returns an error!");
		else {
			input[nchars] = '\0';
			printf("You typed: %s\n", input);
		}
	} 
	while(strncmp(input, "quit", 4) != 0);

	return 0;
}

void inthandler(int s) {
	printf("Received signal %d..wating\n", s);
	sleep(2);
	printf("Leaving inihandler \n");
}

void quithandler(int s) {
	printf("Received signal %d..waiting\n", s);
	sleep(2);
	printf("Leaving quithandler\n");
}
