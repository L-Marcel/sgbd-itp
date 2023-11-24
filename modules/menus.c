#include <stdio.h>

/// @brief Menu em loop que mostra as opções possíveis para o usuário utilizar
/// @return a opção escolhida
int displayDefaultMenu(int table_size) {
    int option;
    printf("\n\n-----Menu que vai ser melhorado depois!-----\n");
    printf("0 - Sair do programa\n");
    printf("1 - Criar uma nova tabela\n");
    if (table_size != 0) {
        printf("2 - Deletar uma tabela existente\n");
        printf("3 - Listar/selecionar tabela(s)\n");
    };
    printf("Opção: ");
    scanf("%i", &option);
    printf("----------------\n\n");
    return option;
}

/// @brief Menu secundário, acessado na opção 3 do menu anterior. Aguarda input do usuário de qual tabela será modificada
/// @return a opção escolhida
int displayTablesMenu() {
    int option;
    printf("\n\nSelecione a tabela que deseja alterar.\n\n");
    printf("Opção: ");
    scanf("%i", &option);
    printf("----------------\n\n");
    return option;
}