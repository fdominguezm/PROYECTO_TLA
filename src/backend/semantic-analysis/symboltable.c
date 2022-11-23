#include <symboltable.h>


int addSymbol(char * name, enum type_t type, union Data value) {
  if (symbol_list == NULL) {
    symbol_node_t * new_symbol = malloc(sizeof(symbol_node_t));

    new_symbol->id = calloc(strlen(name) + 1, 0);
    strcpy(new_symbol->id, name);
    new_symbol->type = type;
    new_symbol->value = value;
    new_symbol->next = NULL;
    return 1;
  }

  symbol_node_t * current_node = symbol_list;

  while (current_node->next != NULL) {
    if (strcmp(name, current_node->id) == 0) {
      printf("Symbol identifier %s already in use.\n", name);
      return -1;
    }
    current_node = current_node->next;
  }

  symbol_node_t * new_symbol = malloc(sizeof(symbol_node_t));

  new_symbol->id = calloc(strlen(name) + 1, 0);
  strcpy(new_symbol->id, name);
  new_symbol->type = type;
  new_symbol->value = value;
  new_symbol->next = NULL;
  
  current_node->next = new_symbol;

  return 1;
}

int removeSymbol(char * name) {
  if (symbol_list == NULL) {
    return -1;
  }

  symbol_node_t * current_node = symbol_list;
  while (current_node->next != NULL) {
    if (strcmp(current_node->id, name) == 0) {
      symbol_node_t * aux = current_node->next->next;
      current_node->next = aux;
      return 1;
    }
  }
  return -1;
}

symbol_node_t * getSymbolValue(char * name) {  
  if (symbol_list == NULL) {
    return NULL;
  }

  symbol_node_t * current_node = symbol_list;

  while(current_node->next != NULL) {
    if (strcmp(current_node->id, name) == 0) {
      return current_node;
    }
  }
  return -1;
}