#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"

/// @brief Captura o natural que representa a opção escolhida pelo usuário.
/// @param option a opção escolhida
/// @return -1 → se for inválido; o natural escolhido → se for valido.
int get_nat_option() {
    int option;
    char line[20];
    fgets(line, 20, stdin);
    int success = sscanf(line, "%i", &option);
    if(success == 0 || option < 0) option = -1;
    return option;
}

/// @brief Valida a opção de menu escolhida.
/// @param option opção escolhida
/// @param qtd_menu_options quantidade de opções/indexes disponíveis para escolha
/// @return 0 → se o usuário inserir 0 (voltar ao menu);
/// (-1) → se receber uma opção inválida; 1 → se nada do que 
/// foi citado anteriormente acontecer.
int is_option_valid(int option, int qtd_menu_options) {
    clear_terminal(); 
    if (option < 0 || option > qtd_menu_options) {
        return -1;
    } else if (option == 0) {
        return 0;
    } else {
        return 1;
    }
}

/// @brief Menu em loop que mostra as opções possíveis para o usuário utilizar.
/// @return A opção escolhida.
int display_default_menu(int table_size) {
    clear_terminal();
    print_divisor("SGDB / ITP");
    printf("[0] → Sair do programa\n");
    printf("[1] → Criar uma nova tabela\n");
    if (table_size != 0) {
        printf("[2] → Deletar uma tabela existente\n");
        printf("[3] → Listar/selecionar tabela(s)\n");
    };
    print_divisor("");
    printf("Opção: ");
    return get_nat_option();
}

/// @brief Menu secundário, acessado na opção 3 do menu anterior. 
/// Aguarda input do usuário de qual tabela será modificada.
/// @param tables as tabelas
/// @return A opção escolhida.
int display_tables_menu(Tables tables, char complement[26]) {
    clear_terminal();
    char title[47];
    sprintf(title, "Tabelas disponíveis%s", complement);
    print_divisor(title);
    print_tables(tables, 1);
    print_divisor("");
    printf("[0] → Voltar ao menu\n");
    print_divisor("");
    printf("Opção: ");
    return get_nat_option();
}

/// @brief Menu de operações envolvendo uma tabela específica.
/// @param table a tabela
/// @return A opção escolhida.
int display_procedures_menu(Table table) {
    clear_terminal();
    print_divisor(table.name);
    printf("[1] → Criar um novo registro na tabela\n");
    printf("[2] → Listar todos os dados da tabela\n");
    printf("[3] → Pesquisar valor na tabela\n");
    printf("[4] → Apagar uma registro da tabela\n");
    print_divisor("");
    printf("[0] → Voltar ao menu\n");
    print_divisor("");
    printf("Opção: ");
    return get_nat_option();
}

/// @brief Menu de opções durante criação de tabela
/// @param table a tabela
/// @return A opção escolhida
int display_new_table_procedure_menu(Table table) {
    clear_terminal();
    print_divisor("Criar nova tabela");
    
    printf("Tabela: %s\n", table.name);
    printf(
        "Colunas:\n∘ %s : %s (chave primaria)\n", 
        table.columns[0].name,
        get_type_name(table.columns[0].type)
    );

    for(int i = 1; i < table.qtd_columns; i++) {
        printf(
            "∘ %s : %s\n", 
            table.columns[i].name,
            get_type_name(table.columns[i].type)
        );
    };

    print_divisor("");
    printf("[0] → Cancelar\n");
    printf("[1] → Finalizar\n");
    printf("[2] → Adicionar uma coluna\n");
    if(table.qtd_columns > 1) {
      printf("[3] → Remover uma coluna\n");
    };

    print_divisor("");
    printf("Opção: ");
    return get_nat_option();
}

/// @brief Menu de operações de tipos para a coluna.
/// @return A opção escolhida.
int display_select_types_menu() {
    clear_terminal();
    print_divisor("Escolha o tipo da coluna");

    // Já está na ordem do enum!
    printf("[0] → Nat\n");
    printf("[1] → Int\n");
    printf("[2] → Float\n");
    printf("[3] → Double\n");
    printf("[4] → Char\n");
    printf("[5] → String\n");

    print_divisor("");
    printf("Opção: ");
    return get_nat_option();
}

/// @brief Menu para selecionar coluna de uma tabela.
/// @param table a tabela
/// @param include_primary_keu se deve ou não incluir a chave primária
/// @return A opção escolhida.
int display_select_column_menu(Table table, char complement[26], bool include_primary_key) {
    clear_terminal();
    char title[47];
    sprintf(title, "Colunas disponíveis%s", complement);
    print_divisor(title);
    print_columns(table, 1, include_primary_key);
    print_divisor("");
    printf("[0] → Voltar\n");
    print_divisor("");
    printf("Opção: ");
    return get_nat_option();
}