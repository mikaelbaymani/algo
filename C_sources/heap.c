#include "heap.h"
#include <stdlib.h>

struct _heap{
  int* array;
  size_t size;
  size_t capacity;
  Compare compare;
};

bool MIN(int i1, int i2) { return i1 > i2; }
bool MAX(int i1, int i2) { return i1 < i2; }

heap* Heap(Compare compare, size_t capacity) {
  heap* h = malloc(sizeof *h);
  h->array = malloc(capacity * sizeof(int) );
  h->size = 0;
  h->capacity = capacity;
  h->compare = compare;
  return h;
}

void Delete(heap** h) {
  free((*h)->array);
  free((*h));
  *h = NULL;
}

static void _heapify(heap* h, int index) {
  int parent = (index - 1) / 2;
  if (h->compare(h->array[parent], h->array[index])) {
    h->array[parent] = h->array[parent] ^ h->array[index];
    h->array[index] = h->array[index] ^ h->array[parent];
    h->array[parent] = h->array[parent] ^ h->array[index];
    _heapify(h, parent);
  }
}

void insert(heap* h, int i) {
  if (h->capacity == h->size) {
    h->array = realloc(h->array, 2 * h->capacity * sizeof(int) );
    h->capacity *= 2;
  }
  h->array[h->size] = i;
  _heapify(h, h->size);
  ++h->size;
}

int peek(heap* h, int* i) {
  if (h->size == 0 || i == NULL) {
    return -1;
  }

  *i = h->array[0];
  return 0;
}

static void __heapify(heap* h, int parent) {
  int next = parent;
  int left = parent * 2 + 1;
  int right = parent * 2 + 2;
  if (left >= 0 && left < h->size && h->compare(h->array[next], h->array[left])) {
    next = left;
  }
  if (right >= 0 && right < h->size && h->compare(h->array[next], h->array[right])) {
    next = right;
  }

  if (next != parent) {
    h->array[next] = h->array[next] ^ h->array[parent];
    h->array[parent] = h->array[parent] ^ h->array[next];
    h->array[next] = h->array[next] ^ h->array[parent];
    __heapify(h, next);
  }
}

void pop(heap* h) {
  if (h->size == 0) {
    return ;
  }

  h->array[0] = h->array[h->size-1];
  --h->size;
  __heapify(h, 0);
}

size_t size(heap* h) {
  return h->size;
}

bool empty(heap* h) {
  return h->size == 0;
}

void traverse(heap* h, void (*callback)(int)) {
  int index;
  for (index = 0; index < h->size; ++index) {
    ( callback )(h->array[index]);
  }
}
