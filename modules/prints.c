#include <stdio.h>
#include <stdlib.h>
#include "prints.h"

/// @brief Imprime as tabelas disponíveis.
/// @param tables lista de tabelas
/// @param start número do primeiro elemento da lista 
void print_tables(Tables tables, int start){
  tables = sort_tables(tables);
  
  for(int i = 0; i < tables.size; i++) {
    printf("[%d] → %s\n", i + start, tables.list[i].name);
  };
}

/// @brief Imprime as colunas de uma tabela
/// @param table a tabelas
/// @param start número do primeiro elemento da lista 
/// @param include_primary_key se deve ou não incluir a chave primária
void print_columns(Table table, int start, bool include_primary_key) {
  int start_column = include_primary_key? 0:1;
  for(int i = start_column; i < table.qtd_columns; i++) {
    printf(
      "[%d] → %s : %s\n", 
      i - start_column + start, 
      table.columns[i].name,
      get_type_name(table.columns[i].type)
    );
  };
}

// [NOVO] Imprimir tabela
void print_table(Table table){
  int columns_length[table.qtd_columns];
  for(int i = 0; i < table.qtd_columns; i++) {
    int gap = i == table.qtd_columns - 1? 0:3;
    columns_length[i] = get_column_length(table, i) + gap;
  };

  int line_length = sum(table.qtd_columns, columns_length) + 1;
  printf("%s / Registros: %d\n\n", table.name, table.qtd_records);

  printf("%s\n", 
    format_table_line_names(
      table.qtd_columns, columns_length, 
      line_length, table
    )
  );

  print_table_divisor(line_length);

  for(int i = 0; i < table.qtd_records; i++) {
    printf("%s\n", 
      format_table_line_record(
        table.qtd_columns, columns_length, 
        line_length, i, table
      )
    );
  };

  printf("\n");
}

/// @brief Imprime o divisor horizontal da tabela.
/// @param line_length tamanho da linha
void print_table_divisor(int line_length) {
  char * div = malloc(sizeof(char) * (line_length + 1));
  strcpy(div, "");

  for(int i = 0; i < line_length; i++) {
    strcat(div, "-");
  };

  printf("%s\n", div);
}

/// @brief Gera divisores com um título no meio.
/// @param title o título, tamanho máximo 53
void print_divisor(char title[53]) {
  int size = strlen(title);

  if(size == 0) {
    printf("======================================================\n");
    return;
  };

  int left = 0;
  int right = 0;
  int max = 54 - size;

  if(size != 0) max -= 2; 
  if(size % 2 == 1) {
    max++;
  };

  left += max/2;
  right += max/2;

  char left_divider[55] = "======================================================";
  char right_divider[55] = "======================================================";
  left_divider[left] = '\0';
  right_divider[right] = '\0';

  printf("%s %s %s\n", left_divider, title, right_divider);
}