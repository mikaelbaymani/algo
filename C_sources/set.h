#ifndef SET_H
#define SET_H
#include <stdint.h>
#include <stdbool.h>

typedef struct set set;

set* Set(int capacity);

void Setdestructor(set** obj);

int insert(set* obj, int64_t value);

bool contains(set* obj, int64_t value);

void erase(set* obj, int64_t value);

void traverse(set* obj, void (*callback)(set*, int64_t));

#endif
