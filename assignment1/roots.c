#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void root_cal_bisection(double root, double tolerance, double l, double r, int nu_iterations){
  double func_l = pow(l,2)-0.8*l+0.15, func_r = pow(r,2)-0.8*r+0.15;
  double m = (l+r)/2;
  double func_m = pow(m,2)-0.8*m+0.15;
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
    func_m = pow(m,2)-0.8*m+0.15;

    abs_error = ((m - root) > 0) ? (m - root) : (root - m);
  }

  printf("Root calculated in Bisection method with tolerance %lf after %d iterations: %lf\n", tolerance, nu_iterations, m);
}

double func_eval(double x){
  return pow(x,2)-0.8*x+0.15;
}

double func_eval_derivative(double x){
  return 2*x-0.8;
}

void root_cal_newton(double root, double tolerance, double m, int nu_iterations){
  double abs_error = ((m - root) > 0) ? (m - root) : (root - m);
  double func_m = func_eval(m);
  double func_m_derivative = func_eval_derivative(m);

  while(abs_error>tolerance){
    if (func_m_derivative == 0){
      printf("Derivative is zero. Exiting\n");
      exit(0);
    }
    m = m - (func_m/func_m_derivative);
    nu_iterations++;
    func_m = func_eval(m);
    func_m_derivative = func_eval_derivative(m);

    abs_error = ((m - root) > 0) ? (m - root) : (root - m);
  }

  printf("Root calculated in Newton's method with tolerance %lf after %d iterations: %lf\n", tolerance, nu_iterations, m);
}

int main()
{
  double tolerance=0.0125, root1=0.3, root2=0.5, abs_error=0;
  
  int nu_iterations = 1;

  root_cal_bisection(root1, tolerance, 0.1, 0.4, nu_iterations);
  root_cal_bisection(root2, tolerance, 0.4, 1, nu_iterations);
  printf("\n");
  root_cal_newton(root1, tolerance, 0.1, nu_iterations);
  root_cal_newton(root2, tolerance, 1, nu_iterations);
  return 0;
}