#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "modules/all_modules.h"

#ifdef _WIN32
  #include <windows.h>
#endif

int main() {
  int menu_option = 99999, table_option, procedure_option, table_exists;
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
        new_table = createNewTable();
        if (strcmp(new_table.name, "NULL_TABLE") != 0) {
          table_exists = tableAlreadyExists(new_table, tables);
          if (table_exists == 0) {
            save_table(new_table);
            printf("Tabela \"%s\" adicionada ao banco de dados com sucesso.\n", new_table.name);
          }
        };
        pause_terminal();
        break;
      case 2:
        if(tables.size == 0) {
          goto error_message;
        };
        printf("Insira o index da tabela que deseja excluir\n");
        table_option = displayTablesMenu(tables);       
        if (isOptionValid(table_option, tables.size) == 0) break;
        deleteTable(table_option, tables);
        pause_terminal();
        break;
      case 3:
        if(tables.size == 0) {
          goto error_message;
        };
        table_option = displayTablesMenu(tables);
        if (isOptionValid(table_option, tables.size) == 0) break;
        printf("Você escolheu mudar a tabela %i!", table_option);
        procedure_option = displayProceduresMenu();
        if (isOptionValid(procedure_option, 5) == 0) break;
        pause_terminal();
        break;
      error_message:
      default:
        printf("ERRO: Opção inválida. Por favor, tente novamente.\n\n");
        pause_terminal();
        break;
    };
  };
  clear_terminal();
  printf("Programa encerrado!\n\n");
  #ifdef _WIN32
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_DEFAULT);
  #endif

  return 0;
}
