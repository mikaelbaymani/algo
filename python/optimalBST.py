#!/usr/bin/python -B
from collections import OrderedDict
# The Algorithm
# Let A=2-D array.
# For s=0 to (n-1)
#   For i=1 to n
#                i+s
#     A[i,i+s] = min [ sum(p_k) + A[i,r-1] + A[r+1,i+s] ]
#                r=i
# return A[1,n]


# 7 keys (say 1,2,3,4,5,6,7 in sorted order) and frequencies w1 = .2,
# w2 = .05, w3 = .17, w4 = .1,w 5 = .2, w6 = .03, w7 = .25.
freq = OrderedDict()
freq[1] = .2
freq[2] = .05
freq[3] = .17
freq[4] = .1
freq[5] = .2
freq[6] = .03
freq[7] = .25

sumdict = lambda d,i,j : sum( [d[k] for k in xrange(i,j+1)])

class memo:
    def __init__(self, f):
        self._f = f
        self._memo = {}
    def __call__(self, *args):
        if not args in self._memo:
            self._memo[args] = self._f(*args)
        return self._memo[args]

def A(i,j):
    global freq
    if i>j:
        return 0
    elif i == j:
        return freq[i]
    minval = float('inf')
    for k in xrange(i,j+1):
        res = A(i, k-1) + A(k+1, j) + sumdict(freq, i, j)
        if res < minval:
            minval = res
    return minval

A = memo(A)                   # Let A=2-D array. [ A[i,j] represent opt BST value for items {i,...,j} ]
for s in xrange(0, len(freq)):# For s=0 to (n-1)
    for i in freq:            # For i=1 to n
        if i+s <= len(freq):
                              #            i+s
            _ = A(i,i+s)      # A[i,i+s] = min [ sum(p_k) + A[i,r-1] + A[r+1,i+s] ]
                              #            r=i

print A(1,len(freq))          # Return A[1,n]
# EOF
