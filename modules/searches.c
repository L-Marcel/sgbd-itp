#include "headers/searches.h"
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
        char input[60];
        sprintf(input, "Digite um valor do tipo \"%s\" para pesquisar: ", get_type_name(type));
        get_string(200, value, input);
        is_valid = validate_record_value(value, type, error);
        if(!is_valid) {
            clear_terminal();
            printf("%s\n", error);
        };
    } while(!is_valid);

    filter_table(aux_table, column_option, value, search_option);
    pause_terminal();
}

/// @brief Irá comparar dois valores
/// @param value_one o primeiro valor 
/// @param value_two o valor do record no loop
/// @param type o tipo dos valores
/// @return EQ, caso os valores sejam iguais; 
/// LT, caso o segundo valor seja menor que o primeiro; 
/// GT, caso contrário.
order compare(char value_one[200], char value_two[200], types type) {
    int value_one_int, value_two_int;
    float value_one_float, value_two_float;
    double value_one_double, value_two_double;
    char value_one_char[2], value_two_char[2];
    char value_one_string[200], value_two_string[200];

    switch (type) {
        case T_NAT:
        case T_INT:
            value_one_int = atoi(value_one);
            value_two_int = atoi(value_two);

            if (value_two_int == value_one_int) {
                return EQ;
            } else if (value_two_int < value_one_int) {
                return LT;
            } else if (value_two_int > value_one_int) {
                return GT;
            };

            break;
        case T_FLOAT:
            sscanf(value_one, "%f", &value_one_float);
            sscanf(value_two, "%f", &value_two_float);

            if (value_two_float == value_one_float) {
                return EQ;
            } else if (value_two_float < value_one_float) {
                return LT;
            } else if (value_two_float > value_one_float) {
                return GT;
            };

            break;
        case T_DOUBLE:
            sscanf(value_one, "%lf", &value_one_double);
            sscanf(value_two, "%lf", &value_two_double);

            if (value_two_double == value_one_double) {
                return EQ;
            } else if (value_two_double < value_one_double) {
                return LT;
            } else if (value_two_double > value_one_double) {
                return GT;
            };

            break;
        case T_CHAR:
            value_one_char[0] = tolower(value_one[0]);
            value_one_char[1] = '\0';
            value_two_char[0] = tolower(value_two[0]);
            value_two_char[1] = '\0';

            if (strcmp(value_two_char, value_one_char) == 0) {
                return EQ;
            } else if (strcmp(value_two_char, value_one_char) < 0) {
                return LT;
            } else if (strcmp(value_two_char, value_one_char) > 0) {
                return GT;
            };

            break;
        case T_STRING:
            lower_string(value_one, value_one_string);
            lower_string(value_two, value_two_string);

            if (strcmp(value_two_string, value_one_string) == 0) {
                return EQ;
            } else if (strcmp(value_two_string, value_one_string) < 0) {
                return LT;
            } else if (strcmp(value_two_string, value_one_string) > 0) {
                return GT;
            };

            break;
        default:
            break;
    }
}

/// @brief Converte o typo ordem para um texto.
/// @param ord o tipo ordem
/// @return O texto, com no máximo 40 caracteres
char* get_order_name(order ord) {
  switch(ord) {
    case LT:
      return "Valores menores que o informado";
    case LTE:
      return "Valores menores ou iguais ao informado";
    case EQ:
      return "Valores iguais ao informado";
    case GT:
      return "Valores maiores que o informado";
    case GTE:
      return "Valores maiores ou iguais ao informado";
    case CT:
      return "Valores próximos do informado";
    default:
      return "Indefinida";
  };
}

/// @brief Irá filtrar a tabela de acordo com os parâmetros inseridos pelo usuário
/// @param table a tabela original
/// @param column_option a coluna escolhida para a pesquisa (Warning: NÃO é o índice!)
/// @param user_value o input do usuário para a pesquisa
/// @param filter_option a opção para filtragem da tabela
/// @return a tabela filtrada
Table filter_table(Table table, int column_option, char user_value[200], order filter_order) {
    int i, strcmp_result;

    unsigned int j;
    order result_order;
    char lower_record[200] = "";
    char lower_value[200] = "";

    Table result = create_empty_table();
    strcpy(result.name, table.name);
    for(i = 0; i < table.qtd_columns; i++) {
        add_column(&result, table.columns[i]);
    };

    if(filter_order == CT) {
        for(i = 0; i < table.qtd_records; i++) {
            lower_string(table.records[i][column_option - 1].value, lower_record);
            lower_string(user_value, lower_value);

            if(strstr(lower_record, lower_value) != NULL) {
                add_record(&result, table.records[i]);
            };
        };
    } else {
        for(i = 0; i < table.qtd_records; i++) {
            result_order = compare(
                user_value, 
                table.records[i][column_option - 1].value, 
                table.columns[column_option - 1].type
            );

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
                default:
                    break;
            };
        };
    };

    for(int i = 0; i < result.qtd_records; i++) {
        Record * next = result.records[i];
        for(int j = i; j < result.qtd_records; j++) {
            if(LT == compare(
                next[column_option - 1].value, 
                result.records[j][column_option - 1].value, 
                result.columns[column_option - 1].type
            )) {
                Record * old_next = next;
                next = result.records[j];
                result.records[j] = old_next;
            };
        };

        result.records[i] = next;
    };

    clear_terminal();
    print_table(result, "encontradas");
    printf(
        "Coluna alvo: %s (%s)\nValor alvo: %s\nOrdem: %s\n",
        result.columns[column_option - 1].name,
        get_type_name(result.columns[column_option - 1].type),
        user_value,
        get_order_name(filter_order)
    );
    print_divisor("", 0);

    return result;
}
