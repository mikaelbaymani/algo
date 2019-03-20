#include <stdlib.h>
#include "trie.h"

// A struct representing a Trie node.
struct _trie {
  struct _trie* children[128];
};

/** Initialize your data structure here. */
trie* Trie() {
  int i;
  trie* t = malloc(sizeof *t);
  for(i = 0; i < 128; ++i)
    t->children[i] = NULL;
  return t;
}

/** Inserts a word into the trie. */
// Iterative function to insert a key
// in the Trie.
void insert(trie* t, char* w) {
  int i;
  trie* cur = t;
  while(*w) {
    i = *w&127;
    if(cur->children[i] == NULL)
      cur->children[i] = Trie();

    cur = cur->children[i];
    ++w;
  }
  i = '*'&127;
  if(cur->children[i] == NULL)
    cur->children[i] = Trie();
}

// Iterative function to search a key
// in a Trie. It return 0 if the key is
// found in the Trie, else it returns !=0
int search(trie* t, char* w)
{
  while (*w)
  {
    t = t->children[*w&127];

    if (!t)
      return !t;
    ++w;
  }
  return !t->children['*'&127];
}

// Returns 0 if there is any word in
// the Trie that starts with the
// given prefix.
int startsWith(trie* t, char* w)
{
  while (*w)
  {
    t = t->children[*w&127];

    if (!t)
      return !t;
    ++w;
  }
  return !t;
}

// Function to traverse the content
// of Trie.
void traverse(trie* t, char w[], int level, void (*callback)(char []))
{
  if (t->children['*'&127])
  {
    w[level] = '\0';
    callback(w);
  }

  int i;
  for (i = 0; i < 128; ++i)
    if (t->children[i])
    {
      w[level] = i;
      traverse(t->children[i], w, level + 1, callback);
    }
}
