#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void root_cal_bisection(double root, double tolerance, double l, double r, int nu_iterations){
  double func_l = cos(l)-pow(l,3)+1, func_r = cos(r)-pow(r,3)+1;
  double m = (l+r)/2;
  double func_m = cos(m)-pow(m,3)+1;
  double abs_error = ((m - root) > 0) ? (m - root) : (root - m);

  while(abs_error>tolerance){
    if ((func_m*func_l)<0){
      r = m;
      func_r = func_m;
    }
    else{
        l = m;
        func_l = func_m;
    }
    m = (l+r)/2;
    nu_iterations++;
    func_m = cos(m)-pow(m,3)+1;

    abs_error = ((m - root) > 0) ? (m - root) : (root - m);
  }

  printf("Root calculated in Bisection method with tolerance %lf after %d iterations: %lf\n", tolerance, nu_iterations, m);
}

int main(){
    double tolerance=0.0125, root1=1.12656, abs_error=0;
    
    int nu_iterations = 1;

    root_cal_bisection(root1, tolerance, 0.1, 02, nu_iterations);
    return 0;
}