#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "modules/prints.h"
#include "modules/files.h"

int main() {
  UINT CPAGE_UTF8 = 65001;
  SetConsoleOutputCP(CPAGE_UTF8);

  create_database_folder();
  
  print_table();
  printf("Tabela sava!");

  Table table = {
    .name = "Teste",
  };

  save_table(table);

  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_DEFAULT);
  return 0;
}