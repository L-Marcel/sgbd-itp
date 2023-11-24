#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include <windows.h>
#include <string.h>
#include "files.h"

/// @brief Cria a pasta "database" se ela não existir
void create_database_folder() {
  struct stat sb;

  if(stat("./database", &sb) != 0) {
    mkdir("database");
  };
}

/// @brief Pega todas as tabelas dentro da pasta "database"
/// @return Lista de tabelas
Tables get_tables() {
  Tables tables = {
    .size = 0,
    .list = malloc(0)
  };

  HANDLE handle;
  WIN32_FIND_DATAA data;

  handle = FindFirstFileA("./database/*.csv", &data);
  if(handle != INVALID_HANDLE_VALUE) {
    do {
      tables.size++;
      tables.list = realloc(tables.list, sizeof(Table) * tables.size);
      char * piece = strtok(data.cFileName, "."); 
      Table table;

      //só está pegando o nome
      strcpy(table.name, piece);

      tables.list[tables.size - 1] = table;
    } while(FindNextFileA(handle, &data));
    FindClose(handle);
  };

  return tables;
}

/// @brief Salva as alterações de uma tabela, a cria se ela não existir
/// @param table a tabela
void save_table(Table table) {
  char path[60]; 
  sprintf(path, "./database/%s.csv", table.name);
  FILE * file = fopen(path, "w+");
  //fprintf(file, "teste,1,2.5\n");
  fclose(file);
}