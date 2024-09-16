/* horner2d.c  psuedo Horners evaluation of 2D polynomial   */
/*             z = horner2d(npower, a[], x, y)              */ 
/*                                                            power a[n]
 * z = a0                  +                                     0    1
 *     a1 x    + a2 y      +                                     1    3
 *     a3 x^2  + a4 x y    + a5 y^2      +                       2    6
 *     a6 x^3  + a7 x^2 y  + a8 x y^2    + a9 Y^3                3   10
 *     a10 X^4 + a11 x^3 y + a12 x^2 y^2 + a13 x y^3 + a14 y^4   4   15
 *     ...                                                       5   21
 *     ...                                                       6   28
 */
/* assume heuristic, magnitude of x roughly magnitude of y */

#include "horner2d.h"

double horner2d(int npower, double a[], double x, double y)
{
  int nterm[11] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66}; /* dim of a[] */
                /* 0  1  2   3   4   5   6   7   8   9  10  npower */
  int ix[66] = { 0, 1, 0, 2, 1, 0, 3, 2, 1, 0, 4, 3, 2, 1, 0,
		 5, 4, 3, 2, 1, 0, 6, 5, 4, 3, 2, 1, 0,
                 7, 6, 5, 4, 3, 2, 1, 0, 8, 7, 6, 5, 4, 3, 2, 1, 0,
                 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
                 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  int iy[66] = { 0, 0, 1, 0, 1, 2, 0, 1, 2, 3, 0, 1, 2, 3, 4,
		 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 6,
                 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8,
                 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  double xp[11], yp[11];
  int n, i;
  double z = 0.0;

  n = nterm[npower]; /* minimum dimension of a[], n-1 max subscript in C */
  xp[0] = 1.0;
  yp[0] = 1.0;
  for(i=1; i<=npower; i++)
  {
    xp[i] = xp[i-1]*x;
    yp[i] = yp[i-1]*y;
  }
  for(i=n-1; i>0; i--) z += a[i]*xp[ix[i]]*yp[iy[i]];
  z += a[0];  
  return z;
}