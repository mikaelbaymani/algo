#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <stdbool.h>

typedef struct heap heap;
typedef bool (*Compare)(int, int);
bool Min(int, int), Max(int, int);

heap* BinaryHeap(int initial_capacity, Compare compare);

void push(heap* obj, int value);

void pop(heap* obj);

bool empty(heap* obj);

void traverse(heap* obj, void (*callback)(int));

#endif
