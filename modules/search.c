#include "search.h"
#include <stdio.h>

// Alguns tipos de função e parâmetros ainda são meramente ilustrativos 

/// @brief Irá pegar o input do usuário e chamar outras funções auxiliares
/// @param table a tabela
/// @param column_option a coluna da pesquisa
/// @param search_option a configuração de pesquisa
void search_main_caller(Table table, int column_option, int search_option) {
    Table aux_table = create_empty_table(); 
    aux_table = table;
    print_table(aux_table);
    pause_terminal();
}

/// @brief Irá pegar o número inserido pelo usuário (apenas para não strings/char)
/// e comparar com todos os valores da coluna 
/// @param user_number
/// @return -2, caso o número comparado seja apenas menor que o informado; 
/// -1, caso seja menor ou igual ao informado; 0, caso seja igual ao informado;
/// 1, caso seja maior ou igual; 2, caso seja apenas maior.
int number_is_equal_less_or_greater(double user_number) {
    return 0;
}

// Rascunho

void search_number();

void search_string();