/*
polynomial in consideration: 0.000025*x^4 + -0.004142*x^3 + 0.248112*x^2 + -8.471496*x^1 + 192.171215
derivative of the polynomial: 0.0001*x^3 + -0.012426*x^2 + 0.496224*x^1 + -8.471496
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double func_eval(double x){
    return 0.000025*pow(x,4) - 0.004142*pow(x,3) + 0.248112*pow(x,2) - 8.471496*x + 192;
}

void root_cal_bisection(double root, double tolerance, double l, double r, int nu_iterations){
    printf("Bisection method\n");
    double func_l = func_eval(l), func_r = func_eval(r);
    double m = (l+r)/2;
    double func_m = func_eval(m);
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
        func_m = func_eval(m);
        if(fabs(func_m)<0.5e-8){
            break;
        }

        abs_error = ((m - root) > 0) ? (m - root) : (root - m);
        printf("Absolute relative error: %.7g at iteration %d\n", abs_error/root, nu_iterations);
    }

    printf("Root calculated with tolerance %0.7g after %d iterations: %lf\n", tolerance, nu_iterations, m);
}

double func_eval_derivative(double x){
    return 0.0001*pow(x,3) - 0.012426*pow(x,2) + 0.496224*x - 8.471496;
}

void root_cal_newton(double root, double tolerance, double m, int nu_iterations){
  printf("Netwon's method\n");
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
    if(fabs(func_m)<0.5e-8){
        break;
    }
    func_m_derivative = func_eval_derivative(m);

    abs_error = ((m - root) > 0) ? (m - root) : (root - m);
    printf("Absolute elative error: %.7g at iteration %d\n", abs_error/root, nu_iterations);
  }

  printf("Root calculated for x with tolerance %.7g after %d iterations: %lf\n", tolerance, nu_iterations, m);
}

int main(int argc, char *argv){
    double root = 63.92303, tolerance = 0.0005;
    root_cal_newton(root, tolerance, 30, 0);
    root_cal_bisection(root, tolerance, 20, 80, 0);
    return 0;
}
