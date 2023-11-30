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
  } else {
    return -1;
  };
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

/// @brief Retorna o index do registro se existir.
/// @param table a tabela
/// @param primary_key a chave primária do registro
/// @return o index, se existir; -1, caso contrário.
int get_tuple_index(Table table, int primary_key) {
  for(int i = 0; i < table.qtd_records; i++) {
    char str_primary_key[sizeof(primary_key) + 1];
    sprintf(str_primary_key, "%i", primary_key);

    if(strcmp(table.records[i][0].value, str_primary_key) == 0) {
      return i;
    };
  };

  return -1;
}

/// @brief Deleta uma tupla de uma tabela
/// @param table a tabela
/// @param tuple_option chave primária da tupla
/// @return false, se não for possível deletar (ou erro); true, se bem sucedido 
bool delete_tuple(Table * table, int tuple_option) {
  int tuple_index = get_tuple_index(*table, tuple_option);

  if(tuple_index == -1) {
    clear_terminal();
    printf("Nenhum registro encontrado!\n");
    pause_terminal();
    return false;
  };
  
  table -> qtd_records--;
  for(int i = tuple_index; i < table -> qtd_records; i++) {
    table -> records[i] = table -> records[i + 1];
  };

  table -> records = realloc(table -> records, sizeof(Record*) * table -> qtd_records);

  clear_terminal();
  printf("Tupla removida com sucesso!\n");
  pause_terminal();

  return true;
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
  char token[200];
  strcpy(token, line);

  char *piece;
  int quantity = 0;

  trim(strlen(token), token);
  piece = strtok(token, ",");

  while (piece != NULL) {
    quantity++;    
    piece = strtok(NULL, ",");
  };

  return quantity;
}

