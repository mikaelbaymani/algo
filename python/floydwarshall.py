#!/usr/bin/python -B
# The Floyd-Warshall Algorithm
class Vertex:
    def __init__(self, key):
        self._neighbors = {}
        self._key = key
    def addNeighbor(self, neighbor_vertex, cost):
        self._neighbors[neighbor_vertex] = cost
    def getConnections(self):
        return self._neighbors
    def getCost(self, to_vertex):
        if to_vertex in self._neighbors:
            return self._neighbors[to_vertex]
        return float("inf")

class Graph:
    def __init__(self):
        self._vertices = {}
        self._sorted = {}
    def addVertex(self, vertex):
        self._vertices[vertex] = Vertex(vertex)
    def addEdge(self, from_vertex, to_vertex, cost):
        if from_vertex not in self._vertices:
            self.addVertex(from_vertex)
        if to_vertex not in self._vertices:
            self.addVertex(to_vertex)
        self._vertices[from_vertex].addNeighbor(to_vertex, cost)
    def getVertices(self):
        if not self._sorted:
            self._sorted = self._vertices.keys()
            self._sorted.sort()
        return self._sorted
    def getEdge(self, from_vertex, to_vertex):
        return self._vertices[from_vertex].getCost(to_vertex)
    def __str__(self):
        return str(self.getVertices())

class memo:
    def __init__(self, f):
        self._f = f
        self._memo = {}
    def __call__(self, *args):
        if not args in self._memo:
            self._memo[args] = self._f(*args)
        return self._memo[args]
    def __delitem__(self, *args):
        del self._memo[args[0]]


G = Graph()
with open("g3.txt") as f:
    (nr_of_vertices,nr_of_edges) = f.readline().split()
    for line in f.readlines():
        (from_vertex,to_vertex,cost) = line.split()
        G.addEdge( int(from_vertex), int(to_vertex), int(cost) )

def A(i,j,k):
    global G
    if k >= 2:
        del A[i,j,k-2]
    elif k == 0:
        if i == j: return 0
        else: return G.getEdge(i,j)
    case1 = A(i,j,k-1)
    case2 = A(i,k,k-1) + A(k,j,k-1)
    if case1 < case2:
        return case1
    return case2

#print G
minval = float('inf')
A = memo(A)
for k in G.getVertices():
    for i in G.getVertices():
        for j in G.getVertices():
            res = A(i,j,k)
            if i == j:
                if res < 0:
                    print "NULL"
                    exit(0)
            if res < minval:
                minval = res
    print str(k)
print minval
