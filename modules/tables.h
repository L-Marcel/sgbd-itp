#include <stdbool.h>

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
void add_in_tables(Tables * tables, Table table);
Table createNewTable();
int tableAlreadyExists(Table table, Tables tables);