#include "set.h"
#include <stdlib.h>
typedef struct node{
  struct node* next,* prev;
  int64_t value;
}node;

struct set{
  node** slots;
  int capacity;
};

set* Set(int capacity) {
  set* obj = malloc(sizeof *obj);
  obj->slots = calloc(capacity, sizeof(node*) );
  obj->capacity = capacity;
  return obj;
}

void Setdestructor(set** obj) {
  traverse(*obj, erase);
  free((*obj)->slots);
  free(*obj);
  *obj = NULL;
}

static node* push(node** h, node* n) {
  n->prev = NULL, n->next = *h;
  if (*h)
    (*h)->prev = n;
  return *h = n;
}

static node* del(node** h, node* n) {
  if (*h == n)
    *h = n->next;
  if (n->next)
    n->next->prev = n->prev;
  if (n->prev)
    n->prev->next = n->next;
  return n;
}

static unsigned int hash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

int insert(set* obj, int64_t value) {
  unsigned i = hash(value) % obj->capacity;
  node* n = obj->slots[i];

  while (n && n->value != value)
    n = n->next;
  if (n == NULL) {
    n = malloc(sizeof *n);
    n->value = value;
    push(&obj->slots[i], n);
  }

  return !n;
}

bool contains(set* obj, int64_t value) {
  unsigned i = hash(value) % obj->capacity;
  node* n = obj->slots[i];

  while (n && n->value != value)
    n = n->next;

  return n? true: false;
}

void erase(set* obj, int64_t value) {
  unsigned i = hash(value) % obj->capacity;
  node* n = obj->slots[i];

  while (n && n->value != value)
    n = n->next;
  if (n != NULL)
    free( del(&obj->slots[i], n) );
}

void traverse(set* obj, void (*callback)(set*, int64_t)) {
  node* cur,* n;
  for (int i = 0; i < obj->capacity; ++i) {
    n = obj->slots[i];
    while (n) {
      cur = n;
      n = n->next;
      callback(obj, cur->value);
    }
  }
}
