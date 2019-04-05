#!/usr/bin/python -B
import time,math
from collections import OrderedDict

class Timer:
    # The time() function returns the
    # number of seconds passed since epoch.
    def __init__(self):
        self._beg = time.time()
    def reset(self):
        self._beg = time.time()
    def elapsed(self):
        return time.time() - self._beg

G=OrderedDict()
V={}
with open('nn.txt') as f:
    _ = f.readline()
    for line in f.readlines():
        i,x,y = line.split()
        G[int(i)] = (float(x), float(y))
        V[int(i)] = False

head = 1
total = 0
tmr = Timer()
tot = Timer()
for _ in range(0,len(G)-1):
    tmr.reset()
    mindist = float('inf')
    V[head] = True
    for curr in G:
        if V[curr]:
            continue
        #if curr == head:
        #    continue
        x, y = G[head]
        z, w = G[curr]
        dist = math.sqrt( (x-z)**2 + (y-w)**2 )
        # print ("%d(%.2f)" % (curr,dist)),
        if dist < mindist:
            mindist = dist
            nextitem = curr
    head = nextitem
    total += mindist
    print "i=%d, %.2f(+%.4fs)" % (_+1, tot.elapsed(), tmr.elapsed())

x, y = G[1]
z, w = G[head]
print total + math.sqrt( (x-z)**2 + (y-w)**2 )
