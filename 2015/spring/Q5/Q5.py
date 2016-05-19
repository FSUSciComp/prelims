# A.T. 18-May-2016
# Q5.py
# Q5 - Spring 2015

import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import solve
import math
from scipy import integrate

# I have used GREEN's Theorem 
def Func(t):
	X = 16 * (np.sin(t))**3
	Y = 13* np.cos(t) - 5* np.cos(2*t) -2* np.cos(3*t) - np.cos(4*t)
	return X , Y
	
# AREA = Integral ( X dY)
def Area_Func(t):

	return 48 * (np.sin(t))**2 *np.cos(t)*( 13* np.cos(t) - 5* np.cos(2*t) -2* np.cos(3*t) - np.cos(4*t))
# X_cm = 1/Area  * Integral ( 0.5 * X * X * dY) 
def Xcm_Func(t):

	return 0.5*(16 * (np.sin(t))**3 )**2* (-13*np.sin(t) +10*np.sin(2*t) + 6*np.sin(3*t) + 4*np.sin(4*t))
# Y_cm = 1/Area  * Integral ( 0.5 * Y * Y dX )
def Ycm_Func(t):
	return 0.5 * 48 * (np.sin(t))**2 *np.cos(t)*( 13* np.cos(t) - 5* np.cos(2*t) -2* np.cos(3*t) - np.cos(4*t))**2


# X_Gyration = 1/Area * Integral ( X-Xcm)**2 over Area
def Xg_Func(t):
	return (-1./3.) * (((16 * (np.sin(t))**3) - 2.63488313796e-16 )**3 )*(-13*np.sin(t) +10*np.sin(2*t) + 6*np.sin(3*t) + 4*np.sin(4*t))


# Y_Gyration = 1/Area * Integral ( Y-Ycm)**2 over Area
def Yg_Func(t):
	return (1./3.) * (((13* np.cos(t) - 5* np.cos(2*t) -2* np.cos(3*t) - np.cos(4*t)) - 0.833333333333  )**3 )* 48 * (np.sin(t))**2 *np.cos(t)

t = np.linspace(0,2 * np.pi, 100)

X = []
Y = []
X , Y = Func(t)

Area = integrate.quad(Area_Func, 0, 2*np.pi)
I_X_cm = integrate.quad(Xcm_Func, 0, 2*np.pi)
I_Y_cm = integrate.quad(Ycm_Func, 0, 2*np.pi)
X_cm = I_X_cm[0]/Area[0]
Y_cm = I_Y_cm[0]/Area[0]
I_Xg = integrate.quad(Xg_Func, 0, 2*np.pi)
I_Yg = integrate.quad(Yg_Func, 0, 2*np.pi)
R_Gyration = (I_Xg[0] + I_Yg[0])/Area[0]


print "The Area = " + str(Area[0])
print "The X_cm = " + str(X_cm)
print "The Y_cm = " + str(Y_cm)
print "The R_G = " + str(R_Gyration)


fig = plt.figure()
plt.title("Heart" )	
L1, = plt.plot(X,Y,'ro')
plt.ylabel('Y')
plt.xlabel('X')
plt.axis('on')
plt.grid(True)
plt.show()
