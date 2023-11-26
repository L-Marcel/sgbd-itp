#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tables.h"

/// @brief Converte o typo enumerado para um texto.
/// @param type o tipo enumerado
/// @return A texto, com tamanho máximo de 10 chars.
char* get_type_name(types type) {
  switch (type) {
    case T_NAT:
      return "Nat";
    case T_INT:
      return "Int";
    case T_STRING:
      return "String";
    case T_CHAR:
      return "Char";
    case T_DOUBLE:
      return "Double";
    case T_FLOAT:
      return "Float";
    default:
      return "Undefined";
  }
}

/// @brief Ordena a lista de tabelas pelo nome delas.
/// @param tables as tabelas
/// @return As tabelas ordenadas por nome.
Tables sort_tables(Tables tables) {
  for(int i = 0; i < tables.size; i++) {
    Table next = tables.list[i];
    for(int j = i; j < tables.size; j++) {
      if(strcmp(tables.list[j].name, next.name) < 0) {
        Table old_next = next;
        next = tables.list[j];
        tables.list[j] = old_next;
      };
    };

    tables.list[i] = next;
  };

  return tables;
}

/// @brief Adiciona uma tabela na lista de tabelas.
/// @param tables a lista de tabelas
/// @param table a tabela a ser adicionada
void add_table(Tables * tables, Table table) {
  tables -> size++;
  tables -> list = realloc(tables -> list, sizeof(Table) * tables -> size);
  tables -> list[tables -> size - 1] = table;
}

/// @brief Inicializa uma tabela vazia.
/// @return a tabela vazia
Table create_empty_table() {
  Table table = {
    .name = "",
    .qtd_columns = 0,
    .qtd_records = 0,
  };

  //É necessário alocar para conseguirmos
  //realocar depois
  table.columns = malloc(0);
  table.records = malloc(0);

  return table;
}

/// @brief Adiciona uma coluna em uma tabela.
/// @param table a tabela
/// @param column a coluna
void add_column(Table table, Column column) {
  table.qtd_columns++;
  table.columns = realloc(table.columns, sizeof(Column) * table.qtd_columns);
  table.columns[table.qtd_columns - 1] = column;
}

/// @brief Remove uma tabela da lista de tabelas
/// @param table_index index da tabela
/// @param tables lista de tabelas
void delete_table(int table_index, Tables * tables) {
  for(int i = 0; i < tables -> size - 1; i++) {
    if(i >= table_index) {
      tables -> list[i] = tables -> list[i + 1];
    };
  };

  tables -> size--;
  tables -> list = realloc(tables -> list, sizeof(Table) * tables -> size);
}

/// @brief Percorre a database para saber se a tabela inserida pelo usuário já existe.
/// @param table a tabela inserida
/// @param tables a lista de tabelas do momento (tables.list e database)
/// @return true, se houver tabela igual na database; false, se não houver tabela igual.
bool table_already_exists(Table table, Tables tables) {
  for (int i = 0; i < tables.size; i++) {
    if (strcmp(table.name, tables.list[i].name) == 0) {
      return true;
    };
  };

  return false;
}