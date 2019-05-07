#include <stdlib.h>
#include "BinarySearchTree.h"

typedef struct node{
  struct node* left,* right;
  int value;
}node;

struct BST{
  node* root;
};

BST* BinarySearchTree() {
  BST* obj = malloc(sizeof *obj);
  obj->root = NULL;
  return obj;
}

node* deletepostorder(node* n) {
  if (n == NULL)
    return NULL;

  deletepostorder(n->left);
  deletepostorder(n->right);

  free(n);

  return NULL;
}

void BSTDestructor(BST** obj) {
  (*obj)->root = deletepostorder((*obj)->root);
  free(*obj);
  *obj = NULL;
}

node* _insert(node* n, int value) {
  if (n == NULL) {
    n = malloc(sizeof *n);
    n->value = value;
  }
  else if (value < n->value) {
    n->left = _insert(n->left, value);
  }
  else if (value > n->value) {
    n->right = _insert(n->right, value);
  }
  return n;
}

void insert(BST* obj, int value) {
  obj->root = _insert(obj->root, value);
}

node* _search(node* n, int value) {
  if (n != NULL) {
    if (value == n->value)
      return n;
    if (value < n->value)
      return _search(n->left, value);
    if (value > n->value)
      return _search(n->right, value);
  }
  return NULL;
}

bool search(BST* obj, int value) {
  return _search(obj->root, value) != NULL;
}

node* _copy(node* n) {
  if (n == NULL)
    return NULL;

  node* m = malloc(sizeof *m);
  m->value = n->value;

  m->left = _copy(n->left);
  m->right = _copy(n->right);

  return m;
}

void copy(BST* this, BST* other) {
  if (!this || !other || this == other)
    return ;

  this->root = deletepostorder(this->root);
  this->root = _copy(other->root);
}

node* findMin(node* n) {
  if (n == NULL)
    return NULL;
  else if (n->left == NULL)
    return n;
  else
    return findMin(n->left);
}

node* _delete(node* n, int value) {
  if (n == NULL) {
    return NULL;
  }
  else if (value < n->value) {
    n->left = _delete(n->left, value);
  }
  else if (value > n->value) {
    n->right = _delete(n->right, value);
  }
  else if (n->left && n->right) {
    node* tmp = findMin(n->right);
    n->value = tmp->value;
    n->right = _delete(n->right, n->value);
  }
  else {
    node* tmp = n;

    if (n->left == NULL)
      n = n->right;
    else if (n->right == NULL)
      n = n->left;

    free(tmp);
  }
  return n;
}

void delete(BST* obj, int value) {
  obj->root = _delete(obj->root, value);
}

void _traverse(node* n, void (*callback)(int value)) {
  if (n != NULL) {
    _traverse(n->left, callback);
    callback(n->value);
    _traverse(n->right, callback);
  }
}

void traverse(BST* obj, void (*callback)(int value)) {
  _traverse(obj->root, callback);
}
