typedef enum {
  true = 1,
  false = 0
} bool;

typedef enum {
  T_NAT,
  T_INT,
  T_FLOAT,
  T_DOUBLE,
  T_CHAR,
  T_STRING
} types;

typedef enum {
  EQ = 0,    // Equal
  LTE = -1,  // Less than or equal
  LT = -2,   // Less than
  GTE = 1,   // Greater than or equal
  GT = 2     // Greater than
} order;