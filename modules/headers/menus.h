#include "prints.h"

int get_nat_option();
int get_nat_or_cancel_option();
int is_option_valid(int option, int qtd_menu_options);
int display_default_menu();
int display_tables_menu(Tables tables, char complement[26]);
int display_procedures_menu(Table table);
int display_new_table_procedure_menu(Table table);
int display_select_types_menu();
int display_select_column_menu(Table table, char complement[26], bool include_primary_key);
int display_delete_record_procedure_menu(Table table);
order display_search_options_menu(Table table, int column_option);