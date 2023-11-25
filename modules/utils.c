#include <stdio.h>
#include "utils.h"

/// @brief Remove espaço vázio no começo e final de um texto
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