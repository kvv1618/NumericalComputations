/* horner2d.h  psuedo Horners evaluation of 2D polynomial          */
/* assume heuristic, magnitude of x roughly magnitude of y         */
/* npower     0  1  2   3   4   5   6   7   8   9   10   10 is max */
/* coef a[ ]  1  3  6  10  15  21  28  36  45  55   66             */
/* unused coeficients in a[] must be 0.0                           */

#ifndef HORNER2D_H 
#define HORNER2D_H

double horner2d(int npower, double a[], double x, double y);

#endif