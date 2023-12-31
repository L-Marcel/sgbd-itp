#include "utils.h"

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
  Column *columns;
  int qtd_records;
  Record **records;
} Table;

typedef struct {
  Table *list;
  int size;
} Tables;

char *get_type_name(types type);
types get_type_original(char string[15]);

Tables sort_tables(Tables tables);
void add_table(Tables *tables, Table table);
void delete_table(int table_index, Tables *tables);

Table create_empty_table();
Record *create_empty_record(int qtd_columns);

void add_column(Table *table, Column column);
void add_record(Table *table, Record *record);
void delete_column(Table *table, int column_index);
bool delete_record(Table *table, int record_option);

bool table_already_exists(Table table, Tables tables);
bool column_already_exists(Column column, Table table);
bool validate_record_value(char value[200], types type, char error[200]);
bool primary_key_already_in_use(char value[200], Table table);
int get_record_index(Table table, int primary_key);

char *columns_names_to_csv_string(Table table);
char *columns_types_to_csv_string(Table table);
char *columns_values_to_csv_string(Table table, int record_index);

int get_qtd_columns(char line[200]);
Table csv_string_to_columns_names(Table table, char line[200]);
Table csv_string_to_columns_types(Table table, char line[200]);
Table csv_string_to_columns_values(Table table, char line[200], int qtd_records);

int get_column_length(Table Table, int column_index);
char *format_table_line_names(
  int qtd_columns, int columns_length[qtd_columns], int line_length, Table table);
char *format_table_line_types(
  int qtd_columns, int columns_length[qtd_columns], int line_length, Table table);
char *format_table_line_record(
  int qtd_columns, int columns_length[qtd_columns], int line_length, int record_index, Table table);