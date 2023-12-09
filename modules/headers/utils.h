#include "enums.h"
#include <string.h>

void get_string(unsigned long max_size, char text[max_size], char* message);
void lower_string(char original_string[200], char lowered_string[200]);
void trim(unsigned long size, char text[size]);
void clear_terminal();
void pause_terminal();
bool include_char(char * text, char target);
int sum(int size, int vector[size]);
int count_right_digits(char value[200]);