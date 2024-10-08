/*
When we balance the weight of the ball and the buoyancy force; we end up with the equation;
1000*(x^3) - 3000(x^2) + 2 = 0; where x = h/r where h is the height of the ball in the water and r is the radius of the ball.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double func_eval(double x){
  return 1000*pow(x,3)-3000*pow(x,2)+2;
}

double func_eval_derivative(double x){
  return 3000*pow(x,2)-6000*x;
}

int main(){
    double relative_error_tolerance = 0.00625, x = 4, abs_relative_approx_error = relative_error_tolerance+1, next_x;

    while(abs_relative_approx_error>relative_error_tolerance){
        double func_x = func_eval(x), func_x_derivative = func_eval_derivative(x);
        if (func_x_derivative == 0){
            printf("Derivative is zero. Exiting\n");
            exit(0);
        }
        next_x = x - (func_x/func_x_derivative);
        abs_relative_approx_error = fabs((next_x-x)/next_x);
        x = next_x;
    }

    printf("Root calculated in Newton's method with relative error tolerance of %f is %f\n", relative_error_tolerance, x);

    printf("The height of the ball in the water is %f times the radius of the ball\n", x);
    printf("h=%f*r\n", x);
}