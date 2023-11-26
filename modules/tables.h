#include "utils.h"

typedef enum {
  T_NAT,
  T_INT,
  T_STRING,
  T_CHAR,
  T_FLOAT,
  T_DOUBLE
} types;

typedef struct {
  types type;
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
Table create_empty_table();
void add_column(Table table, Column column);
void delete_table(int table_index, Tables * tables);
bool table_already_exists(Table table, Tables tables);