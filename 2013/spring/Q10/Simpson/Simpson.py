
# A.T. 3-June-2016
# Montecarlo.py
# A program to calculate integral using Simpson's rule
# Spring 2013 - Numerical Inegration - Q10 - Dr. Beerli

import numpy as np
import matplotlib.pyplot as plt

# Defining our functions
def F1(x):
	return np.exp(-0.5*x**2)
	
def F2(x):
	return np.exp(-0.1 * (x-3)**2)

	
# Main Loop
a = -5.0
b = 5.0
Exact = 27.1136
NN = 2**np.array([4,5,6,7,8,9,10])
I_Simpson = []
Error_Simpson = []
Error = []

for j in NN:
	# Initilizing to Zero
	temp1_odd = 0.0
	temp2_odd = 0.0
	temp1_even = 0.0
	temp2_even = 0.0
	Simp1 = 0
	Simp2 = 0
	# Calculating Odd Terms
	for i in range(1,j,2):
		temp1_odd += F1(a + i* (b-a)/j)
		temp2_odd += F2(a + i* (b-a)/j)	
	# Calculating Even Terms

	for k in range(2,j-1,2):
		temp1_even += F1(a + k* (b-a)/j)
		temp2_even += F2(a + k* (b-a)/j)
	# Calculating Integral

	Simp1 = ((b-a)/(3.0*j)) * (F1(a)+F1(b)+4.0*temp1_odd+2.0*temp1_even) 
	Simp2 = ((b-a)/(j*3.0)) * (F2(a)+F2(b)+4.0*temp2_odd+2.0*temp2_even)
	I_Simpson.append(Simp1**2 + Simp2**2)
	Error_Simpson.append((b-a)**5/(180.0 * j**4))
	Error.append(np.linalg.norm(Simp1**2 + Simp2**2 - Exact))

print "The Final Result = " + str(I_Simpson[-1])


# plotting

fig = plt.figure()
plt.title("Error : $L_2||Approx - Exact||$ vs N" )	
L1, = plt.loglog(NN,Error,'r--')
plt.ylabel('Error')
plt.xlabel('N')
plt.axis('on')
plt.grid(True)
plt.show()	

fig = plt.figure()
plt.title(r"Error: $(b-a)^5/(180  N^4)$ vs N" )	
L1, = plt.loglog(NN,Error_Simpson,'b--')
plt.ylabel('Error')
plt.xlabel('N')
plt.axis('on')
plt.grid(True)
plt.show()
	
