#include <stdio.h>
#include <string.h>
#include "menus.h"

/// @brief Gera os divisores do menu com um título no meio
/// @param title o título, tamanho máximo 47
void print_menu_divisor(char title[53]) {
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

/// @brief Menu em loop que mostra as opções possíveis para o usuário utilizar
/// @return a opção escolhida
int display_default_menu(int table_size) {
    int option;
    clear_terminal();
    print_menu_divisor("SGDB / ITP");
    printf("[0] → Sair do programa\n");
    printf("[1] → Criar uma nova tabela\n");
    if (table_size != 0) {
        printf("[2] → Deletar uma tabela existente\n");
        printf("[3] → Listar/selecionar tabela(s)\n");
    };
    print_menu_divisor("");
    printf("Opção: ");
    scanf("%i", &option);
    getchar();
    return option;
}

/// @brief Menu secundário, acessado na opção 3 do menu anterior. Aguarda input do usuário de qual tabela será modificada
/// @param tables as tabelas
/// @return a opção escolhida
int display_tables_menu(Tables tables, char complement[26]) {
    int option;
    clear_terminal();
    char title[47];
    sprintf(title, "Tabelas disponíveis%s", complement);
    print_menu_divisor(title);
    print_tables(tables, 1);
    print_menu_divisor("");
    printf("[0] → Voltar ao menu\n");
    print_menu_divisor("");
    printf("Opção: ");
    scanf("%i", &option);
    getchar();
    return option;
}

/// @brief Menu de operações envolvendo uma tabela específica
/// @param table a tabela
/// @return a opção escolhida
int display_procedures_menu(Table table) {
    int option;
    clear_terminal();
    print_menu_divisor(table.name);
    printf("[1] → Criar um novo registro na tabela\n");
    printf("[2] → Listar todos os dados da tabela\n");
    printf("[3] → Pesquisar valor na tabela\n");
    printf("[4] → Apagar uma registro da tabela\n");
    print_menu_divisor("");
    printf("[0] → Voltar ao menu\n");
    print_menu_divisor("");
    printf("Opção: ");
    scanf("%i", &option);
    getchar();
    return option;
}

/// @brief Valida a opção de menu escolhida
/// @param option opção escolhida
/// @param qtd_menu_options quantidade de opções/indexs disponíveis para escolha
/// @return 0, se o usuário inserir 0 (voltar ao menu) ou se a opção escolhida ultrapassar a quantidade de opções disponíves; 1, se nada do que foi citado anteriormente acontecer
int is_option_valid(int option, int qtd_menu_options) {
    if (option == 0) {
        return 0;
    } else if (option > qtd_menu_options) {
        printf("A opção escolhida não é valida. Redirecionando ao menu principal.\n");
        pause_terminal();
        return 0;
    } else {
        return 1;
    }
}
