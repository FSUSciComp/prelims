import numpy as np
import matplotlib.pyplot as plt
import warnings
warnings.filterwarnings("ignore")

def g(x):
    return ( np.exp(x) ) / ( np.sin(x)**3 + np.cos(x)**3 )

def cdiff_1(f, x, h):
    return ( f(x + h) - f(x - h) ) / (2*h)

def cdiff_2(f, x, h):
    return ( f(x - 2*h) - 8*f(x - h) + 8*f(x + h) - f(x + 2*h) ) / (12*h)

# The fucntion of interest
# ------------------------
x = np.linspace(0,2)
plt.plot(x, g(x))
plt.plot([1.0, 1.0], [0, g(1.0)], 'k--')
plt.plot(1.0, g(1.0), 'ro')
plt.show()

exact_gp = 1.64087713599607

x = 1.0
h = 0.01
h_c = h/2.0

gp_b_1 = cdiff_1(g, x, h)
print 'B 1 Error: ', abs(gp_b_1 - exact_gp)

gp_b_2 = cdiff_2(g, x, h)
print 'B 2 Error: ', abs(gp_b_2 - exact_gp)

gp_c_1 = cdiff_1(g, x, h_c)
print 'C 1 Error: ', abs(gp_c_1 - exact_gp)

# Richardson Extrapolation
gp_c_2 = gp_c_1  + (gp_c_1 - gp_b_1)/(3.0)
print 'C 2 Error: ', abs(gp_c_2 - exact_gp)
