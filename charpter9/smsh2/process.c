#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "smsh2.h"


int process(char** args) {
    if (args == NULL)
        return 0;

    int ret = 0;
    if (is_control_command(args[0])) {
            ret = do_control_command(args);
        }
    else if (ok_to_excute()) {
        ret = excute_args(args);
    }

    return ret;

}
