#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void countdown();
int set_clock(int m_seconds);
int main() {
	printf("Sleep...\n");
	signal(SIGALRM, countdown);
	if (set_clock(500) == -1) {
		perror("set_clock err.");
	} else {
		while(1)
			pause();
	}
	printf("return\n");
	return 0;
}
void countdown() {
	printf("Received from kernel\n");
}

int set_clock(int m_seconds) {
	struct itimerval new_timeset;
	long n_sec, n_usec;

	n_sec = m_seconds / 1000;
	n_usec = (m_seconds % 1000) * 1000;
	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usec;

	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usec;

	return setitimer(ITIMER_REAL, &new_timeset, NULL);



}
