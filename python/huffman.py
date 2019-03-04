#!/usr/bin/python -B
import sys,heapq

class PriorityQueue(object):

    def __init__(self, key):
        self._key = key
        self._heap = []

    def insert(self, item):
        heapq.heappush(self._heap, (self._key(item), item) )

    def top(self):
        return heapq.heappop(self._heap)[1]

    def __len__(self):
        return len( self._heap )

    def isEmpty(self):
        return len(self)==0

class Node:
    def __init__(self, data, right=None, left=None):
        self.data = data
        self.right = right
        self.left = left

class BinaryTree:
    _max_level = 0
    _min_level = sys.maxint

    def __init__(self, root=None):
        self._root = root

    def _inOrder(self, node, level):
        if node is None:
            return
        elif node.data is None:
            pass
        else:
            if level > self._max_level:
                self._max_level = level
            if level < self._min_level:
                self._min_level = level

        self._inOrder(node.left, level + 1)
        print str(node.data) + (" (root)" if node is self._root else "")
        self._inOrder(node.right, level + 1)

    def inOrder(self):
        level = 0
        self._inOrder(self._root, level)

PQ = PriorityQueue(key=lambda x: x[1])

# Characters A B C D E F
# Weights    3 2 6 8 2 6
PQ.insert( (Node('A'),3) )
PQ.insert( (Node('B'),2) )
PQ.insert( (Node('C'),6) )
PQ.insert( (Node('D'),8) )
PQ.insert( (Node('E'),2) )
PQ.insert( (Node('F'),6) )
#with open("huffman.txt") as f:
#    symbol=1
#    no_of_symbols = f.readline()
#    for line in f.readlines():
#        weight_of_symbol = int(line)
#        PQ.insert( (Node(str(symbol)), weight_of_symbol) )
#        symbol += 1

while len(PQ) > 2:
    right = PQ.top()
    left = PQ.top()
    new_node = Node(None, left[0], right[0])
    new_weight = left[1] + right[1]
    PQ.insert( (new_node, new_weight) )

left = PQ.top()
right = PQ.top()
tree = BinaryTree(Node(None, left[0], right[0]))
tree.inOrder()

print tree._max_level
print tree._min_level
