#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// int MAXLEN = pow(2, sizeof(uint) * 8) - 1; // How to do this at comptime?


struct node_t {
  int content;
  struct node_t *next;
  /* struct node_t *prev; */
};

typedef struct node_t node;
typedef struct node_t list;


node *node_create(int content) {
  node *n = (node *)malloc(sizeof(node));
  n->content = content;
  n->next = NULL;
  return n;
}

node *list_create() {
  return node_create(0);
}


void list_destroy(node *list) {
  // HOLD for freeing nodes.
  free(list);
}


node *list_insert(node *list, uint index, int value) {
  node *before = NULL;
  node *new = node_create(value);
  node *after = list;
  /* for (int i = 0; i < index; i++) { */
    
  /* } */
  if (before != NULL) {
    before->next = new;
  }
  new->next = after;
  return new;
}


uint list_length(node *list) {
  uint length = 0;
  node* iter = list;
  while (iter->next) {
    iter = iter->next;
    length++;
  }
  return length;
}


void test_create_empty_list() {
  list *empty = list_create();
  assert(list_length(empty) == 0);
}


void test_insert_element() {
  list *l = list_create();
  l = list_insert(l, 0, 1);
  assert(list_length(l) == 1);
}


int main(int argc, char **argv) {
  test_create_empty_list();
  test_insert_element();
  return 0;
}
