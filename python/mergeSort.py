#!/usr/bin/python -B

def mergeAndCount(A,B):
    # A,B two input lists (sorted)
    # C  output list
    # i,j current pointers to each list, start at beginning
    # a_i, b_j elements pointed by i, j
    # count number of inversion, initially 0
    C = []
    i = 0
    j = 0
    count = 0
    try:
	while A[i] and B[j]:
	    if B[j] < A[i]:
		count=count+len(A[i:])
		C.append(B[j])
		j=j+1
	    else:
		C.append(A[i])
		i=i+1
    except IndexError: pass
    finally:
	# now one list is empty
	# append the remainder of the list to C
	if len(B) <= j:
	    C.extend(A[i:])
	elif len(A) <= i:
	    C.extend(B[j:])
    return count,C

def sortAndCount(L):
    # if L has one element return 0
    if len( L ) is 1:
	return 0,L
    else:
	# divide L into A, B
	half = len( L ) // 2
	A = L[:half]
	B = L[half:]
	rA, A = sortAndCount(A)
	rB, B = sortAndCount(B)
	r, L = mergeAndCount(A,B)

    return r+rA+rB, L

def readIntegers(filename):
    with open(filename) as f:
	return [int(x) for x in f]

inv,_ = sortAndCount( readIntegers("IntegerArray.txt") )

print inv
