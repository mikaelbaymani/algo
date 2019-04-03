#ifndef MALLOC_H
#define MALLOC_H
#include <stdint.h>
#include <string.h>

typedef struct alloc{
  struct alloc * next;
  size_t size;
  uint8_t data[0];
} ALLOC, *ALLOC_PTR;

/** Global variables should be prefixed with a "G_" */
extern ALLOC_PTR G_FREE_LIST_INSTANCE;

/**
 * @brief Create a malloc
 * Call InitMalloc() before you do anything else.
 * @param memo - user-provided memory.
 * @param size_in_bytes - size of memory, in bytes.
 * @return (none)
 */
void InitMalloc(uint8_t* mem0, size_t size_in_bytes);

/**
 * @brief Allocate memory.
 * The Malloc() function allocates size bytes and returns a pointer to
 * the allocated memory. The memory is not initialized.
 * @param len - size of the memory block, in bytes
 * @return On success, a pointer to the memory block allocated by the
 *         function. If the function failed to allocate the requested
 *         block of memory, a null pointer is returned.
 */
void* Malloc(size_t len);

// MACRO: Calloc allocates space for an array of nelem elements of
// size elsize. The space is initialized to zeros. No NULL check!!
#define Calloc(nelem, elsize) memset(Malloc(nelem*elsize), '\0', nelem*elsize)

/**
 * @brief Deallocate space
 * The Free() function frees the memory space pointed to by p.
 * @param p - pointer to a memory block previously allocated with
 *            Malloc() to be deallocated.
 * @return (none)
 */
void Free(void* p);
#endif
