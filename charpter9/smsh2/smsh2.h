#include <stdbool.h>

bool is_control_command(char* s);
int do_control_command(char** args);
bool ok_to_excute();
char* next_cmd(FILE* fp);
char** split_line(char* line);
