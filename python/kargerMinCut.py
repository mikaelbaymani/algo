#!/usr/bin/python -B

from copy import deepcopy
from random import choice

def Sort(a, b):
    return (a, b) if b > a else (b, a)

class Vertex:
    def __init__(self, id):
	self.id = id
	self.neighbors = set()

    def addNeighbor(self, neighborId):
	self.neighbors.add(neighborId)

    def delNeighbor(self, neighborId):
	if neighborId in self.neighbors:
	    self.neighbors.remove(neighborId)

    def getNeighbors(self):
	return [x for x in self.neighbors]

    def __str__(self):
	return str(self.id) + "->" + "->".join(map(str,self.getNeighbors()))

class UndirectedGraph:
    def __init__(self):
	self.edges = {}
	self.vertices = {}
	self.noOfVertices = 0

    def addVertex(self, id):
        if id not in self.vertices:
	    self.vertices[id] = Vertex(id)
	    self.noOfVertices = self.noOfVertices + 1

    def delVertex(self, id):
	if id in self.vertices:
	    for neighborId in self.vertices[id].getNeighbors():
		self.delEdge(id, neighborId)
	    del self.vertices[id]
	    self.noOfVertices = self.noOfVertices - 1

    def addEdge(self, From, To, weight=None):
	if From == To: return
	if To not in self.vertices:
	    self.addVertex(To)
	if From not in self.vertices:
	    self.addVertex(From)
	self.vertices[From].addNeighbor(To)
	self.vertices[To].addNeighbor(From)
	if weight is None:
	    self.edges[Sort(From, To)] = 1
	elif Sort(From, To) in self.edges:
	    self.edges[Sort(From, To)] += weight
	else:
	    self.edges[Sort(From, To)] = weight

    def delEdge(self, From, To):
	if Sort(From, To) not in self.edges:
	    return
	self.vertices[From].delNeighbor(To)
	self.vertices[To].delNeighbor(From)
	del self.edges[Sort(From, To)]

    def getVertices(self):
	return self.vertices.keys()

    def merge(self, From=None, To=None):
	if (From == None) or (To == None):
	    merged, toBeRemoved = choice(self.edges.keys())
	else:
	    merged, toBeRemoved = From, To
	for newNeighbor in self.vertices[toBeRemoved].getNeighbors():
	    self.addEdge(merged, newNeighbor, self.edges[Sort(toBeRemoved, newNeighbor)])
	self.delVertex(toBeRemoved)

    def minCut(self):
	while (self.noOfVertices > 2):
	    self.merge()
	return self.edges[self.edges.keys()[0]]

    def getNumVertices(self):
	return self.noOfVertices

    def kargersAlgorithm(self, n=None):
	min = 10**100
	if n is None:
	    n = self.getNumVertices()-1
	while n != 0:
	    selfCopy = deepcopy(self)
	    val = selfCopy.minCut()
	    if val < min:
		min = val
	    n = n - 1
	return min

    def __str__(self):
	out = ""
	for v in self.getVertices():
	    out += str(self.vertices[v]) + "\n";
	return out + str(self.edges)


graph = UndirectedGraph()

def readIntegers(graph, filename):
    with open(filename) as f:
	for l in f.readlines():
	    _list = l.split()
	    vertex = int(_list.pop(0))
	    graph.addVertex(vertex)
	    for neighbor in _list:
		graph.addEdge(vertex, int(neighbor))

readIntegers(graph, "kargerMinCut.txt")
print graph.kargersAlgorithm(1000)
