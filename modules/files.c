#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "files.h"

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
  Table table;
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
    // Calloca o aux_name baseado na quantidade de caracteres do diretório
    aux_name = calloc(strlen(file -> d_name), sizeof(char));
    while(file != NULL) {
      // Se for os diretórios "." ou "..", ele ignora e passa pro próximo (dois reais ou um presente misterioso? >:D)
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

// Vai ser mudado para salvar de uma vez só, depois.

/// @brief Salva uma nova tabela criada no diretório database. Salve apenas
/// O nome das colunas e seus tipos, sem salvar nenhuma linha.
/// @param table a tabela
void save_new_table_file(Table table) {
  char path[70];
  char line_content[200];
  sprintf(path, "./database/%s.csv", table.name);
  printf("colunas: %i e records: %i\n", table.qtd_columns, table.qtd_records);
  pause_terminal();
  FILE * file = fopen(path, "w+");
  columns_names_to_csv_string(table, line_content);
  fputs(line_content, file);
  columns_types_to_csv_string(table, line_content, table.qtd_records == 2 ? true : false);
  fputs(line_content, file);
  if (table.qtd_records > 2) {
    printf("Entrou no laço de salvar tuplas (qtd_records) > 2\n");
    for (int i = 3; i <= table.qtd_records; i++) {
      columns_values_to_csv_string(table, line_content, i == table.qtd_records ? true : false);
      printf("A linha é essa: %s\n", line_content);
      fputs(line_content, file);
    }
  }
  fclose(file);
}
/* Comentado temporariamente

/// @brief Salva as alterações de uma tabela, a cria se ela não existir.
/// @param table a tabela
void save_table_file(Table table) {
  char path[70];
  sprintf(path, "./database/%s.csv", table.name);
  FILE * file = fopen(path, "w+");
  fclose(file);
}

void save_tuple_on_table(Record *tuple);
*/

/// @brief Deleta uma tabela por completo, incluindo seu arquivo csv. 
/// No momento, funciona apenas se a tabela foi anteriormente criada 
/// dentro do programa. 
/// @param table a tabela
void remove_table_file(Table table) {
  char path[70];
  sprintf(path, "./database/%s.csv", table.name);
  remove(path);
  printf("Tabela \"%s\" removida!\n", table.name);
}

// [NOVO]
/// @brief Coleta todos os dados da tabela de acordo com seu arquivo CSV
/// @param table a tabela
/// @return a tabela, com todos os dados anteriormente vazios, preenchida
Table get_data_from_table(Table table) {
  char path[70];
  char line_content[200];
  int qtd_records = 2;
  sprintf(path, "./database/%s.csv", table.name);
  FILE *file = fopen(path, "r");
  fgets(line_content, 199, file);
  table = csv_string_to_columns_names(table, line_content);
  fgets(line_content, 199, file);
  table = csv_string_to_columns_types(table, line_content);
  printf("Nomes e tipos das colunas adicionados com sucesso! (Parcial)\n");
  /*
  while (feof(file) == 0); {
    fgets(line_content, 199, file);
    
    table = csv_string_to_columns_values(table, line_content, counter_i);
    qtd_records++;
    pause_terminal();
    
  };
  */
  table.qtd_records = qtd_records;
  pause_terminal();
  return table;
}
//