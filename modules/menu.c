#include <stdio.h>

/// @brief Menu em loop que mostra as opções possíveis para o usuário utilizar
int displayMenu() {
    int option;
    printf("\n\n-----Menu que vai ser melhorado depois!-----\n");
    printf("0 - Sair do programa\n");
    printf("1 - Printar a opção 1\n");
    printf("2 - Mostrar tabelas existentes\n");
    printf("3 - Adicionar uma tabela pré-definida (new_table)\n");
    printf("4 - Deletar uma tabela pré-definida (new_table)\n\n");
    printf("Opção: ");
    scanf("%i", &option);
    printf("\n----------------\n");
    return option;
}