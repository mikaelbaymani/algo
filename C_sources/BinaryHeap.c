#include <stdlib.h>
#include "BinaryHeap.h"

struct heap {
  int* array;
  int size;
  int capacity;
  Compare compare;
};

bool Min(int v1, int v2) { return v1 < v2; }
bool Max(int v1, int v2) { return v1 > v2; }

heap* BinaryHeap(int initial_capacity, Compare compare) {
  heap* obj = malloc(sizeof *obj);
  obj->array = malloc(initial_capacity * sizeof(int));
  obj->size = 0;
  obj->capacity = initial_capacity;
  obj->compare = compare;
  return obj;
}

void _heapify(heap* obj, int index) {
  int parent = index/2;
  if (obj->compare(obj->array[index], obj->array[parent])) {
    int tmp = obj->array[index];
    obj->array[index] = obj->array[parent];
    obj->array[parent] = tmp;
    _heapify(obj, parent);
  }
}

void push(heap* obj, int value) {
  if (obj->size == obj->capacity) {
    obj->array = realloc(obj->array, 2*obj->capacity);
    obj->capacity *= 2;
  }

  obj->array[obj->size] = value;
  _heapify(obj, obj->size);
  obj->size++;
}

void __heapify(heap* obj, int parent) {
  int left = 2*parent + 1;
  int right = 2*parent + 2;

  int target = parent;

  if (left < obj->size && obj->compare(obj->array[left], obj->array[parent]))
    parent = left;
  if (right < obj->size && obj->compare(obj->array[right], obj->array[parent]))
    parent = right;

  if (target != parent) {
    int tmp = obj->array[parent];
    obj->array[parent] = obj->array[target];
    obj->array[target] = tmp;
    __heapify(obj, parent);
  }
}

void pop(heap* obj) {
  if (empty(obj)) {
    return ;
  }

  obj->size--;
  int tmp = obj->array[0];
  obj->array[0] = obj->array[obj->size];
  obj->array[obj->size] = tmp;
  __heapify(obj, 0);
}

int peek(heap* obj) {
  return obj->array[0];
}

bool empty(heap* obj) {
  return obj->size == 0;
}

void traverse(heap* obj, void (*callback)(int value)) {
  for(int i = 0; i < obj->size; ++i) {
    callback(obj->array[i]);
  }
}
