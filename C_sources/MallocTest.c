#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Malloc.h"
static size_t GetFree();

#define RAND()    ((double)rand()/(double)RAND_MAX)
#define BUFS      3500

int main(int argc, char* argv[]) {
  uint8_t bigbuf[1000 * 1000];
  unsigned int size;
  unsigned int where;
  void *ptr[BUFS];
  unsigned int i;

  srand(time(NULL));
  InitMalloc(bigbuf, sizeof (bigbuf));
  printf("%lu B\n", GetFree());

  for (i = 0; i < BUFS; i++) {
        ptr[i] = NULL;
  }

  for (i=0; i < 30000; i++) {
    where = (int)(RAND() * BUFS);
    if (ptr[where] == NULL) {
      size = (int)(RAND() * 1024 + 1);
      ptr[where] = Malloc(size);
      if (ptr[where] == NULL) {
        fprintf(stderr,
                "Malloc() returned NULL at iteration %d failed for size %d\n",
                i,size);
        fflush (stderr);
      }
    } else {
      Free(ptr[where]);
      ptr[where] = NULL;
    }
  }

  for (i=0; i < BUFS; i++) {
    if (ptr[i] != NULL) {
      Free(ptr[i]);
      ptr[i] = NULL;
    }
  }

  printf("%lu B\n", GetFree());
  return 0;
}


// Debug
static size_t GetFree() {
  size_t sz = 0;
  ALLOC_PTR block = G_FREE_LIST_INSTANCE;
  while (block) {
    sz += block->size;
    block = block->next;
  }
  return sz;
}
