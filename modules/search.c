#include "search.h"
#include <stdio.h>

// Alguns tipos de função e parâmetros ainda são meramente ilustrativos 

/// @brief Irá pegar o input do usuário e chamar outras funções auxiliares
/// @param table a tabela
/// @param column_option a coluna da pesquisa
/// @param search_option a configuração de pesquisa
void search_main_caller(Table table, int column_option, int search_option) {
    Table aux_table = table;

    // Sugestão, transforma o tipo de search_option para o enum order
    // e se quiser dá até para alterar os valores do enum
    // ai nessa primeira linha da função já chama o filter_table
    // logo depois de solicitar o valor (lembrando que tem que validar o valor
    // solicitado). Se for Nat, nada de entradas negativas. Mas já temos isso em
    // outra parte do código.

    print_table(aux_table);
    printf("Diff examples: \n");
    printf("- 'A' - 'B' = %d ⇒  'A' > 'B'\n", strcmp("A", "B"));
    printf("- 5 - 2 = %d ⇒  5 > 2\n", 5 - 2);

    printf("- \"Lucas\" - \"Natham\" = %d ⇒  \"Natham\" > \"Lucas\"\n", strcmp("Lucas", "Natham"));
    printf("- \"Natham\" - \"Lucas\" = %d ⇒  \"Natham\" > \"Lucas\"\n", strcmp("Natham", "Lucas"));
    // Não é o tamanho que está sendo comparado nas strings!
    printf("- \"bcd\" - \"abc\" = %d ⇒  \"abc\" < \"bcd\"\n",  strcmp("bcd", "abc"));
    printf("- \"abc\" - \"bcd\" = %d ⇒  \"abc\" < \"bcd\"\n", strcmp("abc", "bcd"));
    printf("- \"abc\" - \"abc\" = %d ⇒  \"abc\" = \"abc\"\n", strcmp("abc", "abc"));
    // Lembrando que, se for maior, é maior OU igual também!


    pause_terminal();
}

// Apenas esboço: o compare e to são os valores para serem
// comparados e o type é o tipo da coluna, pensei em receber
// como double, mas dá erro de tipagem
order compare(char compare[200], char to[200], types type) {
    return EQ;
}

// Apenas esboço: recebe o valor a ser procurado como string mesmo, e
// usa a função compare e o filter_order em um for para ver quais elementos
// adicionar ao result. 
Table filter_table(Table table, char value[200], order filter_order) {
    Table result = create_empty_table();
    // Tem que lembrar de adicionar as colunas da table original
    // acho que temos uma função add_column

    return result;
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