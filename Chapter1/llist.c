#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// int MAXLEN = pow(2, sizeof(uint) * 8) - 1; // How to do this at comptime?

typedef int item;

struct node {
  item content;
  struct node *next;
};

typedef struct node node_t;
typedef node_t **list_t;


list_t list_create() {
  list_t list = malloc(sizeof(node_t *));
  return list;
}


void node_destroy(node_t *node) {
  node->next = NULL;
  free(node);
  node = NULL;
}


void list_destroy(list_t list) {
  node_t *head = *list;
  node_t *next;
  while (head) {
    next = head->next;
    node_destroy(head);
    head = next;
  }
  free(*list);
  list = NULL;
}


node_t *node_create(item value) {
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


void list_remove(list_t list, uint position) {
  node_t *prev = NULL;
  node_t *node = *list;

  for (int i = 0; i < position; i++) {
    prev = node;
    node = node->next;
  }

  if (prev) {
    prev->next = node->next;
  }

  if (position == 0) {
    *list = node->next;
  }
  
  node_destroy(node);

}


item get_item(list_t list, uint position) {
  node_t *head = *list;
  for (int i = 0; i < position; i++) {
    head = head->next;
  }
  return head->content;
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
  list_destroy(empty);
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


void test_insert_multiple_elements_back() {
  list_t list = list_create();
  list_insert(list, 0, 1);
  list_insert(list, 1, 2);
  list_insert(list, 2, 3);
  assert((*list)->content == 1);
  assert((*list)->next->content == 2);
  assert((*list)->next->next->content == 3);
  assert(list_length(list) == 3);
}


void test_insert_elements_mid() {
  list_t list = list_create();
  list_insert(list, 0, 1);
  list_insert(list, 1, 2);
  list_insert(list, 2, 4);
  list_insert(list, 3, 5);
  list_insert(list, 2, 3);
  assert((*list)->content == 1);
  assert((*list)->next->content == 2);
  assert((*list)->next->next->content == 3);
  assert((*list)->next->next->next->content == 4);
  assert((*list)->next->next->next->next->content == 5);
  assert(list_length(list) == 5);
}


void test_remove_single_element() {
  list_t list = list_create();
  list_insert(list, 0, 1);
  list_remove(list, 0);
  assert(is_empty(list));
}


void test_remove_multiple_element() {
  /* list_t l = list_create(); */
  /* list_t li = list_create(); */
  /* list_t lis = list_create(); */
  list_t list = list_create();
  list_insert(list, 0, 1);
  list_remove(list, 0);
  assert(is_empty(list));
}


void test_get_item() {
  list_t list = list_create();
  list_insert(list, 0, 1);
  list_insert(list, 1, 2);
  list_insert(list, 2, 3);
  assert(get_item(list, 0) == 1);
  assert(get_item(list, 1) == 2);
  assert(get_item(list, 2) == 3);
}


int main(int argc, char **argv) {
  test_create_empty_list();
  test_insert_first_element();
  test_insert_multiple_elements_front();
  test_insert_multiple_elements_back();
  test_insert_elements_mid();
  test_remove_single_element();
  test_remove_multiple_element();
  test_get_item();
  return 0;
}
