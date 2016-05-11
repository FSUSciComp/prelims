import numpy as np
from sp2016_2i import f, exact, trap, rate

a = 0
b = 1
Ms = np.array([1, 2, 4, 8, 16])
Ms_2 = Ms[:] * 2
errors = np.array([])
for i in range(Ms_2.size):
  s1 = trap(a, b, Ms[i])
  s2 = trap(a, b, Ms_2[i])
  s = 4.0*(s2 - 1.0/4.0 * s1)/3.0
  errors = np.append(errors, np.abs(s - exact()))
rates = rate(errors)