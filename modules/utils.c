#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers/utils.h"

/// @brief Função que captura um texto não vazio, em caso de texto invalido, 
/// repete a operação.
/// @param max_size tamanho máximo do texto
/// @param text o texto capturado
/// @param message o texto imprimido antes do input.
void get_string(unsigned long max_size, char text[max_size], char* message) {
  bool can_clear = true;
  char input[max_size + 2];
  do {
    if(can_clear) clear_terminal();
    printf("%s", message);

    fgets(input, max_size + 3, stdin);
    trim(strlen(input), input);

    if(strlen(input) >= max_size) {
      fflush(stdin);
      can_clear = false;
      clear_terminal();
      printf("O sistema só suporta entradas com no máximo 200 caracteres!\n");
    } else {
      can_clear = true;
    };
  } while(strlen(input) == 0 || strlen(input) >= max_size + 1);

  strcpy(text, input);
}

/// @brief Remove espaço vázio no começo e final de um texto.
/// @param size tamanho do texto
/// @param text o texto
void trim(unsigned long size, char text[size]) {
  for(int i = size - 1; i > 0; i--) {
    if(text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
      text[i] = '\0';
    } else if(text[i] != '\0') {
      break;
    };
  };

  int gap = 0;
  for(unsigned long i = 0; i < size - 1; i++) {
    if(text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
      gap++;
    } else {
      break;
    };
  };

  for(unsigned long i = gap; i < size - 1; i++) {
    text[i - gap] = text[i];
  };
  text[size - 1 - gap] = '\0';
}

/// @brief Soma um vetor de inteiros.
/// @param size tamanho do vetor
/// @param vector o vetor
/// @return somatório dos valores do vetor.
int sum(int size, int vector[size]) {
  int result = 0;

  for(int i = 0; i < size; i++) {
    result += vector[i];
  };

  return result;
}

/// @brief Limpa o terminal.
void clear_terminal() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

/// @brief Pausa o terminal.
void pause_terminal() {
  #ifdef _WIN32
	  system("pause");
	#else
    system("read -p \"Pressione ENTER para sair.\" saindo");
    clear_terminal();
	#endif
}

/// @brief Diz se uma string contem ou não um caractere especifico.
/// @param text a string
/// @param target o caractere
/// @return true, se conter; false, caso constrário.
bool include_char(char * text, char target) {
  for(unsigned long i = 0; i < strlen(text); i++) {
    if(text[i] == target) {
      return true;
    };
  };

  return false;
}

/// @brief Tolower uma string inteira.
/// @param original_string a string original
/// @param lowered_string a string lowered
void lower_string(char original_string[200], char lowered_string[200]) {
  for (unsigned int i = 0; i < strlen(original_string); i++) {
    lowered_string[i] = tolower(original_string[i]);
  }
  lowered_string[strlen(original_string)] = '\0';
}