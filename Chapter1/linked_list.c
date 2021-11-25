#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct __node_t {
  int __contents;
  struct __node_t *__prev;
  struct __node_t *__next;
};
typedef struct __node_t __node;


struct __list_t {
  size_t __length;
  struct __node_t *__head;
};
typedef struct __list_t List;



__node *__node_create(int value) {
  __node *node = (__node *)malloc(sizeof(__node));
  // TODO: Check if *node == NULL and handle
  node->__contents = value;
  node->__next = NULL;
  node->__prev = NULL;
  return node;
}


void __node_destroy(__node *node) {
  free(node);
  node = NULL;
}


List *list_create() {
  List *list = (List *)malloc(sizeof(List));
  list->__head = NULL;
  list->__length = 0;
  return list;
}


__node *__list_pop_node(List *list) {
  assert(list->__length > 0);
  __node *head_node = list->__head;
  assert(head_node != NULL);
  if (head_node->__next != NULL) {
    list->__head = head_node->__next;
    head_node->__next->__prev = NULL;
  } else {
    list->__head = NULL;
  }
  list->__length--;
  return head_node;
}


void list_destroy(List *list) {
  
  while (list->__length > 0) {
    __node *node = __list_pop_node(list);
    __node_destroy(node);
  }
  free(list);
  list = NULL;
}


bool list_is_empty(List *list) {
  return list->__length == 0;
}


int list_length(List *list) {
  return list->__length;
}


void __insert(__node* prev, __node *next, int position, __node *node) {
  if (!next) {
    assert(position == 0);
    if (prev) {
      prev->__next = node;
      node->__prev = prev;
    }
  } else {
    if (position == 0) {
      if (next->__prev) {
        next->__prev->__next = node;
      }
      next->__prev = node;
      node->__next = next;
    } else {
      return __insert(next, next->__next, position - 1, node);
    }
  }
}


void list_insert(List *list, int position, int value) {
  assert(position <= list->__length);
  __node *node = __node_create(value);
  __insert(NULL, list->__head, position, node);
  if (position == 0) {
    list->__head = node;
  }
  list->__length++;
}


int main(int argc, char **argv) {
  List *list = list_create();
  assert(list_is_empty(list));

  list_insert(list, 0, 1);
  assert(!list_is_empty(list));
  assert(list_length(list) == 1);

  list_insert(list, 0, 2);
  assert(!list_is_empty(list));
  assert(list_length(list) == 2);
  assert(list->__head->__contents == 2);
  assert(list->__head->__next->__contents == 1);
  
  list_destroy(list);

  list = list_create();
  assert(list_is_empty(list));

  list_insert(list, 0, 1);
  assert(!list_is_empty(list));
  assert(list_length(list) == 1);

  list_insert(list, 1, 2);
  assert(!list_is_empty(list));
  assert(list_length(list) == 2);
  assert(list->__head->__contents == 1);
  assert(list->__head->__next->__contents == 2);

}
