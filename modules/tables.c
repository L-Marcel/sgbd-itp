#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tables.h"

/// @brief Converte o typo enumerado para um texto.
/// @param type o tipo enumerado
/// @return A texto, com tamanho máximo de 10 chars.
char* get_type_name(types type) {
  switch (type) {
    case T_NAT:
      return "Nat";
    case T_INT:
      return "Int";
    case T_STRING:
      return "String";
    case T_CHAR:
      return "Char";
    case T_DOUBLE:
      return "Double";
    case T_FLOAT:
      return "Float";
    default:
      return "Undefined";
  }
}

/// @brief Converte o texto para um type
/// @param str a string do tipo enumerado
/// @return O tipo correspondente à string
types get_type_original(char str[10]) {
  if (strcmp(str, "Nat") == 0) {
    return T_NAT;
  } else if (strcmp(str, "Int") == 0) {
    return T_INT;
  } else if (strcmp(str, "String") == 0) {
    return T_STRING;
  } else if (strcmp(str, "Char") == 0) {
    return T_CHAR;
  } else if (strcmp(str, "Double") == 0) {
    return T_DOUBLE;
  } else if (strcmp(str, "Float") == 0) {
    return T_FLOAT;
  } 
}

/// @brief Ordena a lista de tabelas pelo nome delas.
/// @param tables as tabelas
/// @return As tabelas ordenadas por nome.
Tables sort_tables(Tables tables) {
  for(int i = 0; i < tables.size; i++) {
    Table next = tables.list[i];
    for(int j = i; j < tables.size; j++) {
      if(strcmp(tables.list[j].name, next.name) < 0) {
        Table old_next = next;
        next = tables.list[j];
        tables.list[j] = old_next;
      };
    };

    tables.list[i] = next;
  };

  return tables;
}

/// @brief Adiciona uma tabela na lista de tabelas.
/// @param tables a lista de tabelas
/// @param table a tabela a ser adicionada
void add_table(Tables * tables, Table table) {
  tables -> size++;
  tables -> list = realloc(tables -> list, sizeof(Table) * tables -> size);
  tables -> list[tables -> size - 1] = table;
}

/// @brief Inicializa uma tabela vazia.
/// @return a tabela vazia
Table create_empty_table() {
  Table table = {
    .name = "",
    .qtd_columns = 0,
    .qtd_records = 0,
  };

  //É necessário alocar para conseguirmos
  //realocar depois
  table.columns = malloc(0);
  table.records = malloc(0);

  return table;
}

/// @brief Inicializa uma linha/tupla vazia, de acordo com a quantidade
/// de colunas da tabela.
/// @return a tupla vazia
Record *create_empty_tuple(int qtd_columns) {
  Record *tuple = calloc(qtd_columns, sizeof(Record));
  return tuple;
}

/// @brief Adiciona uma coluna em uma tabela.
/// @param table a tabela
/// @param column a coluna
void add_column(Table * table, Column column) {
  table -> qtd_columns++;
  table -> columns = realloc(table -> columns, sizeof(Column) * table -> qtd_columns);
  table -> columns[table -> qtd_columns - 1] = column;
}

/// @brief Apaga uma coluna de uma tabela.
/// @param table a tabela
/// @param column_index o index da coluna
void delete_column(Table * table, int column_index) {
  for(int i = 0; i < table -> qtd_columns - 1; i++) {
    if(i >= column_index) {
      table -> columns[i] = table -> columns[i + 1];
    };
  };

  table -> qtd_columns--;
  table -> columns = realloc(table -> columns, sizeof(Column) * table -> qtd_columns);
}

/// @brief Remove uma tabela da lista de tabelas
/// @param table_index index da tabela
/// @param tables lista de tabelas
void delete_table(int table_index, Tables * tables) {
  for(int i = 0; i < tables -> size - 1; i++) {
    if(i >= table_index) {
      tables -> list[i] = tables -> list[i + 1];
    };
  };

  tables -> size--;
  tables -> list = realloc(tables -> list, sizeof(Table) * tables -> size);
}

/// @brief Percorre a database para saber se a tabela inserida pelo usuário já existe.
/// @param table a tabela inserida
/// @param tables a lista de tabelas
/// @return true, se houver tabela igual na database; false, se não houver tabela igual.
bool table_already_exists(Table table, Tables tables) {
  for (int i = 0; i < tables.size; i++) {
    if (strcmp(table.name, tables.list[i].name) == 0) {
      return true;
    };
  };

  return false;
}

/// @brief Percorre as colunas da tabela para saber se a coluna inserida pelo usuário já existe.
/// @param column a coluna inserida
/// @param table a tabela
/// @return true, se houver coluna igual na tabela; false, se não houver coluna igual.
bool column_already_exists(Column column, Table table) {
  for (int i = 0; i < table.qtd_columns; i++) {
    if (strcmp(column.name, table.columns[i].name) == 0) {
      return true;
    };
  };

  return false;
}

/// @brief Percorre a primeira linha da tabela e conta a quantidade de colunas da tabela.
/// @param line a linha da tabela (estilo csv)
/// @return a quantidade de colunas
int get_qtd_columns(char line[200]){
  // [TODO] tirar limitação de 200 caracteres
  // Alocação dinâmica resolve isso

  char *piece;
  int quantity = 0;

  line[strlen(line) - 1] = '\0';
  piece = strtok(line, ",");
  quantity++;

  while (piece != NULL) {
    quantity++;    
    piece = strtok(NULL, ",");
  }

  quantity--; 

  return quantity;
}

