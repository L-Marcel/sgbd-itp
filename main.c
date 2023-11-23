#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "modules/prints.h"

int main() {
  UINT CPAGE_UTF8 = 65001;
  SetConsoleOutputCP(CPAGE_UTF8);

  print_table();

  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_DEFAULT);
  return 0;
}