/// @brief Concatena os nomes das colunas em uma só string, separados por vírgula.
/// @param table a tabela que contem as colunas
/// @return uma string.
char * columns_names_to_csv_string(Table table) {
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
    if (i == table.qtd_columns - 1 && table.qtd_records == 0) {
      break;
    } else if(i == table.qtd_columns - 1) {
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
  unsigned long result_alloc_size = 0;
  
  for (int i = 0; i < table.qtd_columns; i++) {
    result_alloc_size += (strlen(table.records[record_index][i].value) + 2) * sizeof(char);
    result = realloc(result, result_alloc_size);
    strcat(result, table.records[record_index][i].value);

    if(i == table.qtd_columns - 1 && table.qtd_records == record_index + 1) {
      break;
    } else if(i == table.qtd_columns - 1) {
      strcat(result, "\n");
    } else {
      strcat(result, ",");
    }
  };

  return result;
}

/// @brief Transforma uma string no formato CSV em várias outras string menores, 
/// as quais são alocadas nos nomes das colunas
/// @param Table a tabela a ser inserida os dados
/// @param line a linha no formato CSV
/// @return a tabela, com os nomes das colunas de acordo com o CSV.
Table csv_string_to_columns_names(Table table, char line[200]) {
  // [TODO] tirar limitação de 200 caracteres
  // Alocação dinâmica resolve isso

  char *piece;
  char aux_line[200] = "";
  strcpy(aux_line, line);
  trim(strlen(aux_line) + 1, aux_line);

  int counter = 0; 

  table.qtd_columns = get_qtd_columns(line);
  table.columns = calloc(table.qtd_columns, sizeof(Column));

  piece = strtok(aux_line, ",");
  while (piece != NULL) {
    strcpy(table.columns[counter].name, piece);
    counter++;
    piece = strtok(NULL, ",");
  }

  return table;
}

/// @brief Transforma uma string no formato CSV em várias outras string menores, 
/// as quais são transformadas em "types" e então alocadas nos types das colunas.
/// @param Table a tabela a ser inserida os dados
/// @param line a linha no formato CSV
/// @return a tabela, com os types das colunas de acordo com o CSV.
Table csv_string_to_columns_types(Table table, char line[200]) {
  // [TODO] tirar limitação de 200 caracteres
  // Alocação dinâmica resolve isso

  char *piece;
  int counter = 0; 
  char aux_line[200];
  strcpy(aux_line, line);
  trim(strlen(aux_line) + 1, aux_line);
  piece = strtok(aux_line, ",");
  char aux_piece[100];

  while (piece != NULL) {
    table.columns[counter].type = get_type_original(piece);
    counter++;
    strcpy(aux_piece, piece);
    piece = strtok(NULL, ",");
  }

  return table;
}

/// @brief Transforma uma string no formato CSV em várias outras string menores, 
/// as quais são transformadas nos values das colunas.
/// @param table a tabela
/// @param line a string 
/// @param qtd_records o número de registros na tabela
/// @param is_last_line se é a última linha
Table csv_string_to_columns_values(
  Table table, char line[200], 
  int qtd_records, bool is_last_line
) {
  // [TODO] tirar limitação de 200 caracteres
  // Alocação dinâmica resolve isso

  char *piece;
  int counter_j = 0;
  char aux_line[200];
  strcpy(aux_line, line);
  trim(strlen(aux_line) + 1, aux_line);
  piece = strtok(aux_line, ",");

  while(piece != NULL) {
    strcpy(table.records[qtd_records - 1][counter_j].value, piece);
    counter_j++;
    piece = strtok(NULL, ",");
  }

  return table;
}

/// @brief Calcula o tamanho de uma coluna da tabela.
/// @param table a tabela
/// @param column_index o index da coluna
/// @return o tamanho.
int get_column_length(Table table, int column_index) {
  unsigned int length = 0;
  char column[table.qtd_records + 2][200];
  strcpy(column[0], table.columns[column_index].name);
  strcpy(column[1], get_type_name(table.columns[column_index].type));

  for(int i = 0; i < table.qtd_records; i++) {
    strcpy(column[i + 2], table.records[i][column_index].value);
  };

  for(int i = 0; i < table.qtd_records + 2; i++) {
    if(strlen(column[i]) > length) {
      length = strlen(column[i]);
    };
  };

  return length;
}

/// @brief Concatena os nomes das colunas em uma string,
/// separadas por espaços.
/// @param qtd_columns o numero de colunas
/// @param columns_length o vetor de tamanho das colunas
/// @param line_length o tamanho da linha
/// @param table a tabela
/// @return a string formatada.
char * format_table_line_names(
  int qtd_columns, 
  int columns_length[qtd_columns], 
  int line_length, 
  Table table
) {
  char * line = malloc(sizeof(char) * line_length);
  strcpy(line, "");

  for(int i = 0; i < qtd_columns; i++) {
    int gap = i == qtd_columns - 1? 4:3;
    char column[columns_length[i]];
    sprintf(
      column, 
      "%*s%s", -(columns_length[i] - gap), 
      table.columns[i].name,
      i == qtd_columns - 1? "":" | "
    );
    strcat(line, column);
  };
  
  return line;
}

/// @brief Concatena os tipos das colunas em uma string,
/// separadas por espaços.
/// @param qtd_columns o numero de colunas
/// @param columns_length o vetor de tamanho das colunas
/// @param line_length o tamanho da linha
/// @param table a tabela
/// @return a string formatada.
char * format_table_line_types(
  int qtd_columns, 
  int columns_length[qtd_columns], 
  int line_length, 
  Table table
) {
  char * line = malloc(sizeof(char) * line_length);
  strcpy(line, "");

  for(int i = 0; i < qtd_columns; i++) {
    int gap = i == qtd_columns - 1? 4:3;
    char column[columns_length[i]];
    sprintf(
      column, 
      "%*s%s", 
      -(columns_length[i] - gap), 
      get_type_name(table.columns[i].type),
      i == qtd_columns - 1? "":" | "
    );
    strcat(line, column);
  };
  
  return line;
}

/// @brief Concatena os records das colunas em uma string,
/// separadas por espaços.
/// @param qtd_columns o numero de colunas
/// @param columns_length o vetor de tamanho das colunas
/// @param line_length o tamanho da linha
/// @param record_index o index do record
/// @param table a tabela
/// @return a string formatada.
char * format_table_line_record(
  int qtd_columns, 
  int columns_length[qtd_columns], 
  int line_length,
  int record_index,
  Table table
) {
  char * line = malloc(sizeof(char) * line_length);
  strcpy(line, "");

  for(int i = 0; i < qtd_columns; i++) {
    int gap = i == qtd_columns - 1? 4:3;
    char column[columns_length[i]];
    sprintf(
      column, 
      "%*s%s", 
      -(columns_length[i] - gap), 
      table.records[record_index][i].value, 
      i == qtd_columns - 1? "":" | "
    );
    strcat(line, column);
  };
  
  return line;
}

/// @brief Verifica se o valor do record condiz com o tipo dele.
/// @param value o valor
/// @param type o tipo
/// @param error a razão de ser invalido
/// @return true, se for valido; false, caso contrário.
bool validate_record_value(char value[200], types type, char error[200]) {
  char value_to_validate[200];
  strcpy(value_to_validate, value);
  trim(strlen(value_to_validate) + 1, value_to_validate);

  int nat, integer, success;
  double number;
  switch(type) {
    case T_NAT:
      nat = atoi(value_to_validate);
      strcpy(error, "Valor informado não é um número natural!");

      return 
        !include_char(value_to_validate, ',') &&
        !include_char(value_to_validate, '.') &&
        (nat > 0 || strcmp(value_to_validate, "0") == 0);
    case T_INT:
      integer = atoi(value_to_validate);

      strcpy(error, "Valor informado não é um número inteiro!");
      return 
        !include_char(value_to_validate, ',') &&
        !include_char(value_to_validate, '.') &&
        (integer != 0 || strcmp(value_to_validate, "0") == 0);
    case T_FLOAT:
    case T_DOUBLE:
      strcpy(error, "Valor informado não é um número!");
      success = sscanf(value, "%lf", &number);

      if(success == 1 || strcmp(value_to_validate, "0") == 0) {
        //Bonus da função: vai deixar no formato reduzido do double/float
        sprintf(value, "%lg", number);
        return true;
      };

      return false;
    case T_CHAR:
      strcpy(error, "Valor informado possuí mais de um caractere!");
      return strlen(value_to_validate) == 1;
    case T_STRING:
      strcpy(error, "Por razões de segurança, não gostamos de vírgulas!");
      return !include_char(value_to_validate, ',');
    default:
      return true;
  };
}

/// @brief Verifica se a chave primária está em uso.
/// @param value o valor da chave
/// @param table a tabela
/// @return true, se estiver; false, caso contrário.
bool primary_key_already_in_use(char value[200], Table table) {
  for(int i = 0; i < table.qtd_records; i++) {
    if(strcmp(table.records[i][0].value, value) == 0) {
      return true;
    };
  };

  return false;
}