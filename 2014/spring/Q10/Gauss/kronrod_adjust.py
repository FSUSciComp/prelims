#! /usr/bin/env python
#
def kronrod_adjust ( a, b, n, x, w1, w2 ):

#*****************************************************************************80
#
## KRONROD_ADJUST adjusts a Gauss-Kronrod rule from [-1,+1] to [A,B].
#
#  Licensing:
#
#    This code is distributed under the GNU LGPL license. 
#
#  Modified:
#
#    23 August 2015
#
#  Author:
#
#    John Burkardt
#
#  Parameters:
#
#    Input, real A, B, the endpoints of the new interval.
#
#    Input, integer N, the order of the rule.
#
#    Input/output, real X(N+1), W1(N+1), W2(N+1), the abscissas
#    and weights.
#
  for i in range ( n + 1 ):

    x[i] = ( ( 1.0 - x[i] ) * a   \
           + ( 1.0 + x[i] ) * b ) \
             / 2.0

    w1[i] = ( ( b - a ) / 2.0 ) * w1[i]
    w2[i] = ( ( b - a ) / 2.0 ) * w2[i]

  return
