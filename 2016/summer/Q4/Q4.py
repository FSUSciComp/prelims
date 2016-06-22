
# A.T. 21-June-2016
# Q4.py
# a program to solve ellipses problem for Prelim Summer 2016
# Dr. Sachin

import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import solve
import math


np.random.seed(1367) # set the seed number to regenerate the data again

# Arrays for IN Region 
IN_X = [] 
IN_Y = []
# Arrays for OUT Region
OUT_X = []
OUT_Y = []
# Initiliaze the Numbers
N_IN = 0
N_OUT = 0
# Total number of darts
N= 20000
# Initial Angle of Rotation
aa = np.pi/3.
# Center of Ellipse 2
x0 = 0.1 * np.cos(aa)
y0 = 0.1 * np.sin(aa)

# Main Loop
for i in range(N):
	
	X = np.random.uniform(-3,3)
	Y = np.random.uniform(-3,3)
	
	
	# Montecarlo criteria
	# it should be inside the two Ellipses
	
	if (abs(((X-x0) * np.cos(aa) + (Y-y0)*np.sin(aa))**2/4. + ((X-x0)*np.sin(aa) - (Y-y0)*np.cos(aa))**2) <= 1.0) & (abs(X**2/4.0 + Y**2) <= 1.0):
		IN_X.append(X)
		IN_Y.append(Y)
		N_IN +=1
		
	else:
		OUT_X.append(X)
		OUT_Y.append(Y)
		N_OUT +=1
		
# Area is probability on In darts time the whole area which is 6 * 6
AREA = 36. * N_IN/N
print "AREA = " + str(AREA)

# Plotting
fig = plt.figure()
plt.title("Area = " + str(AREA) )	
L1, = plt.plot(IN_X,IN_Y,'go')
plt.ylabel('Y')
plt.xlabel('X')
plt.axis('on')
plt.grid(True)
plt.show()
