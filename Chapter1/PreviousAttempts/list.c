
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node_t {
  struct node_t* prev;
  struct node_t* next;
  char* contents;
} node;


typedef struct list_t {
  int count;
  node* head;
} list;


node* _new_node() {
  node* n = (node*)malloc(sizeof(node));
  n->prev = NULL; n->next = NULL; n->contents = NULL;
  return n;
}


void _del_node(node* n) {
  free(n);
}


list* new_list() {
  list* l = (list*)malloc(sizeof(list));
  l->count = 0; l->head = NULL;
  return l;
}


void del_list(list* l) {
  for (int i = 0; i < l->count; i++) {
    node* n = l->head;
    l->head = n->next;
    _del_node(n);
  }
  free(l);
}


node* push(list* _list, char* element) {
  node* _node = _new_node();
  _node->contents = element;
  _node->next = _list->head;
  if (_list->count > 0) {
    _node->next->prev = _node;
  }
  _list->count++;
  _list->head = _node;
  return _node;
}


void pop(list* _list, char* output) {
  node* _node = _list->head;
  _node->next->prev = NULL;
  _list->head = _node->next;
  strcpy(output, _node->contents);
  _del_node(_node);
  _list->count--;
}


node* head(list* _list) {
  return _list->head;
}


list* tail(list* _list) {
  list* _new = new_list();
  _new->count = _list->count - 1;
  _new->head = _list->head->next;
  return _new;
}


void _insert_item(node* hd, list* tl, char* item, int location) {
  node* new_item;
  if (location == 1) {
    new_item = push(tl, item);
    hd->next = new_item;
    new_item->prev = hd;
  }
  for (int i = 0; i < location; i++) {
    _insert_item(head(tl), tail(tl), item, location - 1);
  }
}


void insert_item(list* _list, char* item, int location) {
  if (location > _list->count) {
    return;
  }
  
  if (location == 0) {
    push(_list, item);
  }
  
  else {
    _insert_item(head(_list), tail(_list), item, location);
  }
}


void remove_item(list* _list, int location) {

}



void print_list(list* l) {
  int len = l->count;
  node* n;
  if (len == 0) {
    printf("%s\n", "<Empty List>");
  }
  else {
    n = l->head;
    printf("[");
    for (int i = 0; i < len; i++) {
      printf("%s,", n->contents);
      n = n->next;
    }
    printf("]\n");
  }
}


int main(int argc, char** argv) {
  list* l = new_list();
  print_list(l);
  insert_item(l, "One", 0);
  print_list(l);
  insert_item(l, "Two", 1);
  print_list(l);
  /* push(l, "One"); */
  /* push(l, "Two"); */
  /* push(l, "Three"); */
  /* push(l, "Four"); */
  /* print_list(l); */

  /* char* value = malloc(10); // What if I don't know how long the string will be??? */
  /* pop(l, value); */
  /* printf("%lu\n", strlen(value)); */
  
  /* printf("%s\n", value); */
  /* free(value); */
  
  /* print_list(l); */
  
  del_list(l);
}
