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

    pause_terminal();
}

/// @brief Irá comparar o valor do record com o valor inserido pelo usuário
/// @param value_user o valor inserido pelo usuário
/// @param value_compare o valor do record no loop
/// @param type o tipo da coluna a ser pesquisada
/// @return EQ, caso os valores sejam iguais; LT, caso o valor do record seja
/// menor que o input do usuário; GT, caso o valor do record seja maior que o 
/// input do usuário
order compare(char value_user[200], char value_compare[200], types type) {
    int value_user_int, value_compare_int;
    float value_user_float, value_compare_float;
    double value_user_double, value_compare_double;
    char value_user_char[2], value_compare_char[2];
    char value_user_string[200], value_compare_string[200];

    switch (type) {
        case T_NAT:
        case T_INT:
            value_user_int = atoi(value_user);
            value_compare_int = atoi(value_compare);

            if (value_compare_int == value_user_int) {
                return EQ;
            } else if (value_compare_int < value_user_int) {
                return LT;
            } else if (value_compare_int > value_user_int) {
                return GT;
            }

            break;
        case T_FLOAT:
            sscanf(value_user, "%f", &value_user_float);
            sscanf(value_compare, "%f", &value_compare_float);

            if (value_compare_float == value_user_float) {
                return EQ;
            } else if (value_compare_float < value_user_float) {
                return LT;
            } else if (value_compare_float > value_user_float) {
                return GT;
            }

            break;
        case T_DOUBLE:
            sscanf(value_user, "%lf", &value_user_double);
            sscanf(value_compare, "%lf", &value_compare_double);

            if (value_compare_double == value_user_double) {
                return EQ;
            } else if (value_compare_double < value_user_double) {
                return LT;
            } else if (value_compare_double > value_user_double) {
                return GT;
            }

            break;
        case T_CHAR:
            value_user_char[0] = tolower(value_user[0]);
            value_user_char[1] = '\0';
            value_compare_char[0] = tolower(value_compare[0]);
            value_compare_char[1] = '\0';

            if (strcmp(value_compare_char, value_user_char) == 0) {
                return EQ;
            } else if (strcmp(value_compare_char, value_user_char) < 0) {
                return LT;
            } else if (strcmp(value_compare_char, value_user_char) > 0) {
                return GT;
            }

            break;
        case T_STRING:
            lower_string(value_user, value_user_string);
            lower_string(value_compare, value_compare_string);

            if (strcmp(value_compare_string, value_user_string) == 0) {
                return EQ;
            } else if (strcmp(value_compare_string, value_user_string) < 0) {
                return LT;
            } else if (strcmp(value_compare_string, value_user_string) > 0) {
                return GT;
            }

            break;
    }
}

/// @brief Irá filtrar a tabela de acordo com os parâmetros inseridos pelo usuário
/// @param table a tabela original
/// @param column_option a coluna escolhida para a pesquisa (Warning: NÃO é o índice!)
/// @param user_value o input do usuário para a pesquisa
/// @param filter_option a opção para filtragem da tabela
/// @return a tabela filtrada
Table filter_table(Table table, int column_option, char user_value[200], order filter_order) {
    int i, strcmp_result;
    // Tava dando warning sem o unsigned :P
    unsigned int j;
    order result_order;
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
            lower_string(user_value, lower_value);

            // printf("Valores: %s e %s\n", lower_record, lower_value);
            // pause_terminal();

            if (strstr(lower_record, lower_value) != NULL) {
                add_record(&result, table.records[i]);
            }
        }
    } else {
        for (i = 0; i < table.qtd_records; i++) {
            result_order = compare(user_value, table.records[i][column_option - 1].value, table.columns[column_option - 1].type);
            switch (filter_order) {
                case GT:
                    if (result_order == GT) {
                        add_record(&result, table.records[i]);
                    }
                    break;
                case GTE:
                    if (result_order == GT || result_order == EQ)  {
                        add_record(&result, table.records[i]);
                    }
                    break;
                case EQ:
                    if (result_order == EQ) {
                        add_record(&result, table.records[i]);
                    }
                    break;
                case LTE:
                    if (result_order == LT || result_order == EQ)  {
                        add_record(&result, table.records[i]);
                    }
                    break;
                case LT:
                    if (result_order == LT)  {
                        add_record(&result, table.records[i]);
                    }
                    break;
            };
        }
    }

    print_table(result);

    return result;
}