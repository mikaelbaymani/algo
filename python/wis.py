#!/usr/bin/python -B
w_dict = {}
with open("mwis.txt") as f:
    no_of_vertices = int(f.readline())
    line_number = 1
    for line in f.readlines():
        w_dict[line_number] = int(line)
        line_number += 1

A = [None]*(no_of_vertices+1)
A[0] = 0
A[1] = w_dict[1]
for i in range(2,len(A)):
    A[i] = max([A[i-1], A[i-2]+w_dict[i]])

s = set()
i = no_of_vertices
while i >= 1:
    if A[i-1] >= A[i-2]+w_dict[i]:
        i -= 1
    else:
        s.add(i)
        i -= 2

#print s
res = ""
for i in [1, 2, 3, 4, 17, 117, 517, 997]:
    if i in s:
        res += "1"
    else:
        res += "0"

print res


