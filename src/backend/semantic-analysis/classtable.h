#ifndef CLASSTABLE_H_
#define CLASSTABLE_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ATTRS 5

enum type_t {
  INT,
  BOOLEAN,
  STRING
} type_t;

union Data {
  int i;
  char * str;
} Data;

typedef struct class_node_t {
  class_t * _class;
  struct class_node_t * next;
} class_node_t;

typedef struct class_t {
  char * id;
  int attrAmount;
  char * attr_names[MAX_ATTRS];
  enum type_t attr_types[MAX_ATTRS];
} class_t;

typedef struct object_t {
  class_t * _class;
  union Data values[MAX_ATTRS];
} object_t;

typedef struct object_node_t {
  object_t * object;
  struct object_node_t * next;
} object_node_t;

#endif