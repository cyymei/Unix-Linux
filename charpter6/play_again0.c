#include <stdio.h>
#define QUESTION "Do you want another transaction"
int get_response(char* question);
int main() {
	int response;
	response = get_response(QUESTION);
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

		}
	}
}