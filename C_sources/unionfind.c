#include <stdlib.h>
#include "unionfind.h"
// Ref: https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf
struct _unionfind {
  int* id;
  int* sz;
};

unionfind* UnionFind(size_t sz) {
  unionfind* uf = malloc(sizeof *uf);
  uf->id = malloc(sz * sizeof(int) );
  uf->sz = malloc(sz * sizeof(int) );

  while(sz--) {
    uf->id[sz] = sz;
    uf->sz[sz] = 1;
  }

  return uf;
}

static int root(unionfind* uf, int i) {
  // Returns root.
  // Path compression.
  while(i != uf->id[i]) {
    uf->id[i] = uf->id[uf->id[i]];
    i = uf->id[i];
  }
  return i;
}

bool find(unionfind* uf, int p, int q) {
  return root(uf, p) == root(uf, q);
}

bool unite(unionfind* uf, int p, int q) {
  // Perform a union operation. Returns
  // false if union already performed.
  int l = root(uf, p);
  int r = root(uf, q);

  if(l == r) {
    return false;
  }

  if(uf->sz[l] < uf->sz[r]) {
    uf->id[l] = r;
    uf->sz[r] += uf->sz[l];
  } else {
    uf->id[r] = l;
    uf->sz[l] += uf->sz[r];
  }

  return true;
}
// EOF
