#ifndef DEQUE_H
#define DEQUE_H
#include <stdbool.h>

typedef struct deque deque;

deque* Deque();

void DequeDestructor(deque** obj);

void push_front(deque* obj, int value);

void push_back(deque* obj, int value);

void pop_front(deque* obj);

void pop_back(deque* obj);

int front(deque* obj);

int back(deque* obj);

bool empty(deque* obj);

void traverse(deque* obj, void (*callback)(int));

#endif
