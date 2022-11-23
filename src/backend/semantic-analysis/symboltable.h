#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NULL (void *) 0

enum type_t {
  INT,
  BOOLEAN,
  STRING
} type_t;

union Data {
  int i;
  char * str;
} Data;

typedef struct symbol_t {
  char * id;
  enum type_t type;
  int initialized;
  union Data value;
} symbol_t;

typedef struct symbol_node_t {
  symbol_t symbol;
  struct node_t * next;
} symbol_node_t;

symbol_node_t * symbol_list;

int addSymbol(char * name, enum type_t type, union Data value);
int removeSymbol(char * name);
symbol_t * getSymbolNode(char * name);

#endif