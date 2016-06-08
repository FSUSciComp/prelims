# A.T. 3-June-2016
# Romberg.py
# A program to find the integral exp(-x**2) using Romberg
# Spring 2014 - Numerical Inegration - Q10 - Dr. Beerli


# Loading Packages


import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import solve
import math
from scipy import integrate

def Func(x):
	return np.exp(-x**2)

pltNorm = []
pltN = []
Accuracy = 1.0e-5 # Tolerance of the integral
ExactII = 0.35507 # Exact answer of the ingral
Err = 1.0 # Starting Error for recursive function
N = 0 # Step counter
while Err > Accuracy:
	# Points for calculating Trap I(N)
	x1 = np.linspace(-1, 1, num = 2**N)
	# Points for calculating Trap I(2N)
	x2 = np.linspace(-1, 1, num = 2**(N+1))
	# Evaluating Function at Those points
	y1 = Func(x1)
	y2 = Func(x2)
	# Calculating Trapezoid for multisteps
	I = integrate.cumtrapz(y1, x1, initial=0)
	II = integrate.cumtrapz(y2, x2, initial=0)
	# Defining Romberg Integral = I(2N) + ( I(2N) + I(N) )/3
	Romberg = ((II[-1] + (II[-1] - I[-1])/3.0)/np.sqrt(2.0*np.pi))**2
	# Calculating 2-Norm of result
	Norm = np.linalg.norm(Romberg-ExactII)
	# Printing out the results
	print "Step = "+str(2**N)+" Romberg = "+str(Romberg)+" Norm = "+str(Norm)
	pltN.append(N)
	pltNorm.append(Norm)
	# Recursive Steps
	Err = Norm 
	N = N + 1 
	
	
	
# We also can import Romberg from integrations:
print "The Results with Using Python Romberg Function for exp(-x**2)= "
Result = ((integrate.romberg(Func, -1, 1, tol=1e-06, rtol=1e-06,divmax=20, show=True,vec_func=True))/np.sqrt(2.0*np.pi))**2
print "The Final Answer Using Python Package for Romberg = " +  str(Result)

fig = plt.figure()
plt.title('Error of Romberg Integral Versus Log2 of Steps' )	
L1, = plt.plot(pltN,pltNorm,'--bo',label = "Error VS Steps")
plt.ylabel('Error')
plt.xlabel('Log2 of N')
plt.legend()
plt.grid(True)
plt.show()
	
	


