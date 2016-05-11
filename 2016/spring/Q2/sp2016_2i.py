#############################################################################80
###
### Spring 2016 Prelim Question 2 
### Serena Pham
###
#############################################################################80
import numpy as np

def f(x):
  f = np.sin(np.pi * x) # function
  return f
  
def exact():
  exact = 0.6366197723675814
  return exact
  
def trap(a, b, M):
  hs = np.linspace(a, b, M+1)
  h = hs[1] - hs[0]
  s = 0
  for i in range(hs.size-1):
    s += h/2 * ( f(hs[i]) + f(hs[i+1]) )
  return s
  
def rate(errors):
  rate = np.array([])
  for i in range(errors.size-1):
    rate = np.append(rate, np.log(errors[i] / errors[i+1]) / np.log(2))
  print rate
  return rate
  
#############################################################################80
### Call functions
#############################################################################80
a = 0
b = 1
Ms = np.array([1, 2, 4, 8, 16])
errors = np.array([])
for M in Ms:
  s = trap(a, b, M)
  errors = np.append(errors, np.abs(s - exact()))
rates = rate(errors)
