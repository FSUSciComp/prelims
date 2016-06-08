#!/usr/bin/env python

def kronrod ( n, tol ):

#*****************************************************************************80
#
## KRONROD adds N+1 points to an N-point Gaussian rule.
#
#  Discussion:
#
#    This subroutine calculates the abscissas and weights of the 2N+1
#    point Gauss Kronrod quadrature formula which is obtained from the
#    N point Gauss quadrature formula by the optimal addition of N+1 points.
#
#    The optimally added points are called Kronrod abscissas.  The
#    abscissas and weights for both the Gauss and Gauss Kronrod rules
#    are calculated for integration over the interval [-1,+1].
#
#    Since the quadrature formula is symmetric with respect to the origin,
#    only the nonnegative abscissas are calculated.
#
#    Note that the code published in Mathematics of Computation
#    omitted the definition of the variable which is here called COEF2.
#
#  Storage:
#
#    Given N, let M = ( N + 1 ) / 2.
#
#    The Gauss-Kronrod rule will include 2*N+1 points.  However, by symmetry,
#    only N + 1 of them need to be listed.
#
#    The arrays X, W1 and W2 contain the nonnegative abscissas in decreasing
#    order, and the weights of each abscissa in the Gauss-Kronrod and
#    Gauss rules respectively.  This means that about half the entries
#    in W2 are zero.
#
#    For instance, if N = 3, the output is:
#
#    I      X               W1              W2
#
#    1    0.960491        0.104656         0.000000
#    2    0.774597        0.268488         0.555556
#    3    0.434244        0.401397         0.000000
#    4    0.000000        0.450917         0.888889
#
#    and if N = 4, (notice that 0 is now a Kronrod abscissa)
#    the output is
#
#    I      X               W1              W2
#
#    1    0.976560        0.062977        0.000000
#    2    0.861136        0.170054        0.347855
#    3    0.640286        0.266798        0.000000
#    4    0.339981        0.326949        0.652145
#    5    0.000000        0.346443        0.000000
#
#  Licensing:
#
#    This code is distributed under the GNU LGPL license.
#
#  Modified:
#
#    30 April 2013
#
#  Author:
#
#    Original FORTRAN77 version by Robert Piessens, Maria Branders.
#    PYTHON version by John Burkardt.
#
#  Reference:
#
#    Robert Piessens, Maria Branders,
#    A Note on the Optimal Addition of Abscissas to Quadrature Formulas
#    of Gauss and Lobatto,
#    Mathematics of Computation,
#    Volume 28, Number 125, January 1974, pages 135-139.
#
#  Parameters:
#
#    Input, integer N, the order of the Gauss rule.
#
#    Input, real TOL, the requested absolute accuracy of the
#    abscissas.
#
#    Output, real X(N+1), the abscissas.
#
#    Output, real W1(N+1), the weights for the Gauss-Kronrod rule.
#
#    Output, real W2(N+1), the weights for the Gauss rule.
#
  from abwe1 import abwe1
  from abwe2 import abwe2
  from numpy import pi
  from numpy import zeros
  from math import floor
  from math import sin
  from math import sqrt

  tau_dim = ( n + 1 ) / 2
  tau_dim = int ( floor ( tau_dim ) )

  b = zeros ( ((n+1)/2)+1 )
  tau = zeros ( tau_dim )
  w1 = zeros ( n + 1 )
  w2 = zeros ( n + 1 )
  x = zeros ( n + 1 )

  m = int ( floor ( ( n + 1 ) / 2 ) )
  even = ( 2 * m == n )

  d = 2.0
  an = 0.0
  for k in range ( 1, n + 1 ):
    an = an + 1.0
    d = d * an / ( an + 0.5 )
#
#  Calculation of the Chebyshev coefficients of the orthogonal polynomial.
#  
  tau[1-1] = ( an + 2.0 ) / ( an + an + 3.0 )
  b[m-1] = tau[1-1] - 1.0
  ak = an

  for l in range ( 1, m ):
    ak = ak + 2.0
    tau[l+1-1] = ( ( ak - 1.0 ) * ak \
      - an * ( an + 1.0 ) ) * ( ak + 2.0 ) * tau[l-1] \
      / ( ak * ( ( ak + 3.0 ) * ( ak + 2.0 ) \
      - an * ( an + 1.0 ) ) )
    b[m-l-1] = tau[l+1-1]

    for ll in range ( 1, l + 1 ):
      b[m-l-1] = b[m-l-1] + tau[ll-1] * b[m-l+ll-1]

  b[m+1-1] = 1.0
#
#  Calculation of approximate values for the abscissas.
#
  bb = sin ( 0.5 * pi / ( an + an + 1.0 ) )
  x1 = sqrt ( 1.0 - bb * bb )
  s = 2.0 * bb * x1
  c = sqrt ( 1.0 - s * s )
  coef = 1.0 - ( 1.0 - 1.0 / an ) / ( 8.0 * an * an )
  xx = coef * x1
#
#  Coefficient needed for weights.
#
#  COEF2 = 2^(2*n+1) * n! * n! / (2n+1)!
#
  coef2 = 2.0 / ( 2 * n + 1 )
  for i in range ( 1, n + 1 ):
    coef2 = coef2 * 4.0 * i / ( n + i )
#
#  Calculation of the K-th abscissa (a Kronrod abscissa) and the
#  corresponding weight.
#
  for k in range ( 1, n + 1, 2 ):

    [ xx, w1[k-1] ] = abwe1 ( n, m, tol, coef2, even, b, xx )
    w2[k-1] = 0.0

    x[k-1] = xx
    y = x1
    x1 = y * c - bb * s
    bb = y * s + bb * c

    if ( k == n ):
      xx = 0.0
    else:
      xx = coef * x1
#
#  Calculation of the K+1 abscissa (a Gaussian abscissa) and the
#  corresponding weights.
#
    [ xx, w1[k+1-1], w2[k+1-1] ] = abwe2 ( n, m, tol, coef2, even, b, xx )

    x[k+1-1] = xx
    y = x1
    x1 = y * c - bb * s
    bb = y * s + bb * c
    xx = coef * x1
#
#  If N is even, we have one more Kronrod abscissa to compute,
#  namely the origin.
#
  if ( even ):
    xx = 0.0
    [ xx, w1[n+1-1] ] = abwe1 ( n, m, tol, coef2, even, b, xx )
    w2[n+1-1] = 0.0
    x[n+1-1] = xx

  return x, w1, w2
