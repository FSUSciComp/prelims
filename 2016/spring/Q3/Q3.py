
# A.T. 7-May-2016
# Q3.py
# A program to use MC integration
# Q3 - Numerical Integration - Spring 2016

import numpy as np
import matplotlib.pyplot as plt

# definition of function
def fxy(x,y):
	return  (1.0/20216.34) * np.exp(-0.5*(x**2 * y**2 + x**2 + y**2 - 8*x - 8*y))
	

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
	

# Definin a function to the MAIN LOOP


# Preliminaries
def Main_Loop(nsteps):
	domain = np.array([[-np.inf,np.inf],[-np.inf,np.inf]]) # The whole space (-inf,inf )*(-inf,inf)
	#nsteps = 100000 # number of steps in the MCMC chain
	delta = 10. # delta for proposal 

	# initial state
	x = 0.0
	y = 0.0

	AccRatio = 0.0 # Initial value for Acceptance Ratio
	NumSucc = 0 # Number of successes
	# Arrays for recording all of the Successful points (X,Y)
	recX = []
	recY = [] 

	# Main Loop


	for iMCS in range(nsteps):
		# propose -> accept
	
		newx , newy = proposal(x , y , delta ,domain)
		accept , newx , newy = metropolis_accept(newx , newy , x , y)
	
		if accept:
			NumSucc += 1 
			x , y = newx , newy
			recX.append(x)
			recY.append(y)

		
	# Acceptance Ratio 	
	AccRatio = float(NumSucc)/float(nsteps)
	EX = np.mean(recX)
	EY = np.mean(recY)
	Error_X = np.std(recX)/np.sqrt(nsteps)
	Error_Y = np.std(recY)/np.sqrt(nsteps)
	
	return EX, EY ,Error_X, Error_Y, recX , recY	, NumSucc , AccRatio

# Calling the Function 
EX, EY , Error_X, Error_Y , recX , recY ,NumSucc , AccRatio= Main_Loop(100000)

print "Acceptance Ratio = " + str(AccRatio) 
print "Number of Successes = " +  str(NumSucc)
print "Expectation Value X = " + str(EX)
print "Expectation Value Y = " + str(EY)

#Plotting the number of points we used as darts		
fig = plt.figure()
plt.xlabel('X')
plt.ylabel('Y')
plt.title("Successful Sample Points")
plt.plot(recX,recY,'k.')
plt.show()


# For Finding the Accuracy 1e-3 we will have:

NN = 10**np.array([2,3,4,5,6,7])
Er_X = []
for j in NN:
	EX, EY , Error_X, Error_Y , recX , recY ,NumSucc , AccRatio= Main_Loop(j)
	Er_X.append(Error_X)

## Plotting Accuracy
fig = plt.figure()
plt.xlabel('Sample Points')
plt.ylabel('Error X')
plt.title("Error VS Sample Points")
plt.loglog(NN,Er_X,'o-')
plt.show()
