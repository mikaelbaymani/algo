#ifndef TRIE_H
#define TRIE_H

typedef struct _trie trie;

trie* Trie();

void insert(trie* t, char* w);

int search(trie* t, char* w);

int startsWith(trie* t, char* w);

void traverse(trie* t, char w[], int level, void (*callback)(char []));

#endif
