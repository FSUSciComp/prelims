import numpy as np
import scipy as sp
import time

#############################################################################80
### Solve system using Power Method
#############################################################################80
def power(A, tol):
  n = np.shape(A)[0]
  guess = np.ones((n,1))
  prev_norm = 10
  norm = 0
  iter = 0
  while tol < abs(prev_norm - norm):
    x = np.ones((n,1))
    scale = n
    x = np.dot(A, guess)
    scale = max(x)
    x /= scale
    guess = np.copy(x)
    prev_norm = norm
    norm = np.linalg.norm(guess)
    iter += 1
  return x, iter # max eig and iterations
  
# Find spectral radius using Rayleigh quotient
def eigenvalue(max_x, A):
  nu = np.dot(max_x.T, A)
  nu = np.dot(nu, max_x)
  val = nu / np.dot(max_x.T, max_x)
  return val

# Set up tolerance and matrix
tol = 1e-6
m = 100
h = 1.0/(m+1)
A = np.zeros((m,m))
main_diag = 2.0/h**2
off_diag = -1.0/h**2
A[0,0:2] = np.array([main_diag, off_diag])
for i in range(1,m-1):
  A[i,i-1:i+2] = np.array([off_diag, main_diag, off_diag])
A[m-1,m-2:m] = np.array([off_diag, main_diag])

v, iter = power(A, tol) # Get dominant eigenvector
print "After", iter, "iterations."
print "--------------------------"
print "Dominant eigenvector: \n", v
sr = eigenvalue(v, A) # Get eigenvalue corresponding to eigenvector
print "Spectral radius: \n", sr
