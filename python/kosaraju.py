#!/usr/bin/python -B
# Kosaraju's algorithm is a linear time algorithm to find the
# strongly connected components of a directed graph.
import sys
import operator

print sys.getrecursionlimit()
sys.setrecursionlimit(100000)
print sys.getrecursionlimit()
FILENAME = "kosaraju.txt"

class DirectedGraph(object):

    def __init__(self, graph_dict = {}):
        # Init agraph. If you pass no dictionary,
        # an empty dict will be used.
        self.graph_dict = graph_dict

    def addVertex(self, vertex):
        # If the vertex <vertec> is not in self._graph_dict,
        # a <key> node with an empty list as a value
        # is added to the graph.
        if vertex not in self.graph_dict:
            self.graph_dict[vertex] = []
        else:
            pass

    def addEdge(self, vertex_from, vertex_to):
        if vertex_from == vertex_to:
            return
        if vertex_from not in self.graph_dict:
            self.graph_dict[vertex_from] = [vertex_to, ]
        else:
            self.graph_dict[vertex_from].append(vertex_to)

    def reverseGraph(self):
        # Here: Just iterate the sub-lists and the keys
        # in those and add them to a new dictionary with
        # the list values as keys.
        reversed_graph_dict = {}
        for From, sublist in self.graph_dict.iteritems():
            if From not in reversed_graph_dict:
                reversed_graph_dict[From] = []
            for To in sublist:
                if To in reversed_graph_dict:
                    reversed_graph_dict[To].append(From)
                else:
                    reversed_graph_dict[To] = [From,]
        self.graph_dict = reversed_graph_dict
        return self

    def min(self):
        return min(self.graph_dict)

    def max(self):
        return max(self.graph_dict)

    def size(self):
        return len( self.graph_dict )

    def __copy__(self):
        return DirectedGraph(self.graph_dict)

    def __getitem__(self, index):
        return self.graph_dict[index]

    def __str__(self):
        stringout = ""
        for k,v in self.graph_dict.iteritems():
            stringout += str(k) + " : " + str(v) + "\r\n"
        return stringout[:-1]

downto = lambda start, end : range ( start, end-1, -1 )

def DFSLoop(graph):                              # DFS-Loop (graph G)
    DFSLoop.f = [None] * 1000000
    DFSLoop.s = set()                            # for finishing times in 1st pass
    DFSLoop.t = 0                                # for leaders in 2nd pass
    DFSLoop.explored = [False] * 1000000
    DFSLoop.leaders = {}
    for i in downto( 1000000, 1 ):               # for i = n downto 1
        try:
            graph[i]
        except:
            continue
        if DFSLoop.explored[i] is False:         # if i not yet explored
            DFSLoop.s.add(i)                     # s:=1
            def DFS(graph, i, leader):           # DFS(graph G, node i)
                DFSLoop.explored[i] = True       # mark i as explored
                if leader in DFSLoop.leaders:
                    DFSLoop.leaders[leader] += 1
                else:
                    DFSLoop.leaders[leader] = 1
                for j in graph[i]:               # for each arc (i,j) G
                    if DFSLoop.explored[j] is False:# if j not yet explored
                        DFS(graph, j, leader)    # DFS(G,j)
                DFSLoop.t += 1                   # t++
                DFSLoop.f[i] = DFSLoop.t         # i's finishing time
            DFS(graph, i, i)                     # DFS(G,i)
    return (DFSLoop.s, DFSLoop.f, DFSLoop.leaders)

G = DirectedGraph()

with open (FILENAME, 'r') as f:
    for line in f.readlines():
        values = line.split()
        From, To = values[0], values[1]
        G.addEdge(int(From), int(To))

Grev = G.__copy__().reverseGraph()
## print G
## print Grev

print "run 1st DFS-Loop"
( _ , f, _ ) = DFSLoop(Grev)
#print f

graph_dict = {}
for key,val in G.graph_dict.iteritems():
    graph_dict[ f[key] ] = []
    for v in val:
        if f[v] not in graph_dict:
            graph_dict[ f[v] ] = []
        graph_dict[ f[key] ].append( f[v] )

Gnew = DirectedGraph(graph_dict)
print Gnew

print "run 2nd DFS-Loop"
( _ , _ , leaders ) = DFSLoop(Gnew)
print sorted(list(leaders.values()), reverse=True)[:5]
