#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "files.h"
  #include <dirent.h>
#ifdef _WIN32
  #include <windows.h>
  #include <direct.h>
#else
  #include <dirent.h>
#endif

/// @brief Cria a pasta "database" se ela não existir
void create_database_folder() {
  struct stat sb;

  if(stat("./database", &sb) != 0) {
    #ifdef _WIN32
      mkdir("database");
    #else
      mkdir("database", 0777);
    #endif
  };
}

/// @brief Pega todas as tabelas dentro da pasta "database"
/// @return Lista de tabelas
Tables get_tables() {
  Tables tables = {
    .size = 0,
    .list = malloc(0)
  };

  create_database_folder();

  #ifdef _WIN32
    HANDLE handle;
    WIN32_FIND_DATAA data;

    handle = FindFirstFileA("./database/*.csv", &data);
    if(handle != INVALID_HANDLE_VALUE) {
      do {
        char * piece = strtok(data.cFileName, "."); 
        Table table;
        strcpy(table.name, piece);
        add_in_tables(&tables, table);
      } while(FindNextFileA(handle, &data));
      FindClose(handle);
    };
  #else
    DIR * dir = opendir("./database");
    if(dir == NULL) {
      perror("Não foi possível localizar a pasta \"./dabatase\"!");
      exit(1);
    };

    struct dirent * file = readdir(dir);
    while(file != NULL) {
      char * piece = strtok(file -> d_name, "."); 
      Table table;
      strcpy(table.name, piece);
      add_in_tables(&tables, table);
      file = readdir(dir);
    };

    closedir(dir);
  #endif

  return tables;
}

/// @brief Salva as alterações de uma tabela, a cria se ela não existir
/// @param table a tabela
void save_table(Table table) {
  char path[70]; 
  sprintf(path, "./database/%s.csv", table.name);
  FILE * file = fopen(path, "w+");
  //fprintf(file, "teste,1,2.5\n");
  fclose(file);
}

/// @brief Deleta uma tabela por completo, incluindo seu arquivo csv. No momento, funciona apenas se a tabela foi anteriormente criada dentro do programa. 
/// @param table a tabela
void delete_table(Table table) {
  char path[70];
  sprintf(path, "./database/%s.csv", table.name);
  remove(path);
}