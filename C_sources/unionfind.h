#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <stdbool.h>

typedef struct _unionfind unionfind;

unionfind* UnionFind(size_t sz);

bool find(unionfind* uf, int p, int q);

bool unite(unionfind* uf, int p, int q);

#endif
