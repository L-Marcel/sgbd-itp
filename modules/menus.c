#include <stdio.h>
#include "menus.h"

/// @brief Menu em loop que mostra as opções possíveis para o usuário utilizar
/// @return a opção escolhida
int displayDefaultMenu(int table_size) {
    int option;
    clear_terminal();
    printf("====== Menu que vai ser melhorado depois! ======\n");
    printf("0 → Sair do programa\n");
    printf("1 → Criar uma nova tabela\n");
    if (table_size != 0) {
        printf("2 → Deletar uma tabela existente\n");
        printf("3 → Listar/selecionar tabela(s)\n");
    };
    printf("================================================\n");
    printf("Opção: ");
    scanf("%i", &option);
    return option;
}

/// @brief Menu secundário, acessado na opção 3 do menu anterior. Aguarda input do usuário de qual tabela será modificada
/// @param tables as tabelas
/// @return a opção escolhida
int displayTablesMenu(Tables tables) {
    int option;
    clear_terminal();
    printf("============== Selecione uma tabela ============\n");
    printf("0 → Voltar ao menu\n");
    print_tables(tables, 1);
    printf("================================================\n");
    printf("Opção: ");
    scanf("%i", &option);
    return option;
}

/// Não sei ainda, só botei aqui (menu pra remover tupla, add tupla, procurar coisas, etc)
int displayProceduresMenu() {
    int option;
    clear_terminal();
    printf("========= Selecione o que deseja fazer com a tabela =========\n");
    printf("0 - Voltar ao menu\n");
    printf("1 - Criar uma nova linha na tabela\n");
    printf("2 - Listar todos os dados da tabela\n");
    printf("3 - Pesquisar valor na tabela\n");
    printf("4 - Apagar uma tupla da tabela\n");
    printf("=============================================================\n");
    printf("Opção: ");
    scanf("%i", &option);
    return option;
}

/// @brief Valida a opção de menu escolhida
/// @param option opção escolhida
/// @param qtd_menu_options quantidade de opções/indexs disponíveis para escolha
/// @return 0, se o usuário inserir 0 (voltar ao menu) ou se a opção escolhida ultrapassar a quantidade de opções disponíves; 1, se nada do que foi citado anteriormente acontecer
int isOptionValid(int option, int qtd_menu_options) {
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
