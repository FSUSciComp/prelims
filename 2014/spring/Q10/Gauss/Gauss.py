
# A.T. 3-June-2016
# Gauss.py
# A program to find the integral exp(-x**2) using Gauss and Kronrod
# Spring 2014 - Numerical Inegration - Q10 - Dr. Beerli

# Loading Packages

import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import solve
import math
from kronrod import kronrod
from kronrod_adjust import kronrod_adjust




# defining our function

def F(x):
	
	return np.exp(-x**2)
		
n =1	# Setting the Order
tol = 1e-6	# Tolerance
Err = 1  	# Error of the difference of Kronrod and Gauss


while Err > tol:
	abscissa = [] # an array for abscissa
	WK = [] 	  # an array for Kronrod Weights
	WG = []		  # an array for Gauss Weights
	# Calling Kronrod to get abscissa [0,1] and weights
	abscissa, WK, WG  = kronrod ( n, tol )
	abscissa_rev = abscissa[::-1] # make a reverse of abscissa
	# making the abscissa to [-1,1]
	for i in range(n):
		abscissa = np.append(abscissa,2 * abscissa_rev[0] - abscissa_rev[i+1])
	WG_ = []
	WK_ = []
	for i in range(n):
		WG_ = np.append(WG_,WG[i])
		WK_ = np.append(WK_,WK[i])
	WG_rev = WG_[::-1]
	WK_rev = WK_[::-1]
	for i in range(n):
		WK = np.append(WK,WK_rev[i])
		WG = np.append(WG,WG_rev[i])

	IK = 0.0 # Initilize Kronrod-Integral to Zero
	IG = 0.0 # Initilize Gauss-Integral to Zero
	
	# Main Loop for calculating Integral :: Wi * Xi 
	for i in range(len(abscissa)):
		IK += F(abscissa[i]) * WK[i]
		IG += F(abscissa[i])* WG[i]
		
	# Calculating the Whole integral with constants
	IG_Total = (IG/np.sqrt(2.0 * np.pi))**2
	IK_Total = (IK/np.sqrt(2.0 * np.pi))**2
	# Relative Error
	Err = abs(np.linalg.norm(IK - IG)/np.linalg.norm(IK)) 
	n += 1 # Increasing the number of points
	
print "The Integral Using Gauss rule :: I = " + str(IG_Total)
print "The Integral Using Gauss-Kronrod (N=6) :: I = " + str(IK_Total)
print "Relative Error of Integrals  = " + str(Err)

# Plotting
fig = plt.figure(1)
plt.title('Integrand' )	
L1, = plt.plot(abscissa,F(abscissa),'-b',label = "F(x)")
plt.ylabel('Y')
plt.xlabel('X')
plt.legend(loc = 0)
plt.grid(True)
plt.show()


fig = plt.figure(2)
plt.title('Nodes-Weights' )	
L2, = plt.plot(abscissa,WK,'r*',markersize=10,label = "Gauss-Kronrod")
L3, = plt.plot(abscissa,WG,'go',markersize=10,label = "Gauss")
plt.ylabel('Weights')
plt.xlabel('Abscissa')
plt.legend(loc = 0)
plt.grid(True)
plt.show()



