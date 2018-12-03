#include <stdlib.h>

enum state {
    NEUTRAL,
    WANT_THEN,
    THEN_BLOCK
};

enum results {
    SUCCESS,
    FAIL
};
static int if_state = NEUTRAL;
static int
int is_control_command(char* s) {

}