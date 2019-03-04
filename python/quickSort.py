
# For the first part of the programming assignment, you should
# always use the first element of the array as the pivot element.
def callback1(A,l,r):
	pass

# Compute the number of comparisons (as in Problem 1), always using
# the final element of the given array as the pivot element. Again,
# be sure to implement the Partition subroutine exactly as it is
# described in the video lectures.
def callback2(A,l,r):
	A[l], A[r-1] = A[r-1], A[l]

# Compute the number of comparisons (as in Problem 1), using the
# "median-of-three" pivot rule. [The primary motivation behind this
# rule is to do a little bit of extra work to get much better performance
# on input arrays that are nearly sorted or reverse sorted.] In more detail,
# you should choose the pivot as follows. Consider the first, middle, and final
# elements of the given array. (If the array has odd length it should be clear
# what the "middle" element is; for an array with even length 2k2k, use the k^{th}k th
# element as the "middle" element. So for the array 4 5 6 7, the "middle" element
# is the second one ---- 5 and not 6!) Identify which of these three elements is the
# median (i.e., the one whose value is in between the other two), and use this as
# your pivot. As discussed in the first and second parts of this programming
# assignment, be sure to implement Partition exactly as described in the video
# lectures (including exchanging the pivot element with the first element just before
# the main Partition subroutine).
def callback3(A,l,r):
	half = (r-l-1) // 2 + l
	if A[l] <= A[half] <= A[r-1] or A[r-1] <= A[half] <= A[l]:
		A[l], A[half] = A[half], A[l]
	elif A[half] <= A[l] <= A[r-1] or A[r-1] <= A[l] <= A[half]:
		pass
	else:
		A[l], A[r-1] = A[r-1], A[l]

#def partition(A,l,r,callback):
#	pivot, index = callback(A,l,r)
#	i = l
#	yes = False
#	for j in range(l, r):
#		if j == index:
#			pass
#		elif A[j] < pivot:
#			# swap
#			A[i], A[j] = A[j], A[i]
#			i = i + 1
#
#		if i == index:
#			i = i + 1
#			yes = True
#
#	if yes:
#		A[index], A[i-1] = A[i-1], A[index]
#		return i-1, r-l-1
#
#	A[index], A[i] = A[i], A[index]
#	return i, r-l-1

def partition(A,l,r,cb):
	cb(A,l,r)
	p = A[l]
	i = l + 1
	for j in range(l+1, r):
		if A[j] < p:
			A[j], A[i] = A[i], A[j]
			i = i + 1
	A[l], A[i-1] = A[i-1], A[l]
	return i-1, r-l-1

def quickSort(A,p,r,cb):
	c=0
	if p < r:
		q,c = partition(A,p,r,cb)
		c += quickSort(A,p,q,cb)
		c += quickSort(A,q+1,r,cb)
	return c

def readIntegers(filename):
	with open(filename) as f:
		return [int(x) for x in f]

arr = readIntegers("quickSort.txt")
print quickSort(arr, 0, 10000, callback1)
print arr[:10]
print arr[-10:]
print

arr = readIntegers("quickSort.txt")
print quickSort(arr, 0, 10000, callback2)
print arr[:10]
print arr[-10:]
print


arr = readIntegers("quickSort.txt")
print quickSort(arr, 0, 10000, callback3)
print arr[:10]
print arr[-10:]
print
