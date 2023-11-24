#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "modules/all_modules.h"

int main() {
  int option;
  UINT CPAGE_UTF8 = 65001;
  Tables tables;
  Table new_table;
  SetConsoleOutputCP(CPAGE_UTF8);

  create_database_folder();

  print_table();

  //----- teste
  Table table = {
    .name = "A",
  };
  save_table(table);

  Table table2 = {
    .name = "B",
  };
  save_table(table2);

  //  Tables tables = get_tables();
  //  printf("\nLista de tabelas:\n");

  //  print_tables(tables, 1);
  //----- teste

  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_DEFAULT);
  //  ̶Resumo da ópera: modularizei apenas os prints e o scanf da opção. Estes estão em "./modules/menu.c" Fica menos poluido visualmente aqui na main.
  while (option != 0) {
    option = displayMenu();
    switch (option) {
      case 1:
        printf("\nSelecionou a 1!\n");
        break;
      case 2:
        tables = get_tables();
        printf("\nLista de tabelas:\n");
        print_tables(tables, 1);
        break;
      case 3:
        strcpy(new_table.name, "new_table");
        save_table(new_table);
        printf("\nTabela adicionada.\n");
        break;
      case 4:
        delete_table(new_table);
        printf("\nTabela deletada.\n");
        break;
    };
  };
  printf("Programa encerrado.\n");
  return 0;
}