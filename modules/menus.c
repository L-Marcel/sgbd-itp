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