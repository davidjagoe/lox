
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


node* new_node() {
  node* n = (node*)malloc(sizeof(node));
  n->prev = 0; n->next = 0; n->contents = 0;
  return n;
}


void del_node(node* n) {
  free(n);
}


list* new_list() {
  list* l = (list*)malloc(sizeof(list));
  l->count = 0; l->head = 0;
  return l;
}


void del_list(list* l) {
  for (int i = 0; i < l->count; i++) {
    node* n = l->head;
    l->head = n->next;
    del_node(n);
  }
  free(l);
}


void push(list* l, char* element) {
  node* n = new_node();
  n->contents = element;
  n->next = l->head;
  l->count++;
  l->head = n;
}


void pop(list* l, char* output) {
  node* n = l->head;
  l->head = n->next;
  strcpy(output, n->contents);
  del_node(n);
  l->count--;
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
  push(l, "One");
  push(l, "Two");
  push(l, "Three");
  push(l, "Four");
  print_list(l);

  char* value = malloc(10); // What if I don't know how long the string will be???
  pop(l, value);
  printf("%lu\n", strlen(value));
  
  printf("%s\n", value);
  free(value);
  
  print_list(l);
  
  del_list(l);
}
