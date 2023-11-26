#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/// @brief Função que captura um texto não vazio, em caso de texto invalido, repete a operação.
/// @param max_size tamanho máximo do texto
/// @param text o texto capturado
/// @param message a texto imprimido antes do input
void get_string(int max_size, char text[max_size], char* message) {
  do {
    clear_terminal();
    printf("%s", message);
    fgets(text, max_size, stdin);
    trim(strlen(text), text);
    //nunca vai passar um texto vazio
  } while(strlen(text) == 0);
}

/// @brief Remove espaço vázio no começo e final de um texto.
/// @param size tamanho do texto
/// @param text o texto
void trim(int size, char text[size]) {
  for(int i = size - 1; i > 0; i--) {
    if(text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
      text[i] = '\0';
    } else if(text[i] != '\0') {
      break;
    };
  };

  int gap = 0;
  for(int i = 0; i < size - 1; i++) {
    if(text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
      gap++;
    } else {
      break;
    };
  };

  for(int i = gap; i < size - 1; i++) {
    text[i - gap] = text[i];
  };
  text[size - 1 - gap] = '\0';
}

/// @brief Limpa o terminal
void clear_terminal() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

/// @brief Pausa o terminal
void pause_terminal() {
  #ifdef _WIN32
	  system("pause");
	#else
    system("read -p \"Pressione ENTER para sair.\" saindo");
    clear_terminal();
	#endif
}