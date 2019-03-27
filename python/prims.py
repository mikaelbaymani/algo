#!/usr/bin/python -B
import heapq
class UndirectedGraph(object):

    def __init__(self):

        self._graph_dict = {}
        self._no_of_vertices = 0
        self._no_of_edges = 0

    def V(self):
        return self._no_of_vertices

    def E(self):
        return self._no_of_edges

    def _add(self, vertex):
        if vertex not in self._graph_dict:
            self._graph_dict[vertex] = []
            self._no_of_vertices += 1

    def set_edge(self, vertex1, vertex2, cost):
        self._add(vertex1)
        self._add(vertex2)
        self._graph_dict[vertex1].append( (vertex2,cost) )
        self._graph_dict[vertex2].append( (vertex1,cost) )
        self._no_of_edges += 1

    def get_edge(self, vertex1, vertex2):
        for neighbor,cost in self._graph_dict[vertex1]:
            if neighbor == vertex2:
                return cost

    def __call__(self):
        for vertex in self._graph_dict:
            yield vertex

    def __getitem__(self, vertex):
        if vertex in self._graph_dict:
            return self._graph_dict[vertex]
        return None

class PriorityQueue(object):

    def __init__(self, key):
        self._key = key
        self._heap = []

    def insert(self, item):
        heapq.heappush(self._heap, (self._key(item), item))

    def top(self):
        return heapq.heappop(self._heap)[1]

    def isEmpty(self):
        return len( self._heap )==0


graph = UndirectedGraph()
with open('edges.txt') as fp:
    first_line = fp.readline().split()
    no_of_vertices, no_of_edges = first_line
    for line in fp.readlines():
        vertex1,vertex2,cost=line.split()
        graph.set_edge(int(vertex1),int(vertex2),int(cost))

print graph.V()
print no_of_vertices
print graph.E()
print no_of_edges

def prims(graph, source=1):
    PQ = PriorityQueue(key=lambda x: x[1])
    unvisited = set()
    distance = 0
    PQ.insert( ((source, source), 0) )
    for vertex in graph():
        unvisited.add(vertex)
    while not PQ.isEmpty():
        p = PQ.top()
        cursor = p[0][0]
        if cursor in unvisited:
            unvisited.remove(cursor)
            distance += p[1]
            print p[1]

        for neighbor,_ in graph[cursor]:
            if neighbor in unvisited:
                PQ.insert( ((neighbor,cursor), graph.get_edge(neighbor,cursor)) )

    return distance

print prims(graph)
# -3612829
