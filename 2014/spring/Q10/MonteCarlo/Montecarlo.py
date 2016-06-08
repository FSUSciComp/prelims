
# A.T. 3-June-2016
# Montecarlo.py
# A program to calculate integral ( e(-x^2)dx in -1 and 1) using Monte Carlo With N points
# Spring 2014 - Numerical Inegration - Q10 - Dr. Beerli

import numpy as np
import matplotlib.pyplot as plt


N=100000 # Number of Sample points
xi = np.random.uniform(-1, 1, N) # Uniform distribution
fi = np.exp(-xi**2) # Finding the value of F at sample points
dx = 2.0 / N # Defining the delta x
intg = np.sum(fi) * dx # Calculating the integral
	
StdInt = 2.0/np.sqrt(N) # Standard Deviation
I = (intg/np.sqrt(2*np.pi))**2 # The amount of Integral for e(-x**2 - Y**2)/2pi
	
print "The Result = " + str(I)
print "Standard Deviation = " + str(StdInt)


fig = plt.figure()
plt.title("Region" )	
L1, = plt.plot(xi,fi,'ro')
plt.ylabel('Y')
plt.xlabel('X')
plt.axis('on')
plt.grid(True)
plt.show()
