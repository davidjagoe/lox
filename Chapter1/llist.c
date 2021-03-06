#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
  char *content;
  struct node *next;
};

typedef struct node node_t;
typedef node_t **list_t;


list_t list_create() {
  list_t list = malloc(sizeof(node_t *));
  *list = NULL; // Originally leaving this out caused me some hard-to-find problems.
  return list;
}


void node_destroy(node_t *node) {
  free(node->content);
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
  free(list);
  list = NULL;
}


node_t *node_create(char *value) {
  char *val = malloc(strlen(value) * sizeof(char));
  strcpy(val, value);
  node_t *node = malloc(sizeof(node_t));
  node->content = val;
  return node;
}


int list_insert(list_t list, uint position, char *value) {
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


char *get_item(list_t list, uint position) {
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
  return list_length(list) == 0;
}


void test_create_empty_list() {
  list_t empty = list_create();
  assert(is_empty(empty));
  assert(list_length(empty) == 0);
  list_destroy(empty);
}


void test_insert_first_element() {
  list_t list = list_create();
  list_insert(list, 0, "1");
  assert(strcmp((*list)->content, "1") == 0);
  assert(list_length(list) == 1);
  list_destroy(list);
}


void test_insert_multiple_elements_front() {
  list_t list = list_create();
  list_insert(list, 0, "1");
  list_insert(list, 0, "2");
  list_insert(list, 0, "3");
  assert(strcmp((*list)->content, "3") == 0);
  assert(strcmp((*list)->next->content, "2") == 0);
  assert(strcmp((*list)->next->next->content, "1") == 0);
  assert(list_length(list) == 3);
  list_destroy(list);
}


void test_insert_multiple_elements_back() {
  list_t list = list_create();
  list_insert(list, 0, "1");
  list_insert(list, 1, "2");
  list_insert(list, 2, "3");
  assert(strcmp((*list)->content, "1") == 0);
  assert(strcmp((*list)->next->content, "2") == 0);
  assert(strcmp((*list)->next->next->content, "3") == 0);
  assert(list_length(list) == 3);
  list_destroy(list);
}


void test_insert_elements_mid() {
  list_t list = list_create();
  list_insert(list, 0, "1");
  list_insert(list, 1, "2");
  list_insert(list, 2, "4");
  list_insert(list, 3, "5");
  list_insert(list, 2, "3");
  assert(strcmp((*list)->content, "1") == 0);
  assert(strcmp((*list)->next->content, "2") == 0);
  assert(strcmp((*list)->next->next->content, "3") == 0);
  assert(strcmp((*list)->next->next->next->content, "4") == 0);
  assert(strcmp((*list)->next->next->next->next->content, "5") == 0);
  assert(list_length(list) == 5);
  list_destroy(list);
}


void test_remove_single_element() {
  list_t list = list_create();
  list_insert(list, 0, "1");
  list_remove(list, 0);
  assert(is_empty(list));
  list_destroy(list);
}


void test_get_item() {
  list_t list = list_create();
  list_insert(list, 0, "1");
  list_insert(list, 1, "2");
  list_insert(list, 2, "3");
  assert(strcmp(get_item(list, 0), "1") == 0);
  assert(strcmp(get_item(list, 1), "2") == 0);
  assert(strcmp(get_item(list, 2), "3") == 0);
  list_destroy(list);
}


void test_remove_multiple_element() {
  list_t list = list_create();
  list_insert(list, 0, "1");
  list_insert(list, 1, "2");
  list_insert(list, 2, "3");
  list_insert(list, 3, "4");
  list_insert(list, 4, "5");
  list_remove(list, 2);
  list_remove(list, 2);
  assert(strcmp(get_item(list, 2), "5") == 0);
  assert(list_length(list) == 3);
  list_destroy(list);
}


int main(int argc, char **argv) {
  test_create_empty_list();
  test_insert_first_element();
  test_insert_multiple_elements_front();
  test_insert_multiple_elements_back();
  test_insert_elements_mid();
  test_remove_single_element();
  test_remove_single_element();
  test_get_item();
  test_remove_multiple_element();
  return 0;
}
