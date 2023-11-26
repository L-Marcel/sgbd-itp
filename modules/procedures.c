#include <stdio.h>
#include <ctype.h>
#include "procedures.h"

/// @brief Cria uma nova tabela valida.
/// @param tables lista de tabelas já existentes
/// @return em caso de sucesso, a própria tabela criada. Em caso de erro ou cancelamento, 
/// uma tabela vazia, para simbolizar à main que não é uma tabela invalida.
Table new_table_procedure(Tables tables) {
  Table new_table = create_empty_table();

  int qtd_columns = 0;
  char yes_or_no;
  
  bool table_exists = false;
  do {
    char exists_message[120];
    sprintf(
      exists_message, 
      "Já existe uma tabela chamada \"%s\"!\nNome da tabela (max: 49): ", 
      new_table.name
    );

    get_string(
      50, 
      new_table.name,
      table_exists? 
        exists_message : 
        "Nome da tabela (max: 49): "
    );
    table_exists = table_already_exists(new_table, tables);
  } while(table_exists);

  Column primary_column = {
    .is_primary_key = true,
    .type = T_NAT,
  };

  get_string(50, primary_column.name, "Nome da chave primária (max: 49): ");
  add_column(&new_table, primary_column);

  int valid_option = -1;
  do {
    int procedure_option = display_new_table_procedure_menu(new_table);
    int max_options = new_table.qtd_columns > 1? 3:2;
    valid_option = is_option_valid(procedure_option, max_options);

    bool will_create = true;

    if (valid_option == -1) continue;
    else if (valid_option == 0) will_create = false;

    Column new_column = {
      .is_primary_key = false,
      .name = "",
    };

    bool column_exists = false;

    valid_option = -1;

    int column_option;
    int column_valid_option = -1;
    switch (procedure_option) {
      case 2:
        do {
          char exists_message[120];
          sprintf(
            exists_message, 
            "Já existe uma uma coluna chamada \"%s\"!\nNome da coluna (max: 49): ", 
            new_column.name
          );

          get_string(
            50, 
            new_column.name,
            column_exists? 
              exists_message : 
              "Nome da coluna (max: 49): "
          );
          column_exists = column_already_exists(new_column, new_table);
        } while(column_exists);

        int type_option;
        int type_valid_option = -1;
        do {
          type_option = display_select_types_menu();
          type_valid_option = is_option_valid(type_option, 5);

          if(type_valid_option == -1) continue;

          new_column.type = type_option;
        } while(type_valid_option == -1);

        add_column(&new_table, new_column);
        break;
      case 3: // [TODO] Remover coluna 
        do {
          column_option = display_select_column_menu(new_table, " para remover", false);
          column_valid_option = is_option_valid(column_option, new_table.qtd_columns);

          if(column_valid_option == -1) continue;
          if(column_option == 0) break;

          delete_column(&new_table, column_option);
        } while(column_valid_option == -1);

        break;
      default:
        while(true) {
          printf(
            "Deseja realmente %s a tabela \"%s\"? (Y/N): ", 
            will_create? "criar":"descartar",
            new_table.name
          );

          scanf("%c", &yes_or_no);
          getchar();
          clear_terminal();
          if (tolower(yes_or_no) == 'y') {
            return will_create? new_table:create_empty_table();
          } else if (tolower(yes_or_no) == 'n') {
            valid_option = -1;
            break;
          };
        };
        break;
    };
  } while(valid_option == -1);
}