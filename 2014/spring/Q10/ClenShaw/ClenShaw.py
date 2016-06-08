# A.T. 3-June-2016
# ClenShaw.py
# A program to find the integral exp(-x**2) using ClenShaw Curtis
# Spring 2014 - Numerical Inegration - Q10 - Dr. Beerli
# Loading Packages


import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import solve
import math
from scipy import integrate


def ClenShaw(func , a, b , N ) :
	 
	c = np.zeros([2 , 2*N -2])
	c[0][0] = 2.0
	c[1][1] = 1.0
	c[1][-1] = 1.0
	
	
	for i in np.arange(2 , N , 2):
		val = 2.0/(1 - pow(i,2))
		c[0][i] = val
		c[0][2*N - 2 -i] = val
		
		
	f = np.real(np.fft.ifft(c))
	w = f[0][:N] ; w[0] *= 0.5 ; w[-1] *= 0.5
	x = 0.5 * ((b+a) + (N-1)*(b-a) * f[1][:N])
	
	return np.dot(w,func(x)) * (b-a)
	
def F(x):
	return np.exp(-x**2)

I = (ClenShaw(F,-1,1,100)/np.sqrt(2*np.pi))**2
	
print "The Result using ClenShaw-Curtis Integration = " + str(I)


	
	
	
	
