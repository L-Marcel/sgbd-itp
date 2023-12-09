#include "procedures.h"

void search_main_caller(Table table, int column_option, order search_option);
int number_is_equal_less_or_greater(double user_number);
char *get_order_name(order ord);
order compare(char value_one[200], char value_two[200], types type);
Table filter_table(Table table, int column_option, char value[200], order filter_order);