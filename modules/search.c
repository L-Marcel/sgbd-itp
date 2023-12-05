#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/// @brief Irá pegar o input do usuário e chamar outras funções auxiliares
/// @param table a tabela
/// @param column_option a coluna da pesquisa
/// @param search_option a configuração de pesquisa
void search_main_caller(Table table, int column_option, order search_option) {
    Table aux_table = table;
    char value[200], error[200];
    types type = table.columns[column_option - 1].type;
    bool is_valid;
    do {
        get_string(200, value, "Digite o valor de parâmetro para a pesquisa: ");
        is_valid = validate_record_value(value, type, error);
        if(!is_valid) {
            printf("%s", error);
        }
    } while (!is_valid);

    filter_table(aux_table, column_option, value, search_option);

    // print_table(aux_table);
    // printf("Diff examples: \n");
    // printf("- 'A' - 'B' = %d ⇒  'A' > 'B'\n", strcmp("A", "B"));
    // printf("- 5 - 2 = %d ⇒  5 > 2\n", 5 - 2);

    // printf("- \"Lucas\" - \"Natham\" = %d ⇒  \"Natham\" > \"Lucas\"\n", strcmp("Lucas", "Natham"));
    // printf("- \"Natham\" - \"Lucas\" = %d ⇒  \"Natham\" > \"Lucas\"\n", strcmp("Natham", "Lucas"));
    // // Não é o tamanho que está sendo comparado nas strings!
    // printf("- \"bcd\" - \"abc\" = %d ⇒  \"abc\" < \"bcd\"\n",  strcmp("bcd", "abc"));
    // printf("- \"abc\" - \"bcd\" = %d ⇒  \"abc\" < \"bcd\"\n", strcmp("abc", "bcd"));
    // printf("- \"abc\" - \"abc\" = %d ⇒  \"abc\" = \"abc\"\n", strcmp("abc", "abc"));
    // // Lembrando que, se for maior, é maior OU igual também!

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
Table filter_table(Table table, int column_option, char value[200], order filter_order) {
    int i, strcmp_result;
    // Tava dando warning sem o unsigned :P
    unsigned int j;
    char lower_record[200] = {0};
    char lower_value[200] = {0};

    Table result = create_empty_table();
    for (i = 0; i < table.qtd_columns; i++) {
        add_column(&result, table.columns[i]);
    }

    // O filter_order ser NT é o mesmo que ter certeza que o type é string.
    if (filter_order == NT) {
        for (i = 0; i < table.qtd_records; i++) {
            lower_string(table.records[i][column_option - 1].value, lower_record);
            lower_string(value, lower_value);

            // printf("Valores: %s e %s\n", lower_record, lower_value);
            // pause_terminal();

            if (strstr(lower_record, lower_value) != NULL) {
                add_record(&result, table.records[i]);
            }
        }
    } else {
        for (i = 0; i < table.qtd_records; i++) {
            compare(value, table.records[i][column_option].value, table.columns[column_option].type);
        };
    }

    print_table(result);

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