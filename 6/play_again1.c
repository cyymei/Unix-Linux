#include <stdio.h>
#include <termios.h>
#define QUESTION "Do you want another transaction"

int get_response(char* question);
int main() {
	struct termios original_mode;
	struct termios set_mode;

	tcgetattr(0, &original_mode);
	set_mode = original_mode;

	set_mode.c_lflag &= ~ICANON;
	set_mode.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &set_mode);
	

	int response;
	response = get_response(QUESTION);

	tcsetattr(0,TCSANOW, &original_mode);
	return response;
}
int get_response(char* question) {
	printf("%s (y/n?)\n", question);
	while (1) {
		switch(getchar()) {
			case 'Y':
			case 'y': return 0;
			case 'n':
			case 'N':
			case EOF: return 1;	
			default: printf("can't understand!\n");

		}
	}
}