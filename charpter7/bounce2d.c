#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <termios.h>
#include <stdlib.h>
/*declarations*/
int set_ticker(int ns);
void move_msg();
void get_mode(struct termios* origin_mode);
void set_mode(struct termios new_mode);
void reset_mode();

int col;
int row;
int dir;
struct termios original_mode;
struct termios mode;
int main() {
	/* code */
	initscr();

	col = 0;
	row = LINES / 2;
	dir = 1;
	int delay_time;

	
	get_mode(&original_mode);
	mode = original_mode;
	set_mode(mode);

	delay_time = 200;  // ms

	clear();	
	move(row, col);
	addstr("O");
	refresh();
	signal(SIGALRM, move_msg);

	while (1) {
		signal(SIGINT, reset_mode);
		char c = getch();
		if (c == 'q' || c == 'Q')
			break;
		if (c == 'f' || c == 'F')
			delay_time *= 2;
		if (c == 's' || c == 'S')
			delay_time = delay_time > 2 ? delay_time / 2 : delay_time;
		if (c == ' ')
			dir = -dir;
		set_ticker(delay_time);
	}
	
	reset_mode(mode);
	endwin();
	return 0;
}
// set delay timer
int set_ticker(int ms) {
	struct itimerval new_timeset;
	long n_sec, n_usec;
	n_sec = ms / 1000;
	n_usec = ms % 1000 * 1000L;
	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usec;
	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usec;

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
void move_msg() {
	move(row, col);
	addstr(" ");
	if (dir == -1 && col <= 0) {
		col = 1;
		dir = -dir;
	} else if (dir == 1 && col + strlen("O") >= COLS) {
		dir = -1;
	}
	col += dir;
	move(row, col);
	addstr("O");
	refresh();
}

void get_mode(struct termios* origin_mode) {
	tcgetattr(0, origin_mode);
}

void set_mode(struct termios new_mode) {
	new_mode.c_lflag &= ~ICANON;
	new_mode.c_cc[VMIN] = 1;
	new_mode.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &new_mode);
}

void reset_mode() {
	tcsetattr(0, TCSANOW, &original_mode);
	endwin();
	exit(1);
}


