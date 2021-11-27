#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// int MAXLEN = pow(2, sizeof(uint) * 8) - 1; // How to do this at comptime?


struct node {
  int content;
  struct node *next;
};

typedef struct node node_t;
typedef node_t **list_t;


list_t list_create() {
  list_t list = malloc(sizeof(node_t *));
  return list;
}


/* void list_destroy(node_t **list) { */
/*   // HOLD for freeing nodes. */
/*   /\* free(list); *\/ */
/* } */


node_t *node_create(int value) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->content = value;
  return node;
}


int list_insert(list_t list, uint position, int value) {
  node_t *new = node_create(value);
  node_t *before = NULL;
  node_t *after = *list;

  for (int i = 0; i < position; i++) {
    before = after;
    after = after->next;
  }

  new->next = after;
  if (before) {
    before->next = new;
  }

  if (position == 0) {
    *list = new;
  }
  
  return -1;
}


uint list_length(list_t list) {
  uint length = 0;
  node_t *head = *list;
  while (head) {
    head = head->next;
    length++;
  }
  return length;
}


bool is_empty(list_t list) {
  return *list == NULL;
}


void test_create_empty_list() {
  list_t empty = list_create();
  assert(is_empty(empty));
  assert(list_length(empty) == 0);
}


void test_insert_first_element() {
  list_t list = list_create();
  list_insert(list, 0, 1);
  assert((*list)->content == 1);
  assert(list_length(list) == 1);
}


void test_insert_multiple_elements_front() {
  list_t list = list_create();
  list_insert(list, 0, 1);
  list_insert(list, 0, 2);
  list_insert(list, 0, 3);
  assert((*list)->content == 3);
  assert((*list)->next->content == 2);
  assert((*list)->next->next->content == 1);
  assert(list_length(list) == 3);
}


int main(int argc, char **argv) {
  test_create_empty_list();
  test_insert_first_element();
  test_insert_multiple_elements_front();
  return 0;
}
