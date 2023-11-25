#include <stdio.h>
#include <stdlib.h>
#include "prints.h"

/// @brief Imprime as tabelas disponíveis
/// @param tables lista de tabelas
/// @param start número do primeiro elemento da lista 
void print_tables(Tables tables, int start){
  tables = sort_tables(tables);
  
  //essa imprimirá a lista de tabelas!
  for(int i = 0; i < tables.size; i++) {
    //começa a imprimir do {start} porque o 0 será a opção de cancelar
    printf("%d → %s\n", i + start, tables.list[i].name);
  };
}

void print_table(){
  //essa imprimirá a tabela com os dados!
  printf("Olá mundo! Isso vai dar muito trabalho!");
}

/// @brief Limpa o terminal
void clear_terminal() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

/// @brief Pausa o terminal
void pause_terminal() {
  #ifdef _WIN32
	  system("pause");
	#else
	  system("read -p \"Pressione ENTER para sair.\" saindo");
	#endif
}