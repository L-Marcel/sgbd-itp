#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include "modules/search.h"

#define SEED = true;
#include "seeds/users.h"

#ifdef _WIN32
  #include <windows.h>
#endif

int main(int argc, char **argv) {
  int table_option, procedure_option, column_option, record_option, search_option, table_exists;

  #ifdef _WIN32
    UINT CPAGE_UTF8 = 65001;
    SetConsoleOutputCP(CPAGE_UTF8);
  #endif

  Table new_table;
  Record *new_record;

  int menu_option = -1;
  int valid_option = -1;

  if(argc >= 2 && strcmp(argv[1], "--seed") == 0) {
    seed_users();
  };

  while(menu_option != 0) {
    Tables tables = get_tables();
    menu_option = display_default_menu(tables.size);
    clear_terminal();
    switch (menu_option) {
      case 0: // Sair
        break;
      case 1: // Criar uma nova tabela
        new_table = new_table_procedure(tables);
        if (strcmp(new_table.name, "") != 0) {
          save_table_file(new_table);
          printf("Tabela \"%s\" adicionada ao banco de dados com sucesso.\n", new_table.name);
        } else {
          printf("Operação cancelada!\n");
        };

        pause_terminal();
        break;
      case 2: // Deletar uma tabela existente
        if(tables.size == 0) {
          goto error_message;
        };

        valid_option = -1;
        do {
          table_option = display_tables_menu(tables, " para remover");  
          valid_option = is_option_valid(table_option, tables.size);   
         
          if (valid_option == 0) break;
          else if (valid_option == -1) continue;

          Table table_to_delete = tables.list[table_option - 1];
          delete_table(table_option - 1, &tables);
          remove_table_file(table_to_delete);
          pause_terminal();
        } while(valid_option == -1);
        break;
      case 3: // Listar/selecionar tabela(s)
        if(tables.size == 0) {
          goto error_message;
        };

        valid_option = -1;
        do {
          table_option = display_tables_menu(tables, "");
          valid_option = is_option_valid(table_option, tables.size);
          if (valid_option == 0) break;
          else if (valid_option == -1) continue;
          Table table = tables.list[table_option - 1];
          table = get_data_from_table(table);

          do {
            procedure_option = display_procedures_menu(table);
            valid_option = is_option_valid(procedure_option, 5);
            int start_qtd_records = table.qtd_records;
            if (valid_option == 0) break;

            switch (procedure_option) {
              case 1: 
                table = new_record_procedure(table);

                if (start_qtd_records < table.qtd_records) {
                  save_table_file(table);
                  printf("Nova tupla registrada com sucesso!\n");
                } else {
                  printf("Operação cancelada!\n");
                }

                pause_terminal();
                break;
              case 2:
                print_table(table);
                pause_terminal();
                break;
              case 3: // [TODO] Pesquisar valor na tabela
                if(table.qtd_records <= 0) {
                  break;
                };
                column_option = display_select_column_menu(table, " para a pesquisa", true);
                valid_option = is_option_valid(column_option, table.qtd_columns);
                if (valid_option <= -1) break;
                search_option = display_search_options_menu(table, column_option);
                if (search_option <= 0 || search_option > 7) break;
                search_main_caller(table, column_option, search_option);

                break;
              case 4:
                if(table.qtd_records <= 0) {
                  break;
                };

                do {
                  record_option = display_delete_record_procedure_menu(table);
                  if (record_option < -1) {
                    valid_option = -1;
                    continue;
                  } else if(record_option == -1) {
                    valid_option = 0;
                    break;
                  };

                  valid_option = delete_record(&table, record_option);
                  if (!valid_option) {
                    valid_option = -1;
                    continue;
                  };

                  save_table_file(table);

                  clear_terminal();
                  printf("Tupla removida com sucesso!\n");
                  pause_terminal();
                } while(valid_option == -1);
                break;
              default:
                break;
            };

            valid_option = -1;
          } while(valid_option == -1);
        } while(valid_option == -1);

        break;
      error_message:
      default:
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