/// @brief Concatena os nomes das colunas em uma só string, separados por vírgula.
/// @param table a tabela que contem as colunas
/// @return uma string.
char * columns_names_to_csv_string(Table table) {
  // [NOVO] Não tem mais limitação de 200 caracteres
  char * result = malloc(sizeof(char));
  strcpy(result, "");
  unsigned long long result_alloc_size = 0;

  for (int i = 0; i < table.qtd_columns; i++) {
    result_alloc_size += (strlen(table.columns[i].name) + 2) * sizeof(char);
    result = realloc(result, result_alloc_size);
    strcat(result, table.columns[i].name);
    
    if(i == table.qtd_columns - 1) {
      strcat(result, "\n");
    } else {
      strcat(result, ",");
    }
  };

  return result;
}

/// @brief Concatena os typos das colunas em uma só string, separados por vírgula.
/// @param table a tabela que contem as colunas
/// @return uma string.
char * columns_types_to_csv_string(Table table) {
  char * result = malloc(sizeof(char));
  strcpy(result, "");
  unsigned long long result_alloc_size = 0;

  for (int i = 0; i < table.qtd_columns; i++) {
    char * type_name = get_type_name(table.columns[i].type);

    result_alloc_size += (strlen(type_name) + 2) * sizeof(char);
    result = realloc(result, result_alloc_size);
    strcat(result, type_name);

    if(i == table.qtd_columns - 1) {
      strcat(result, "\n");
    } else {
      strcat(result, ",");
    };
  };

  return result;
}

/// @brief Concatena os valores de uma linha em uma só string, separados por vírgula.
/// @param table a tabela que contem a linha
/// @return uma string.
char * columns_values_to_csv_string(Table table, int record_index) {
  char * result = malloc(sizeof(char));
  strcpy(result, "");
  unsigned long long result_alloc_size = 0;

  for (int i = 0; i < table.qtd_columns; i++) {
    result_alloc_size += (strlen(table.records[record_index][i].value) + 2) * sizeof(char);
    result = realloc(result, result_alloc_size);
    strcat(result, table.records[record_index][i].value);

    if(i == table.qtd_columns - 1) {
      strcat(result, "\n");
    } else {
      strcat(result, ",");
    }
  };

  return result;
}

/// @brief Transforma uma string em estilo CSV em várias outras string menores, as quais são 
/// alocadas nos nomes das colunas
/// @param Table a tabela a ser inserida os dados
/// @param line a linha em estilo CSV
/// @return a tabela, com os nomes das colunas de acordo com o CSV
Table csv_string_to_columns_names(Table table, char line[200]) {
  // [TODO] tirar limitação de 200 caracteres
  // Alocação dinâmica resolve isso

  char *piece;
  char aux_line[200];
  strcpy(aux_line, line);
  aux_line[strlen(aux_line) - 1] = '\0';
  int columns_quantity = get_qtd_columns(line), counter = 0;

  table.qtd_columns = columns_quantity;
  free(table.columns);
  table.columns = calloc(columns_quantity, sizeof(Column));

  piece = strtok(aux_line, ",");

  while (piece != NULL) {
    strcpy(table.columns[counter].name, piece);
    counter++;
    piece = strtok(NULL, ",");
  }

  return table;
}

/// @brief Transforma uma string em estilo CSV em várias outras string menores, as quais são 
/// transformadas em "types" e então alocadas nos types das colunas
/// @param Table a tabela a ser inserida os dados
/// @param line a linha em estilo CSV
/// @return a tabela, com os types das colunas de acordo com o CSV
Table csv_string_to_columns_types(Table table, char line[200]) {
  // [TODO] tirar limitação de 200 caracteres
  // Alocação dinâmica resolve isso

  char *piece;
  int counter = 0;
  char aux_line[200];
  strcpy(aux_line, line);

  aux_line[strlen(aux_line) - 1] = '\0';

  piece = strtok(aux_line, ",");

  while (piece != NULL) {
    table.columns[counter].type = get_type_original(piece);
    counter++;
    piece = strtok(NULL, ",");
  }

  return table;
}

/// @brief Transforma uma string em estilo CSV em várias outras string menores, as quais são 
/// transformadas nos values das colunas 
Table csv_string_to_columns_values(Table table, char line[200], int qtd_records_minus_3, bool is_last_line) {
  // [TODO] tirar limitação de 200 caracteres
  // Alocação dinâmica resolve isso

  char *piece;
  char aux_line[200];
  strcpy(aux_line, line);
  aux_line[strlen(aux_line)] = '\0';
  int counter_j = 0;
  int aux_len;

  piece = strtok(aux_line, ",");

  while (piece != NULL) {
    strcpy(table.records[qtd_records_minus_3][counter_j].value, piece);
    counter_j++;
    piece = strtok(NULL, ",");
  }
  if (is_last_line && piece == NULL) {
    aux_len = strlen(table.records[qtd_records_minus_3][counter_j].value);
    table.records[qtd_records_minus_3][counter_j].value[aux_len] = '\0';
  }

  return table;
}
