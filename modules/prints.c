#include <stdio.h>
#include <stdlib.h>
#include "prints.h"

/// @brief Imprime as tabelas disponíveis.
/// @param tables lista de tabelas
/// @param start número do primeiro elemento da lista 
void print_tables(Tables tables, int start){
  tables = sort_tables(tables);
  
  //essa imprimirá a lista de tabelas!
  for(int i = 0; i < tables.size; i++) {
    //começa a imprimir do {start} porque o 0 será a opção de cancelar
    printf("[%d] → %s\n", i + start, tables.list[i].name);
  };
}

void print_table(){
  //essa imprimirá a tabela com os dados!
  printf("Olá mundo! Isso vai dar muito trabalho!");
}

/// @brief Gera divisores com um título no meio.
/// @param title o título, tamanho máximo 53
void print_divisor(char title[53]) {
  int size = strlen(title);

  if(size == 0) {
    printf("======================================================\n");
    return;
  };

  int left = 0;
  int right = 0;
  int max = 54 - size;

  if(size != 0) max -= 2; 
  if(size % 2 == 1) {
    max++;
  };

  left += max/2;
  right += max/2;

  char left_divider[55] = "======================================================";
  char right_divider[55] = "======================================================";
  left_divider[left] = '\0';
  right_divider[right] = '\0';

  printf("%s %s %s\n", left_divider, title, right_divider);
}