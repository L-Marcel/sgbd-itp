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
  EQ,  
  GT,
  GTE,
  LT, 
  LTE,    
  NT     
} order;