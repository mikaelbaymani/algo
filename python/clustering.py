#!/usr/bin/python -B
import heapq

class PriorityQueue:
    def __init__(self, key):
        self._key = key
        self._heap = []

    def insert(self, item):
        heapq.heappush(self._heap, (self._key(item), item) )

    def top(self):
        return heapq.heappop(self._heap)[1]

    def empty(self):
        return len(self._heap)==0

class WeightedQuickUnion(object):
    # https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf
    # Data Structure    Union    Find
    # WeightedQU        log N    log N
    def __init__(self, n):
        self._id = []
        self._sz = []
        for i in range(n):
            self._id.append(i)
            self._sz.append(1)

    def leader(self, i):
        # Return leader
        while i != self._id[i]:
            ## Path compression.
            self._id[i] = self._id[self._id[i]]
            i = self._id[i]
        return i

    def find(self, p, q):
        return self.leader(p) == self.leader(q)

    def unite(self, p, q):
        # Perform a union operation. Returns
        # False if union already performed.
        l = self.leader(p)
        r = self.leader(q)
        if l == r:
            return False
        # Modify quick-union to
        # merge smaller tree into larger tree
        # update the _sz[] array
        if self._sz[l] < self._sz[r]:
            self._id[l] = r
            self._sz[r] += self._sz[l]
        else:
            self._id[r] = l
            self._sz[l] += self._sz[r]
        return True

def kclustering(PQueue, noOfNodes, k = 4):
    if k > noOfNodes:
        return ;

    noOfClusters = noOfNodes
    WQU = WeightedQuickUnion(noOfNodes+1)

    while True:
        if noOfClusters == k:
            break

        node1, node2, _ = PQ.top()
        if WQU.unite(node1, node2) == True:
            noOfClusters -= 1

    while not PQ.empty():
        node1, node2, dist = PQ.top()
        if not WQU.find(node1, node2):
            break

    return dist

PQ = PriorityQueue(key=lambda triplet: triplet[2])

with open("clustering1.txt") as f:
    noOfNodes = int( f.readline() )
    for line in f.readlines():
        node1, node2, dist = line.split()
        PQ.insert( (int(node1), int(node2), int(dist)) )

print kclustering(PQ, noOfNodes)
