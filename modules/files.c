#include <stdio.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "files.h"

void create_database_folder() {
  struct stat sb;

  if(stat("./database", &sb) != 0) {
    mkdir("database");
  };
}

void save_table(Table table) {
  char path[60]; 
  sprintf(path, "./database/%s.csv", table.name);
  FILE * file = fopen(path, "w+");

  
  fprintf(file, "teste,1,2.5\n");
  fclose(file);
}