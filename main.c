#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include "modules/all_modules.h"

#ifdef _WIN32
  #include <windows.h>
#endif

int main() {
  int menu_option, table_option;
  #ifdef _WIN32
    UINT CPAGE_UTF8 = 65001;
    SetConsoleOutputCP(CPAGE_UTF8);
  #endif

  Tables tables, new_table;

  while (menu_option != 0) {
    clear_terminal();
    tables = get_tables();
    menu_option = displayDefaultMenu(tables.size);
    clear_terminal();
    switch (menu_option) {
      // Agora tem um case 0 pq como não tinha antes, qnd inseria 0 ia pro 
      // case default antes de encerrar o programa. Tá um pouquinho gambiarra,
      // n gostei mt :P
      case 0:
        break;
      case 1:
        printf("\nCriou a tabela! (Ilustrativo)\n");
        break;
      case 2:
        // Se não tiver tabelas e mesmo assim o usuário inserir "2", vai para
        // o default case do switch, que é ativado, também, quando nenhuma das 
        // opções corresponde aos cases (é o else do switch-case). 
        if(tables.size == 0) {
          goto error_message;
        };
        printf("\nDeletou a tabela! (Ilustrativo):\n");
        break;
      case 3:
        // Mesma coisa do 2, só que com o 3. Fica meio feiozinho ali em baixo, 
        // mas não consigo pensar em nenhuma forma melhor de fazer, por enquanto
        if(tables.size == 0) {
          goto error_message;
        };
        table_option = displayTablesMenu(tables);
        printf("Você escolheu mudar a tabela %i! Redirecionando para o menu principal.", table_option);
        break;
      error_message:
      default:
        printf("\nOpção inválida. Tente novamente.\n");
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