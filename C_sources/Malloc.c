#include <stdio.h>
#include "Malloc.h"
// Singleton
ALLOC_PTR G_FREE_LIST_INSTANCE;

/** This malloc behaves like the 'real' malloc. */
// This version of Malloc() will differ from the standard one in only one way.
// The very first call that should be made in any program that uses this version
// of Malloc() will be a call to InitMalloc(..)
void InitMalloc(uint8_t* memo, size_t size_in_bytes) {
  // Store the memo in a static global variable.
  G_FREE_LIST_INSTANCE = (ALLOC_PTR)memo;
  * G_FREE_LIST_INSTANCE = (ALLOC){NULL, size_in_bytes - sizeof (ALLOC)};
}

// Allocate memory block - Allocates a block of len bytes of memory, returning a
// pointer to the beginning of the block
void* Malloc(size_t len) {
  ALLOC_PTR block = G_FREE_LIST_INSTANCE;
  ALLOC_PTR next;
  ALLOC_PTR prev = NULL;
  for (; block && len; prev = block, block = block->next) {
    if ((sizeof(ALLOC) + len) < block->size) {
      next = (ALLOC_PTR)((size_t)block + len + sizeof(ALLOC));
      if (block == G_FREE_LIST_INSTANCE) {
        G_FREE_LIST_INSTANCE = next;
      }
      if (prev) {
        prev->next = next;
      }
      *next = (ALLOC){block->next, block->size - len - sizeof(ALLOC)};
      block->size = len;
    } else if (len <= block->size) {
      if (block->next && block == G_FREE_LIST_INSTANCE) {
        G_FREE_LIST_INSTANCE = block->next;
      } else if (block == G_FREE_LIST_INSTANCE) {
        G_FREE_LIST_INSTANCE = G_FREE_LIST_INSTANCE->next = NULL;
      } else {
        prev->next = block->next;
      }
    } else {
      continue;
    }

    *block = (ALLOC){NULL, block->size};
    return block->data;
  }

  return NULL;
}

// Mark the given block as free by linking it to the free-list
static void LinkBlock(ALLOC_PTR block) {
  if (block < G_FREE_LIST_INSTANCE) {
    block->next = G_FREE_LIST_INSTANCE;
    G_FREE_LIST_INSTANCE = block;
  } else {
    ALLOC_PTR tmp = G_FREE_LIST_INSTANCE;
    while (tmp->next && tmp->next < block) {
      tmp = tmp->next;
    }
    if (tmp->next) {
      block->next = tmp->next;
    }
    tmp->next = block;
  }
}

// Merge block with adjacent free blocks
static void Coalesce() {
  ALLOC_PTR block = G_FREE_LIST_INSTANCE;
  do {
    if (((size_t)block + block->size + sizeof(ALLOC)) == (size_t)block->next) {
      block->size += (block->next->size + sizeof(ALLOC));
      block->next = block->next->next;
    } else {
      block = block->next;
    }
  } while (block->next);
}

// Deallocate memory block - A block of memory previously allocated by a call to
// Malloc() is deallocated, making it available again for further allocations.
void Free(void* p) {
  // If ptr is NULL, no operation is performed
  if (p == NULL) {
    return ;
  }
  ALLOC_PTR block = (ALLOC_PTR)((size_t)p - sizeof(ALLOC));

  if (G_FREE_LIST_INSTANCE != NULL) {
    LinkBlock(block);
    Coalesce();
  } else {
    G_FREE_LIST_INSTANCE = block;
  }
}
