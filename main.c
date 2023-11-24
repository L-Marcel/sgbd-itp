#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "modules/all_modules.h"

int main() {
  UINT CPAGE_UTF8 = 65001;
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

  Tables tables = get_tables();
  printf("\nLista de tabelas:\n");

  print_tables(tables, 1);
  //----- teste

  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_DEFAULT);
  return 0;
}