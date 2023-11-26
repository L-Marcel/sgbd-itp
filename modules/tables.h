#include "utils.h"

typedef enum {
  T_NAT,
  T_INT,
  T_FLOAT,
  T_DOUBLE,
  T_CHAR,
  T_STRING
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

char* get_type_name(types type);
Tables sort_tables(Tables tables);
void add_table(Tables * tables, Table table);
void delete_table(int table_index, Tables * tables);
Table create_empty_table();
void add_column(Table * table, Column column);
void delete_column(Table * table, int column_index);
bool table_already_exists(Table table, Tables tables);
bool column_already_exists(Column column, Table table);
void columns_names_to_csv_string(Table table, char line[200]);
void columns_types_to_csv_string(Table table, char line[200]);
//void columns_values_to_csv_string(Table table, char line[200]);