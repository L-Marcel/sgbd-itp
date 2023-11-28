#include <string.h>

typedef enum {
  true = 1,
  false = 0
} bool;

void get_string(unsigned long max_size, char text[max_size], char* message);
void trim(unsigned long size, char text[size]);
void clear_terminal();
void pause_terminal();

// [NOVO]
bool include_char(char * text, char target);
int sum(int size, int vector[size]);