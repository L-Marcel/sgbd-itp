#include <stdio.h>
#include "tables.h"

void create_table(Table table) {
  char path[60]; 
  sprintf(path, "./database/%s", table.name);
  //FILE * file = fopen()
}