#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <smsh2.h>


int process(char** args) {
    if (args == NULL)
        return 0;

    int ret = 0;
    printf("%s\n", args[0]);
    if (is_control_command(args[0])) {

            printf("is_control_command\n");
            ret = do_control_command(args);
        }
    else if (ok_to_excute()) {
        printf("ok_to_excute\n");
        ret = excute_args(args);
    }

    return ret;

}