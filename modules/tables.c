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

/// @brief Cria uma nova tabela. Ainda está incompleto (falta os inputs do usuário)
/// @return em caso de sucesso: a própria tabela criada. em caso de erro ou cancelamento, uma tabela vazia com parâmetro name = "NULL_TABLE", para simbolizar à main que a tabela é vazia.
Table createNewTable() {
  Table new_table, empty_table;
  int qtd_columns, i;
  char yes_or_no;
  // Como a função tem que retornar Table, essa empty_table é caso dê algo errado, aí retorna uma table só com o nome preenchido pra simbolizar que tá errado. 
  strcpy(empty_table.name, "NULL_TABLE");
  printf("Por favor, preencha as informações abaixo:\n\n");
  printf("Nome da tabela: ");
  scanf("%s", new_table.name);
  getchar();
  printf("Quantidade de colunas/atributos da tabela (se não souber, insira 0): ");
  scanf("%i", &qtd_columns);
  getchar();
  if (qtd_columns < 0) {
    printf("Valor inválido: Não é possível ter colunas negativas. Redirecionando para o menu principal.");
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
  if (yes_or_no == 'Y' || yes_or_no == 'y') {
      return new_table;
  } else if (yes_or_no == 'N' || yes_or_no == 'n') {
      return empty_table;
  } else {
      printf("Opção inválida. Voltando para o menu principal.");
      system("pause");
      return empty_table;
  };
}

/// Deleta a tabela solicitada (pelo index desta). Não fiz nada ainda
void deleteTable(int table_index, Tables tables) {
  printf("Deletei nada!");
}

/// @brief Percorre a database para saber se a tabela inserida pelo usuário já existe
/// @param table a tabela inserida
/// @param tables a lista de tabelas do momento (tables.list e database)
/// @return 1, se houver tabela igual na database; 0, se não houver tabela igual
int tableAlreadyExists(Table table, Tables tables) {
  for (int i = 0; i < tables.size; i++) {
    if (strcmp(table.name, tables.list[i].name) == 0) {
      printf("Erro: Tabela já existente.\n");
      return 1;
    };
  };
  return 0;
}