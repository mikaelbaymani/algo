#include <stdlib.h>
#include "Deque.h"

struct node{
  struct node* next,* prev;
  int value;
};

typedef struct node node;

struct deque{
  node* head,* tail;
  size_t size;
};

deque* Deque() {
  deque* obj = malloc(sizeof *obj);
  obj->head = obj->tail = NULL;
  obj->size = 0;
  return obj;
}

void DequeDestructor(deque** obj) {
  while (!empty(*obj)) {
    pop_front(*obj);
  }
  free(*obj);
  *obj = NULL;
}

node* _push_front(node** h, node** t, node* n) {
  n->prev = NULL;

  n->next = *h;

  if (*h) {
    (*h)->prev = n;
  }

  if (*t == NULL) {
    *t = n;
  }

  return *h = n;
}


node* _push_back(node** h, node** t, node* n) {
  n->next = NULL;

  n->prev = *t;

  if (*t) {
    (*t)->next = n;
  }

  if (*h == NULL) {
    *h = n;
  }

  return *t = n;
}

void push_front(deque* obj, int value) {
  node* n = malloc(sizeof *n);
  n->value = value;
  _push_front(&obj->head, &obj->tail, n);
  obj->size++;
}

void push_back(deque* obj, int value) {
 node* n = malloc(sizeof *n);
  n->value = value;
  _push_back(&obj->head, &obj->tail, n);
  obj->size++;
}

node* delete(node** h, node** t, node* n) {
  if (*h == n) {
    *h = n->next;
  }

  if (*t == n) {
    *t = n->prev;
  }

  if (n->next) {
    n->next->prev = n->prev;
  }

  if (n->prev) {
    n->prev->next = n->next;
  }

  return n;
}

void pop_front(deque* obj) {
  free( delete(&obj->head, &obj->tail, obj->head) );
  obj->size--;
}

void pop_back(deque* obj) {
  free( delete(&obj->head, &obj->tail, obj->tail) );
  obj->size--;
}

int front(deque* obj) {
  return obj->head->value;
}

int back(deque* obj) {
  return obj->tail->value;
}

bool empty(deque* obj) {
  return obj->size == 0;
}

void traverse(deque* obj, void (*callback)(int)) {
  node* cur;
  node* n = obj->head;
  while (n) {
    cur = n;
    n = n->next;
    callback(cur->value);
  }
}
