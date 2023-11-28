#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include "modules/procedures.h"

#ifdef _WIN32
  #include <windows.h>
#endif

int main() {
  int table_option, procedure_option, table_exists;
  #ifdef _WIN32
    UINT CPAGE_UTF8 = 65001;
    SetConsoleOutputCP(CPAGE_UTF8);
  #endif

  Table new_table;
  Record *new_tuple;

  int menu_option = -1;
  int valid_option = -1;

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
          /// Ajudinha pra não se perder:
          ///
          /// get_data_from_table(table) -> files.c, linha 137
          /// set_new_table_file(table) (mudar nome depois pra set_table_file) -> files.c, linha 86
          /// new_tuple_procedure(table) -> procedures.c, linha 143
          /// funções de conversão (string <-> CSV) -> tables.c, a partir da linha 193
          ///
          /// Passo a passo do algoritmo (até a etapa 2, tá funcionando certo):
          ///
          /// 1 - A atribuição do table ocorre (linha 75), pegando somente o nome da tabela
          /// 2 - Agora na linha 97, tá indo no CSV da tabela e pegando todos os dados da tabela através 
          /// do get_data_from_table(table);
          /// 3 - Depois, na linha 108, tá indo pra o procedimento em que o usuário
          /// insire os dados da nova tupla. Até o momento, o programa consegue, com sucesso,
          /// inserir os dados quando é a primeira tupla cadastrada. Quando já tem uma  ou mais tupla,
          /// ainda não tá dando certo.
          /// 
          /// 4 - Depois de *teoricamente* tudo dar certo, vai para a linha 113 e sobrescreve
          /// a tabela com a nova tupla. 
          ///
          // [NOVO]  

          table = get_data_from_table(table);
          do {
            procedure_option = display_procedures_menu(table);
            valid_option = is_option_valid(procedure_option, 5);
            if (valid_option == 0) break;

            switch (procedure_option) {
              case 1: // [PARCIAL] Criar um novo registro na tabela 

                // [CHANGE] Bug corrigido, mas como não está carregando as
                // tuplas anteriores, a tabela sempre vai ficar só com uma
                table = new_tuple_procedure(table);
                if (strcmp(table.records[0][0].value, "") != 0) {
                  save_table_file(table);
                  printf("Tupla adicionada com sucesso!\n");
                } else {
                  printf("Operação cancelada!\n");
                }
                pause_terminal();
                break;
              case 2: // [TODO] Listar todos os dados da tabela
                print_table(table);
                pause_terminal();
                break;
              case 3: // [TODO] Pesquisar valor na tabela
                break;
              case 4: // [TODO] Apagar uma registro da tabela
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
