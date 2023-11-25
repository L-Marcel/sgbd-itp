#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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

/// @brief Adiciona uma tabela na lista de tabelas
/// @param tables a lista de tabelas
/// @param table a tabela a ser adicionada
void add_table(Tables * tables, Table table) {
  tables -> size++;
  tables -> list = realloc(tables -> list, sizeof(Table) * tables -> size);
  tables -> list[tables -> size - 1] = table;
}

/// @brief Cria uma nova tabela. Ainda está incompleto (falta os inputs do usuário)
/// @return em caso de sucesso: a própria tabela criada. em caso de erro ou cancelamento, uma tabela vazia com parâmetro name = "NULL_TABLE", para simbolizar à main que a tabela é vazia.
Table create_new_table() {
  Table new_table, empty_table;
  int qtd_columns, i;
  char yes_or_no;
 
  strcpy(empty_table.name, "NULL_TABLE");
  printf("Nome da tabela: ");
  fgets(new_table.name, 50, stdin);
  trim(strlen(new_table.name), new_table.name);

  fflush(stdin);
  printf("Quantidade de colunas (se não souber, insira 0): ");
  scanf("%i", &qtd_columns);
  getchar();
  if (qtd_columns < 0) {
    printf("Valor inválido: não é possível ter colunas negativas. Redirecionando para o menu principal.");
    return empty_table;
  } else if (qtd_columns > 0) {
    for (i = 0; i < qtd_columns; i++) {
      printf("Valor da coluna %i\n", i);
    };
  } else {
      printf("Vamo fazer um while.\n");
  };
  printf("Deseja realmente adicionar a tabela \"%s\" ao banco de dados? (Y/N): ", new_table.name);
  scanf("%c", &yes_or_no);
  getchar();
  if (tolower(yes_or_no) == 'y') {
      return new_table;
  } else if (tolower(yes_or_no) == 'n') {
      return empty_table;
  } else {
      printf("Opção inválida. Voltando para o menu principal.");
      system("pause");
      return empty_table;
  };
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

/// @brief Percorre a database para saber se a tabela inserida pelo usuário já existe
/// @param table a tabela inserida
/// @param tables a lista de tabelas do momento (tables.list e database)
/// @return 1, se houver tabela igual na database; 0, se não houver tabela igual
int table_already_exists(Table table, Tables tables) {
  for (int i = 0; i < tables.size; i++) {
    if (strcmp(table.name, tables.list[i].name) == 0) {
      printf("Erro: tabela já existe!\n");
      return 1;
    };
  };
  return 0;
}