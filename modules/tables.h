#include <stdbool.h>
#include "utils.h"

typedef struct {
  char type[10];
  char name[50];
  bool is_primary_key;
} Column;

typedef struct {
  char value[200];
} Record;

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
void add_table(Tables * tables, Table table);
Table create_new_table();
void delete_table(int table_index, Tables * tables);
int table_already_exists(Table table, Tables tables);