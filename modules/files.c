#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include <windows.h>
#include "files.h"

void create_database_folder() {
  struct stat sb;

  if(stat("./database", &sb) != 0) {
    mkdir("database");
  };
}

Tables * get_tables() {
  Tables tables = {
    .size = 0,
    .tables = malloc(0)
  };

  HANDLE handle;
  WIN32_FIND_DATAA data;

  handle = FindFirstFileA("./database/*.csv", &data);
  if(handle != INVALID_HANDLE_VALUE) {
    do {
    
      printf("\n%s", data.cFileName);
    } while(FindNextFileA(handle, &data));
    FindClose(handle);
  };
}

void save_table(Table table) {
  char path[60]; 
  sprintf(path, "./database/%s.csv", table.name);
  FILE * file = fopen(path, "w+");

  
  fprintf(file, "teste,1,2.5\n");
  fclose(file);
}