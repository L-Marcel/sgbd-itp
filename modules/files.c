#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "headers/files.h"

#ifdef _WIN32
  #include <windows.h>
  #include <direct.h>
#else
  #include <dirent.h>
#endif

/// @brief Cria a pasta "database" se ela não existir.
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

/// @brief Pega todas as tabelas dentro da pasta "database".
/// @return Lista de tabelas.
Tables get_tables() {
  Tables tables = {
    .size = 0,
    .list = malloc(0)
  };
  
  Table table = {
    .qtd_columns = 0,
    .qtd_records = 0,
    .records = malloc(0),
    .columns = malloc(0),
  };

  char *piece, *aux_name;

  create_database_folder();

  #ifdef _WIN32
    HANDLE handle;
    WIN32_FIND_DATAA data;

    handle = FindFirstFileA("./database/*.csv", &data);
    if(handle != INVALID_HANDLE_VALUE) {
      do {
        char * piece = strtok(data.cFileName, ".");
        strcpy(table.name, piece);
        add_table(&tables, table);
      } while(FindNextFileA(handle, &data));
      FindClose(handle);
    };
  #else
    DIR * dir = opendir("./database");
    if(dir == NULL) {
      perror("Não foi possível localizar a pasta \"./dabatase\"!");
      exit(1);
    };

    struct dirent *file = readdir(dir);
    aux_name = calloc(strlen(file -> d_name), sizeof(char));
    
    while(file != NULL) {
      if (strcmp(file -> d_name, ".") != 0 && strcmp(file -> d_name, "..") != 0) {
        aux_name = realloc(aux_name, strlen(file -> d_name) * sizeof(char));
        strcpy(aux_name, file -> d_name);
        piece = strtok(aux_name, ".");
        strcpy(table.name, piece);
        add_table(&tables, table);
      };

      file = readdir(dir);
    };

    closedir(dir);
  #endif

  return tables;
}

/// @brief Salva os dados de uma tabela em um arquivo.
/// @param table a tabela
void save_table_file(Table table) {
  char path[70];
  sprintf(path, "./database/%s.csv", table.name);
  FILE * file = fopen(path, "w+");

  fputs(columns_names_to_csv_string(table), file);
  fputs(columns_types_to_csv_string(table), file);

  for(int i = 0; i < table.qtd_records; i++) {
    fputs(columns_values_to_csv_string(table, i), file);
  };

  fclose(file);
}

/// @brief Deleta o arquivo de uma tabela.
/// @param table a tabela
void remove_table_file(Table table) {
  char path[70];
  sprintf(path, "./database/%s.csv", table.name);
  remove(path);
  printf("Tabela \"%s\" removida!\n", table.name);
}

/// @brief Coleta todos os dados da tabela de acordo com seu arquivo CSV.
/// @param table a tabela
/// @return a tabela, com todos os dados anteriormente vazios, preenchida.
Table get_data_from_table(Table table) {
  char path[70];
  char line_content[200];

  sprintf(path, "./database/%s.csv", table.name);
  FILE * file = fopen(path, "r");
  
  char * file_content = malloc(0);
  int size = 0;

  while(feof(file) == 0) {
    size++;
    file_content = realloc(file_content, sizeof(char) * size);
    file_content[size - 1] = fgetc(file);
  };

  fclose(file);

  char * piece = strtok(file_content, "\n");
  int count = 0;

  char ** lines = malloc(0);

  while(piece != NULL) {
    lines = realloc(lines, sizeof(char*) * (count + 1));
    lines[count] = malloc((strlen(piece) + 1) * sizeof(char));
    strcpy(lines[count], piece);
 
    piece = strtok(NULL, "\n");
    count++;
  };

  for(int i = 0; i < count; i++) {
    switch(i) {
      case 0:
        table = csv_string_to_columns_names(table, lines[i]);
        break;
      case 1:
        table = csv_string_to_columns_types(table, lines[i]);
        break;
      default:
        table.qtd_records++;
        table.records = realloc(table.records, sizeof(Record*) * table.qtd_records);
        table.records[table.qtd_records - 1] = calloc(table.qtd_columns, sizeof(Record));

        table = csv_string_to_columns_values(
          table, 
          lines[i], 
          table.qtd_records
        );
        break;
    };
  };

  return table;
}