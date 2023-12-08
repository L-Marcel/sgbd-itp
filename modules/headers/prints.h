#include "files.h"

void print_tables(Tables tables, int start);
void print_table(Table table, char turples_message[50]);
void print_divisor(char title[53], int utf8_chars);
void print_columns(Table table, int start, bool include_primary_key);
void print_table_divisor(int line_length);