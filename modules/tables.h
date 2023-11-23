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

typedef struct {
  char name[50];
  int qtd_columns;
  Column * columns;
  int qtd_records;
  Record ** records;
} Table;

typedef struct {
  Table * tables;
  int size;
} Tables;