#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define QUESTION "Do you want another transaction"

int get_response(char* question);
int get_ok_char();

int main() {
	struct termios original_mode;
	struct termios set_mode;

	tcgetattr(0, &original_mode);
	set_mode = original_mode;

	set_mode.c_lflag &= ~ICANON;
	//set_mode.c_lflag &= ~ECHO;
	set_mode.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &set_mode);

	int origin_flags = fcntl(0, F_GETFL);
	int termFalgs = origin_flags;
	termFalgs |= O_NONBLOCK;
	fcntl(0, F_SETFL, termFalgs);
	

	int response;
	response = get_response(QUESTION);

	tcsetattr(0,TCSANOW, &original_mode);
	fcntl(0, F_SETFL, origin_flags);
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
	while(c = getchar() != EOF && strchr("YyNn", c) == NULL) 
		;
	return c;
}