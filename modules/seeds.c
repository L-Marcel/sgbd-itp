#include "headers/core.h"
#include <stdio.h>
#include <stdlib.h>

void seed_users() {
  Table table = create_empty_table();

  // Aviso: recorri a IA (Github Copilot) para gerar
  // os valores da tabela a ser preenchida!

  // Não foi utilizada IA em nenhum outro trecho
  // do código, e essa parte é mais dedicada a
  // fins de testes.

  Column columns[6] = {
    {
      .is_primary_key = true, 
      .name = "Id", 
      .type = T_NAT
    },
    {
      .is_primary_key = false,
      .name = "Nome",
      .type = T_STRING,
    },
    {
      .is_primary_key = false,
      .name = "Idade",
      .type = T_NAT,
    },
    {
      .is_primary_key = false,
      .name = "Altura",
      .type = T_FLOAT,
    },
    {
      .is_primary_key = false,
      .name = "Peso",
      .type = T_FLOAT,
    },
    {
      .is_primary_key = false,
      .name = "Sexo",
      .type = T_CHAR,
    }
  };
  
  Record records[9][6] = {
    {{.value = "1"}, {.value = "Joao"}, {.value = "20"}, {.value = "1.80"}, {.value = "80.00"}, {.value = "M"}},
    {{.value = "2"}, {.value = "Maria"}, {.value = "25"}, {.value = "1.60"}, {.value = "60.00"}, {.value = "F"}},
    {{.value = "3"}, {.value = "Jose"}, {.value = "30"}, {.value = "1.70"}, {.value = "70.00"}, {.value = "M"}},
    {{.value = "4"}, {.value = "Ana"}, {.value = "35"}, {.value = "1.65"}, {.value = "65.00"}, {.value = "F"}},
    {{.value = "5"}, {.value = "Pedro"}, {.value = "40"}, {.value = "1.75"}, {.value = "75.00"}, {.value = "M"}},
    {{.value = "6"}, {.value = "Carla"}, {.value = "45"}, {.value = "1.55"}, {.value = "55.00"}, {.value = "F"}},
    {{.value = "7"}, {.value = "Paulo"}, {.value = "50"}, {.value = "1.85"}, {.value = "85.00"}, {.value = "M"}},
    {{.value = "8"}, {.value = "Julia"}, {.value = "55"}, {.value = "1.75"}, {.value = "75.00"}, {.value = "F"}},
    {{.value = "9"}, {.value = "Marcos"}, {.value = "60"}, {.value = "1.65"}, {.value = "65.00"}, {.value = "M"}}
  };

  table.qtd_columns = 6, table.qtd_records = 9, strcpy(table.name, "Usuarios");
  table.columns = realloc(table.columns, sizeof(Column) * table.qtd_columns);
  table.columns = columns;

  table.records = realloc(table.records, sizeof(Record *) * table.qtd_records);
  for (int i = 0; i < table.qtd_records; i++) {
    table.records[i] = records[i];
  };

  save_table_file(table);
  clear_terminal();
  printf("Tabela \"Usuarios\" criada/sobrescrevida!\nExecute \"make run\" para conseguir "
         "acessá-la!\n");
}