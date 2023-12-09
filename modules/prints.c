#include "headers/prints.h"
#include <stdio.h>
#include <stdlib.h>

/// @brief Imprime as tabelas disponíveis.
/// @param tables lista de tabelas
/// @param start número do primeiro elemento da lista
void print_tables(Tables tables, int start) {
  tables = sort_tables(tables);
  for (int i = 0; i < tables.size; i++) {
    printf("[%d] → %s\n", i + start, tables.list[i].name);
  };
}

/// @brief Imprime as colunas de uma tabela
/// @param table a tabelas
/// @param start número do primeiro elemento da lista
/// @param include_primary_key se deve ou não incluir a chave primária
void print_columns(Table table, int start, bool include_primary_key) {
  int start_column = include_primary_key ? 0 : 1;
  for (int i = start_column; i < table.qtd_columns; i++) {
    printf("[%d] → %s : %s\n", i - start_column + start, table.columns[i].name,
        get_type_name(table.columns[i].type));
  };
}

/// @brief Imprime uma tabela.
/// @param table a tabela
void print_table(Table table, char turples_message[50]) {
  int columns_length[table.qtd_columns];
  for (int i = 0; i < table.qtd_columns; i++) {
    int gap = i == table.qtd_columns - 1 ? 0 : 3;
    columns_length[i] = get_column_length(table, i) + gap;
  };

  int line_length = sum(table.qtd_columns, columns_length) + 1;

  print_divisor(table.name, 0);
  printf("\n%s\n", format_table_line_names(table.qtd_columns, columns_length, line_length, table));

  print_table_divisor(line_length + 1);

  for (int i = 0; i < table.qtd_records; i++) {
    printf(
        "%s\n", format_table_line_record(table.qtd_columns, columns_length, line_length, i, table));
  };

  char records_text[50];
  printf("\n");
  sprintf(records_text, "%d tuplas %s", table.qtd_records, turples_message);
  print_divisor(records_text, 0);
}

/// @brief Imprime o divisor horizontal da tabela.
/// @param line_length tamanho da linha
void print_table_divisor(int line_length) {
  char *div = malloc(sizeof(char) * (line_length + 1));
  strcpy(div, "");

  for (int i = 0; i < line_length; i++) {
    strcat(div, "-");
  };

  printf("%s\n", div);
}

/// @brief Gera divisores com um título no meio.
/// @param title o título, tamanho máximo 53
/// @param utf8_chars número de caracteres especiais no texto
void print_divisor(char title[53], int utf8_chars) {
  int size = strlen(title) - utf8_chars;

  if (size == 0) {
    printf("======================================================\n");
    return;
  };

  int left = 0;
  int right = 0;
  int max = 54 - size;
  int gap = 0;

  if (size != 0) max -= 2;
  if (size % 2 == 1) { gap++; };

  left += max / 2;
  right += max / 2 + gap;

  char left_divider[55] = "======================================================";
  char right_divider[55] = "======================================================";
  left_divider[left] = '\0';
  right_divider[right] = '\0';

  printf("%s %s %s\n", left_divider, title, right_divider);
}
