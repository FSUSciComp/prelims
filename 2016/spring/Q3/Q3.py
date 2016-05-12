# A.T. 7-May-2016
# Q3.py
# A program to use MC integration
# Q3 - Numerical Integration - Spring 2016

import numpy as np
import matplotlib.pyplot as plt

# definition of function
def fxy(x,y):
	return x * (1.0/20216.34) * np.exp(-0.5*(x**2 * y**2 + x**2 + y**2 - 8*x - 8*y))
	

# proposal Function
def proposal(x , y , delta , domain):
	newx = x + delta * (2.0 * np.random.rand() - 1.0)
	newy = y + delta * (2.0 * np.random.rand() - 1.0)
	
	# if point inside the domain propose:
	if (domain[0][0] < newx < domain[0][1]) and (domain[1][0] <newy<domain[1][1]):
		return newx , newy
		
	else: # recursion
		proposal(x , y ,delta, domain)
		
# Acceptance Function

def metropolis_accept(newx , newy, oldx, oldy):
	numer = fxy(newx , newy)
	denom = fxy(oldx , oldy)
	
	if np.random.rand() < (numer)/(denom) :
		accept = True
		x , y = newx , newy
	else:
		accept = False
		x , y = oldx , oldy
		
	return accept , x ,y
	

# Preliminaries

domain = np.array([[-np.inf,np.inf],[-np.inf,np.inf]]) # The whole space (-inf,inf )*(-inf,inf)
nsteps = 100000 # number of steps in the MCMC chain
delta = 10. # delta for proposal 
thin = 10 # save every 10th point

# initial state
x = 0.0
y = 0.0

AccRatio = 0.0 # Initial value for Acceptance Ratio
NumSucc = 0 # Number of successes
recz = np.zeros((nsteps/thin,2)) # record of points sampled after thining

# Main Loop


for iMCS in range(nsteps):
	# propose -> accept
	
	newx , newy = proposal(x , y , delta ,domain)
	accept , newx , newy = metropolis_accept(newx , newy , x , y)
	
	if accept:
		NumSucc += 1 
		x , y = newx , newy
		
	if (iMCS % thin) == 0:# Record
		recz[iMCS/thin] = [x , y]
		
# Acceptance Ratio 	
AccRatio = float(NumSucc)/float(nsteps)
	
print "Acceptance Ratio = " + str(AccRatio) 
print "Number of Successes = " +  str(NumSucc)


# Plotting the number of points we used as darts		
fig = plt.figure()
plt.plot(recz[:,0],recz[:,1],'k.')
plt.show()
