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

  while (menu_option != 0) {
    clear_terminal();
    tables = get_tables();
    menu_option = display_default_menu(tables.size);
    clear_terminal();
    switch (menu_option) {
      case 0:
        break;
      case 1: 
        new_table = create_new_table();
        if (strcmp(new_table.name, "NULL_TABLE") != 0) {
          table_exists = table_already_exists(new_table, tables);
          if (table_exists == 0) {
            save_table_file(new_table);
            printf("Tabela \"%s\" adicionada ao banco de dados com sucesso.\n", new_table.name);
          }
        };
        pause_terminal();
        break;
      case 2:
        if(tables.size == 0) {
          goto error_message;
        };
        table_option = display_tables_menu(tables, " para remover");       
        if (is_option_valid(table_option, tables.size) == 0) break;
        Table table_to_delete = tables.list[table_option - 1];
        delete_table(table_option - 1, &tables);
        clear_terminal();
        remove_table_file(table_to_delete);
        pause_terminal();
        break;
      case 3:
        if(tables.size == 0) {
          goto error_message;
        };

        table_option = display_tables_menu(tables, "");
        if (is_option_valid(table_option, tables.size) == 0) break;
        procedure_option = display_procedures_menu(tables.list[table_option - 1]);
        if (is_option_valid(procedure_option, 5) == 0) break;

        break;
      error_message:
      default:
        fflush(stdin);
        break;
    };
  };
  clear_terminal();
  printf("Programa encerrado!");
  #ifdef _WIN32
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_DEFAULT);
  #endif

  return 0;
}
