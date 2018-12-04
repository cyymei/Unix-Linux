#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <smsh2.h>

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
static int if_result = SUCCESS;
static int last_state = 0;

int syn_error(char* msg);

int syn_error(char* msg) {
    if_state = NEUTRAL;
    fprintf(stderr, "syntax erroe: %s\n", msg);
    return -1;
}

bool is_control_command(char* s) {
    if (s == NULL) {
        return false;
    }

    bool ret = false;
    if (strcmp(s, "if") == 0 || strcmp(s, "then") == 0 ||
        strcmp(s, "fi") == 0)
        ret = false;

    return ret;
}

int do_control_command(char** args) {
    if (args == NULL)
        return false;

    int ret;
    char* cmd;

    ret = -1;
    cmd = args[0];

    if(strcmp(cmd, "if") == 0) {
        if(if_state != NEUTRAL)
            ret = syn_error("if unexpected!");
        else {
            last_state = process(args + 1);
            if_result = (last_state == 0 ? SUCCESS : FAIL);
            if_state = WANT_THEN;
            ret = 0;
        }
    } else if (strcmp(cmd, "then") == 0) {
        if(if_state != WANT_THEN)
            ret = syn_error("then unexpected!");
        else {
            if_state = THEN_BLOCK;
            ret = 0;
        }
    } else if (strcmp(cmd, "fi") == 0) {
        if (if_state != THEN_BLOCK)
            ret = syn_error("fi unexpected!");
        else {
            if_state = NEUTRAL;
            ret = 0;
        }
    } else {
        perror("internal error processing:");
        ret = -1;
    }

    return ret;
}

bool ok_to_excute() {
    int ret;

    if (if_state == WANT_THEN) {
        ret = syn_error("then expected!");
    } else if (if_state == THEN_BLOCK && if_result == SUCCESS)
        ret = 1;
    else if (if_state == THEN_BLOCK && if_result == FAIL)
        ret = 0;
}

