#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tables.h"

/// @brief Ordena a lista de tabelas pelo nome delas
/// @param tables as tabelas
/// @return as tabelas ordenadas por nome
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

void add_in_tables(Tables * tables, Table table) {
  tables -> size++;
  tables -> list = realloc(tables -> list, sizeof(Table) * tables -> size);
  tables -> list[tables -> size - 1] = table;
}

Table create_table() {
  Table t;
  return t;
}