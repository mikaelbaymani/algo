#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Design and implement a data structure for Least Recently Used (LRU) cache. It
// should support the following operations: get and put.
//
// get(key) - Get the value (will always be positive) of the key if the key
// exists in the cache, otherwise return -1.
//
// put(key, value) - Set or insert the value if the key is not already present.
// When the cache reached its capacity, it should invalidate the least recently
// used item before inserting a new item.
//
// Follow up:
// Could you do both operations in O(1) time complexity?
typedef struct element{
  struct element* next,* prev;
  int key, value;
} element;

//// DEQUE ////
typedef struct {
  element* head,* tail;
  size_t size;
} deque;

deque* Deque() {
  deque* obj = malloc(sizeof *obj);
  obj->head = obj->tail = NULL;
  obj->size = 0;
  return obj;
}

element* _push_front(element** h, element** t, element* e) {
  e->prev = NULL, e->next = *h;

  if (*h)
    (*h)->prev = e;

  if (*t == NULL)
    *t = e;

  return *h = e;
}

element* _push_back(element** h, element** t, element* e) {
  e->next = NULL, e->prev = *t;

  if (*t)
    (*t)->next = e;

  if (*h == NULL)
    *h = e;

  return *t = e;
}

element* push_front(deque* obj, element* elm) {
  obj->size++;
  return _push_front(&obj->head, &obj->tail, elm);
}

element* push_back(deque* obj, element* elm) {
  obj->size++;
  return _push_back(&obj->head, &obj->tail, elm);
}

element* _delete(element** h, element** t, element* e) {
  if (*h == e)
    *h = e->next;

  if (*t == e)
    *t = e->prev;

  if (e->next)
    e->next->prev = e->prev;

  if (e->prev)
    e->prev->next = e->next;

  return e;
}

element* delete(deque* obj, element* elm) {
  obj->size--;
  return _delete(&obj->head, &obj->tail, elm);
}

element* pop_front(deque* obj) {
  return delete(obj, obj->head);
}

element* pop_back(deque* obj) {
  return delete(obj, obj->tail);
}

bool empty(deque* obj) {
  return obj->size == 0;
}

void traverse(deque* obj, void (*callback)(deque*, element*)) {
  element* cur,* elm = obj->head;
  while (elm) {
    cur = elm;
    elm = elm->next;
    callback(obj, cur);
  }
}

void DequeDestructor(deque** obj, bool shallow) {
  element* elm;
  while (!empty(*obj)) {
    elm = pop_front(*obj);
    if (!shallow)
      free (elm);
  }
  free (*obj);
  *obj = NULL;
}

//// MAP ////
typedef struct node {
  struct node* next;
  int key;
  element* elm;
} node;

typedef struct map {
  node** buckets;
  int capacity;
} map;

map* Map(int capacity) {
  map* obj = malloc(sizeof *obj);
  obj->buckets = calloc(capacity, sizeof(node*) );
  obj->capacity = capacity;
  return obj;
}

unsigned int hash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

void insert(map* obj, int key, element* elm) {
  unsigned i = hash(key) % obj->capacity;
  node* n = obj->buckets[i];

  while (n) {
    if (n->key == key)
      break;
    n = n->next;
  }
  if (n) {
    n->elm = elm;
  }
  else {
    n = malloc(sizeof *n);
    n->key = key, n->elm = elm;
    n->next = obj->buckets[i];
    obj->buckets[i] = n;
  }
}

element* search(map* obj, int key) {
  unsigned i = hash(key) % obj->capacity;
  node* n = obj->buckets[i];

  while (n) {
    if (n->key == key)
      return n->elm;
    n = n->next;
  }
  return NULL;
}

void discard(map* obj, int key) {
  unsigned i = hash(key) % obj->capacity;
  node* prev = NULL, * cur = obj->buckets[i];

  while (cur) {
    if (cur->key == key) {
      if (prev)
        prev->next = cur->next;
      if (obj->buckets[i] == cur)
        obj->buckets[i] = cur->next;
      free(cur);
      cur = NULL;
      break;
    }
    prev = cur;
    cur = cur->next;
  }
}

void walkthrough(map* obj, void (*callback)(map*, int)) {
  node* n,* cur;
  for (int i = 0; i < obj->capacity; ++i) {
    n = obj->buckets[i];
    while (n) {
      cur = n;
      n = n->next;
      callback(obj, cur->key);
    }
  }
}

void MapDestructor(map** obj) {
  walkthrough(*obj, discard);
  free((*obj)->buckets);
  free(*obj);
  *obj = NULL;
}

//// LRUCache ////
typedef struct {
  deque* q;
  map* m;
  int capacity;
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
  LRUCache* obj = malloc(sizeof *obj);
  obj->q = Deque();
  obj->m = Map(2*capacity);
  obj->capacity = capacity;
  return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
  element* elm = search(obj->m, key);
  if (elm == NULL) {
    return -1;
  }
  delete(obj->q, elm);
  push_front(obj->q, elm);
  return elm->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
  element* elm = search(obj->m, key);
  if (elm == NULL) {
    if (obj->q->size == obj->capacity) {
      elm = pop_back(obj->q);
      discard(obj->m, elm->key);
      elm->key = key, elm->value = value;
      push_front(obj->q, elm);
      insert(obj->m, key, elm);
    }
    else {
      elm = malloc(sizeof *elm);
      elm->key = key, elm->value = value;
      push_front(obj->q, elm);
      insert(obj->m, key, elm);
    }
  }
  else {
    elm = delete(obj->q, elm);
    elm->value = value;
    push_front(obj->q, elm);
  }
}

void lRUCacheFree(LRUCache* obj) {
  MapDestructor(&obj->m);
  DequeDestructor(&obj->q, false);
  free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
 */



int main(int argc, char* argv[]) {
  LRUCache* obj = lRUCacheCreate(2);
  lRUCachePut(obj, 1, 1);
  lRUCachePut(obj, 2, 2);
  printf("returns %d\n", lRUCacheGet(obj, 1));
  lRUCachePut(obj, 3, 3); // evicts key 2
  printf("returns %d\n", lRUCacheGet(obj, 2));
  lRUCachePut(obj, 4, 4); // evicts key 1
  printf("returns %d\n", lRUCacheGet(obj, 1));
  printf("returns %d\n", lRUCacheGet(obj, 3));
  printf("returns %d\n", lRUCacheGet(obj, 4));

  lRUCacheFree(obj);
  return 0;
}
