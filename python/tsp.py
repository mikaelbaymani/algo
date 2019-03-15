#!/usr/bin/python -B
# Travelling Salesman Problem
# A Dynamic Programming Algorithm
import math, time
from itertools import combinations
CITIES = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
          15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25)
COORDINATES = []
GRAPH = {}
SET=None
START = CITIES[0]
FILENAME='tsp.txt'

class Timer:
    # The time() function returns the
    # number of seconds passed since epoch.
    def __init__(self):
        self._beg = time.time()
    def reset(self):
        self._beg = time.time()
    def elapsed(self):
        return time.time() - self._beg

class memo:
    # Memoize
    def __init__(self, f):
        self._f = f
        self._memo = {}
    def __call__(self, *args):
        if not args in self._memo:
            self._memo[args] = self._f(*args)
        return self._memo[args]
    def __delitem__(self, args):
        if args in self._memo:
            del self._memo[args]

def ForeachSetThatContainsOne(S,m):
    # For each set S<={1,2,...,n} of size m that contains 1:
    for _tuple in [i for i in combinations(S[1:],m-1)]:
        subset = 1 << S[0]
        for t in _tuple:
            subset |= (1 << t)
        yield subset,_tuple

def Bits(n):
    bit = 1
    pos = 0
    while n >= bit:
       if n & bit:
           yield pos
       bit <<= 1
       pos += 1

# Read inputfile and populate GRAPH
with open(FILENAME, 'r') as f:
    _ = f.readline()
    for line in f.readlines():
        x, y = line.split()
        COORDINATES.append( (float(x),float(y)) )
for i in range(0, len(COORDINATES)):
    for j in range(i+1, len(COORDINATES)):
        from_city = CITIES[i]
        to_city = CITIES[j]
        x, y = COORDINATES[i]
        z, w = COORDINATES[j]
        # The distance between two cities is defined as the Euclidean
        # distance --- that is, two cities at locations (x,y)(x,y) and
        # (z,w)(z,w) have distance sqrt((x-z)^2 + (y-w)^2) between them.
        cost = math.sqrt((x-z)**2 + (y-w)**2)

        if not from_city in GRAPH:
            # Add city to GRAPH
            GRAPH[from_city] = {}
        if not to_city in GRAPH:
            # Add city to GRAPH
            GRAPH[to_city] = {}

        GRAPH[from_city][to_city] = GRAPH[to_city][from_city] = cost
## Let A=2D array, indexed by subsets S<={1,2,...,n}
## that contain 1 and destinations j E {1,2,...,n}.
def A(S, j):
    global GRAPH,START
    if j == START:
        if S == (1 << START): return 0
        else: return float('inf')
    S &= ~(1<<j)
    return min( [A(S,k)+GRAPH[k][j] for k in Bits(S)] )
A=memo(A)

SET = CITIES[:len(COORDINATES)]
inner = Timer()
outer = Timer()
for m in range(2,len(SET)+1):                                # For m =2,3,4,...,m: [m subproblem size]
    for (subset,_tuple) in ForeachSetThatContainsOne(SET,m): # For each set S<={1,2,...,n} of size m that contains 1:
        for j in _tuple:                                     # For each j E S, j!=1

            _ = A(subset,j)
    # Free up some memory
    for (subset, _tuple) in ForeachSetThatContainsOne(SET,m - 1):
        for j in _tuple: del A[(subset,j)]

    print("m = %d, %.2fs" % (m, inner.elapsed()) )
    inner.reset()

S=0
for s in SET:
    S |= (1 << s)
# The minimum cost of a traveling salesman tour for this instance, rounded down
# to the nearest integer.
print("Minimum cost of TSP: %d" % int(min( [A(S,s)+GRAPH[s][START] for s in Bits(S) if s!=START])))
print("It took %.2f seconds" % outer.elapsed())
