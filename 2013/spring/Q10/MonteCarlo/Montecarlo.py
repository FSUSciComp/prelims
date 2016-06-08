
# A.T. 3-June-2016
# Montecarlo.py
# A program to calculate integral using Monte Carlo With N points
# Spring 2013 - Numerical Inegration - Q10 - Dr. Beerli

import numpy as np
import matplotlib.pyplot as plt

def I1(N):
	xi = np.random.uniform(-5, 5, N)
	fi = np.exp(-0.5*xi**2)
	dx = 10.0 / N
	intg = np.sum(fi) * dx
	
	#StdInt = 10.0/np.sqrt(N)
	return intg
	
def I2(N):
	xi = np.random.uniform(-5, 5, N)
	fi = np.exp(-0.1 * (xi-3)**2)
	dx = 10.0 / N
	intg = np.sum(fi) * dx
	return intg
	
# Main Loop

Exact = 27.1136
Error = [] 
II = [] # Total integral result :: I1**2 + I2**2
approx = 0	
NN = 2**np.array([4,5,6,7,8,9,10])
for i in NN:
	approx =  I1(i)**2 + I2(i)**2
	II.append( approx)
	Error.append(np.linalg.norm(approx-Exact))

print "The Final Result with 1024 darts = " + str(II[-1])
# plotting



fig = plt.figure()
plt.title("Error vs N" )	
L1, = plt.plot(NN,Error,'r--')
plt.ylabel('Error')
plt.xlabel('N')
plt.axis('on')
plt.grid(True)
plt.show()	

fig = plt.figure()
plt.title("Error vs N" )	
L1, = plt.loglog(NN,Error,'b--')
plt.ylabel('Error')
plt.xlabel('N')
plt.axis('on')
plt.grid(True)
plt.show()
	
