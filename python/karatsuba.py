from math import pow,log10

def karatsuba(num1, num2):
	if (num1 < 10) or (num2 < 10):
		return num1*num2
	# calculates the size of the numbers
	m = max( int( log10(num1) ), int( log10(num2) ) ) + 1
	m2 = m//2
	m3 = -(-m//2)
	
	# convert to strings
	# pad zeros to strings
	snum1 = str(num1)
	snum2 = str(num2).zfill( len(snum1) )
	snum1 = snum1.zfill( len(snum2) )
	
	# split the digit sequences in the middle
	high1, low1 = int( snum1[:m3] ), int( snum1[m3:] )
	high2, low2 = int( snum2[:m3] ), int( snum2[m3:] )
	
	# 3 calls made to numbers approximately half the size
	z0 = karatsuba(low1, low2)
	z1 = karatsuba(low1 + high1, low2 + high2)
	z2 = karatsuba(high1, high2)
	
	return (z2 * 10**(m2*2)) + ((z1 - z2 - z0) * 10**m2) + z0	

print karatsuba(3141592653589793238462643383279502884197169399375105820974944592,
				2718281828459045235360287471352662497757247093699959574966967627)