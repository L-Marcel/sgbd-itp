#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include "modules/all_modules.h"

#ifdef _WIN32
  #include <windows.h>
#endif

int main() {
  int menu_option, table_option, table_exists;
  #ifdef _WIN32
    UINT CPAGE_UTF8 = 65001;
    SetConsoleOutputCP(CPAGE_UTF8);
  #endif

  Table new_table;
  Tables tables;
  clear_terminal();
  while (menu_option != 0) {
    tables = get_tables();
    menu_option = displayDefaultMenu(tables.size);
    clear_terminal();
    switch (menu_option) {
      case 0:
        break;
      case 1:
        // Abre passo a passo para o usuário inserir as informações da tabela
        new_table = createNewTable();
        if (strcmp(new_table.name, "NULL_TABLE") != 0) {
          // Verifica se a tabela já existe. Atualmente, se existir a função retorna 1 e se não, retorna 0.
          table_exists = tableAlreadyExists(new_table, tables);
          if (table_exists == 0) {
            save_table(new_table);
            printf("Tabela \"%s\" adicionada ao banco de dados com sucesso.\n", new_table.name);
          }
        }
        system("pause");
        break;
      case 2:
        if(tables.size == 0) {
          goto error_message;
        };
        printf("\nDeletou a tabela! (Ilustrativo):\n");
        break;
      case 3:
        if(tables.size == 0) {
          goto error_message;
        };
        table_option = displayTablesMenu(tables);
        printf("Você escolheu mudar a tabela %i! Redirecionando para o menu principal.", table_option);
        break;
      error_message:
      default:
        printf("ERRO: Opção inválida. Por favor, tente novamente.\n\n");
        system("pause");
        break;
    };
  };
  clear_terminal();
  printf("Programa encerrado!\n");

  #ifdef _WIN32
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_DEFAULT);
  #endif

  return 0;
}