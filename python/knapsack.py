#!/usr/bin/python -B

vw = {}

with open("knapsack1.txt") as f:
    knapsack_size,number_of_items=f.readline().split()
    knapsack_size = int(knapsack_size)
    number_of_items = int(number_of_items)
    item = 1
    for line in f.readlines():
        value,weight = line.split()
        vw[item] = (int(value),int(weight))
        item += 1

class memo:
    def __init__(self, f):
        self._f = f
        self._memo = {}
    def __call__(self, *args):
        if not args in self._memo:
            self._memo[args] = self._f(*args)
        return self._memo[args]
    def __delitem__(self, *args):
        if args[0] in self._memo:
            del self._memo[args[0]]
    def __str__(self):
        return str(self._memo)
    def __len__(self):
        return len(self._memo)

def A(i, x):
    global vw
    if i == 0:
        return 0;
    v,w=vw[i]
    if x-w < 0:
        res = A(i-1,x)
    else:
        res = max([A(i-1,x), A(i-1,x-w)+v])
    del A[i-2,x]
    return res

A=memo(A)


for i in range(1,number_of_items+1):
    for x in range(0, knapsack_size+1):
        A(i,x)

print "optimal value = " + str(A(i,x))
print len(A)
