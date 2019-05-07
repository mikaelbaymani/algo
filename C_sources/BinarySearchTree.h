#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "stdbool.h"

typedef struct BST BST;

BST* BinarySearchTree();

void BSTDestructor(BST** obj);

void insert(BST* obj, int value);

bool search(BST* obj, int value);

void copy(BST* this, BST* other);

void delete(BST* obj, int value);

void traverse(BST* obj, void (*callback)(int value));

#endif
