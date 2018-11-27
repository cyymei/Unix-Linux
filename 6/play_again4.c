#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define QUESTION "Do you want another transaction"

int get_response(char* question);
int get_ok_char();
int mode(int how);
void set_nodelay_mode();
void set_cr_noecho_mode();
void ctrl_c_handler();

int main() {
	mode(0);

	set_cr_noecho_mode();
	set_nodelay_mode();

	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);

	int response;
	response = get_response(QUESTION);

	mode(1);
	return response;
}
int get_response(char* question) {
	printf("%s (y/n?)\n", question);
	fflush(stdout);
	int times = 0;
	while (1) {
		sleep(2);
		int input = tolower(get_ok_char());
		if (input == 'y')
			return 0;
		if (input == 'n')
			return 1;
		if (times++ > 2) {
			printf("timeout!\n");
			return 2;
		}
		printf("opps\n");
	}
}
int get_ok_char() {
	int c;
	
	while((c = getchar()) != EOF && strchr("YyNn", c) == NULL) 
		;
		
	// printf("get char: %c\n", c);
	return c;
}

int mode(int how) {
	static struct termios original_mode;
	static int origin_flags; 
	static int stored = 0;
	if (how == 0) {
		tcgetattr(0, &original_mode);
		origin_flags = fcntl(0, F_GETFL);
		stored = 1;
		printf("get mode\n");
	} else if (stored) {
		tcsetattr(0, TCSANOW, &original_mode);
		fcntl(0, F_SETFL, origin_flags);
		printf("rest mode\n");
	}
}

void set_cr_noecho_mode() {
	struct termios mode;
	tcgetattr(0, &mode);
	mode.c_lflag &= ~ICANON;
	mode.c_lflag &= ~ECHO;
	mode.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &mode);
}

void set_nodelay_mode() {
	int flag;
	flag = fcntl(0, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(0, F_SETFL, flag);
}

void ctrl_c_handler() {
	mode(1);
	exit(1);
}