#include <string.h>

typedef enum {
  true = 1,
  false = 0
} bool;

void get_string(int max_size, char text[max_size], char* message);
void trim(int size, char text[size]);
int sum(int size, int vector[size]);
void clear_terminal();
void pause_terminal();