#include "tables.h"

void create_database_folder();
Tables get_tables();

// [NOVO] Vai ser mudado para salvar de uma vez só, depois.
void save_new_table_file(Table table);
//void save_tuple_on_table_file();
//void save_table_file(Table table);
//

void remove_table_file(Table table);

// [NOVO]
Table get_data_from_table(Table table);
//