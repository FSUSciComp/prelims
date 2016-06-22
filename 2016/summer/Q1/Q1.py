# A.T 19-June-2016
# Q1.py
# A program to solve stationary iteration A = T + L + U for Ax = b

import numpy as np



# Tri Diagonal Matrix Algorithm(a.k.a Thomas algorithm) solver

def TDMA(a,b,c,f):
    a, b, c, f = map(lambda k_list: map(float, k_list), (a, b, c, f))

    alpha = [0]
    beta = [0]
    n = len(f)
    x = [0] * n

    for i in range(n-1):
        alpha.append(-b[i]/(a[i]*alpha[i] + c[i]))
        beta.append((f[i] - a[i]*beta[i])/(a[i]*alpha[i] + c[i]))
            
    x[n-1] = (f[n-1] - a[n-2]*beta[n-1])/(c[n-1] + a[n-2]*alpha[n-1])

    for i in reversed(range(n-1)):
        x[i] = alpha[i+1]*x[i+1] + beta[i+1]
    
    return x

# Defining a function for preparation Matrix A
# Output: T , L , U ..... Input: A
def Matrix_Prep(A):
	
	# initializing matrices T , U , L with zeros
	T = np.zeros_like(A)
	U = np.zeros_like(A)
	L = np.zeros_like(A)


	# Making matrix L
	for i in range(len(A)):
		for j in range(len(A)):
			if i>= j+2:
				L[i][j] = A[i][j]
				
	# MAking matrix U
	for i in range(len(A)):
		for j in range(len(A)):
			if j>=i+2:
				U[i][j] = A[i][j]	
	# making matrix T 
	T = A - (U+L)
# Making list of Tridiagonal Matrix A to have:
#    T =    [BB1 CC1 .....0 ]
#       	[AA2 BB2 CC2...0]
#		    [...............]
#		    [0.......AAn BBn]

# Making Matrices AA, BB , CC like arrays to use in TDMA
	D1 = np.diag(A, k=1)
	D2 = np.diag(A)
	D3 = np.diag(A, k=-1)
	return T,L,U , D1, D2, D3
	
# We have to Test out our Algorithm with different Matrices

# CASE1 : Symmetric Positive Definite

		
# initialzing Matrix A for Left Hand Side of Ax = b
A = np.array([[2 ,-1,0],
              [-1,2,-1.],
              [0 ,-1,2]])

# initialzing Matrix b for Right Hand Side of Ax = b
b = np.array([0,0 ,4])
# initializing counter
N = 1
# Set maximum iteration
max_iter = 100
# Set the initial Guess
X = np.array([0 , 0 ,0])

# Main Loop
T1, L1, U1, D1,D2,D3 = Matrix_Prep(A)
print " Matrix : Symmetric Positive Definite A = "
print A

while( N < max_iter):
	#Making Right Hand Side
	RHS = b - np.dot((L1+U1),X)
	
	X1 =TDMA(D3,D1,D2,RHS)
	print "Iteration = " + str(N)
	print "X = " + str(X1)
	N += 1
	X = X1



# CASE2 : Diagonal Dominant Matrix

		
# initialzing Matrix A for Left Hand Side of Ax = b
B = np.array([[10 ,-1,8],
              [6  ,20,4],
              [5 ,3, 30]])

# initialzing Matrix b for Right Hand Side of Ax = b
b1 = np.array([32,58 ,101])
# initializing counter
K = 1

# Set the initial Guess
X = np.array([0 , 0 ,0])

# Main Loop
T2, L2, U2, D11,D22,D33 = Matrix_Prep(B)
print "Matrix : Diagonally dominant Matrix B"
print B
while( K < max_iter):
	#Making Right Hand Side
	RHS = b1 - np.dot((L2+U2),X)
	
	X2 =TDMA(D33,D11,D22,RHS)
	print "Iteration = " + str(K)
	print "X = " + str(X2)
	K += 1
	X = X2
	


# CASE3 : General Matrix

		
# initialzing Matrix A for Left Hand Side of Ax = b
C = np.array([[1 ,2,3],
              [4  ,-1,0],
              [2 ,8, -1]])

# initialzing Matrix b for Right Hand Side of Ax = b
b2 = np.array([14,2 ,15])
# initializing counter
M = 1

# Set the initial Guess
X = np.array([0 , 0 ,0])

# Main Loop
T3, L3, U3, D111,D222,D333 = Matrix_Prep(C)
print "Matrix : General Matrix C"
print C
while( M < max_iter):
	#Making Right Hand Side
	RHS = b2 - np.dot((L3+U3),X)
	
	X3 =TDMA(D333,D111,D222,RHS)
	print "Iteration = " + str(M)
	print "X = " + str(X3)
	M += 1
	X = X3
		
