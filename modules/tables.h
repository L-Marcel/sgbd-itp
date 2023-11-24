#include <stdbool.h>

typedef struct {
  char type[10];
  char name[50];
  bool primary;
} Column;

typedef struct {
  Column column;
  char value[200];
} Record;

// Considerando que o usuário pode criar a table como quiser, os atributos da Table deveriam ser mutáveis, não? 

// Na real que depende. Não sei se entendi, dá pra fazer uma table padrão com todos os types primitivos, ou uma mutável que seria de acordo com o que o usuário inserisse. Aí teríamos que criar um arquivo com C pra ser a Table

// Atualiza: Não tô preocupado com isso agora, tava vendo outras coisas.
typedef struct {
  char name[50];
  int qtd_columns;
  Column * columns;
  int qtd_records;
  Record ** records;
} Table;

typedef struct {
  Table * list;
  int size;
} Tables;

Tables sort_tables(Tables tables);
Table create_table();