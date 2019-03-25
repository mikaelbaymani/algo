#ifndef HEAP_H
#define HEAP_H
#include <stdio.h>
#include <stdbool.h>

typedef struct _heap heap;

bool MIN(int i1, int i2);
bool MAX(int i1, int i2);
typedef bool (*Compare)(int i1, int i2);

heap* Heap(Compare compare, size_t capacity);

void Delete(heap** h);

void insert(heap* h, int i);

int peek(heap* h, int* i);

void pop(heap* h);

size_t size(heap* h);

bool empty(heap* h);

void traverse(heap* h, void (*callback)(int) );

#endif
