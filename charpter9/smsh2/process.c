#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int is_control_command(char* s);
int do_control_command(char** args);
int ok_to_excute();

int process(char** args) {
    if (args == NULL)
        return 0;

    int ret = 0;

    if (is_control_command(args[0]))
        ret = do_control_command(args);
    else if (ok_to_excute())
        ret = excute_args(args);
    return ret;

}