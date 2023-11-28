#include "tables.h"

// Qualquer outra função envolvendo arquivo além dessas
// são desnecessárias, essas já resolvem tudo
void create_database_folder();
Tables get_tables();
void save_table_file(Table table);
void remove_table_file(Table table);
Table get_data_from_table(Table table);