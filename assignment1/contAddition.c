#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    double num = argc > 1 ? atof(argv[1]) : 0.001, sum = 0.0;
    
    int numIterations = argc > 2 ? atoi(argv[2]) : 1000;
    for(int i=0;i<numIterations;i++){
        sum += num;
    }

    double trueValue = 1.0;

    printf("Approximate Value: %2.64g\n", sum);
    printf("Absolute Error: %2.64g\n", (trueValue - sum)<0 ? (-1.0)*(trueValue - sum): (trueValue - sum));
    printf("Relative Error: %2.64g\n", ((trueValue - sum)<0 ? (-1.0)*(trueValue - sum): (trueValue - sum))/trueValue);
     
    /* 
    Why does the computer differ from the true value?
    The computer uses binary representation to store the numbers. 
    The number 0.001 is not exactly representable in binary.
    The computer stores the number as 0.001000000000000000020816681711721685132943093776702880859375
    When we add 0.001 1000 times, the error accumulates and the number stored in the computer is different from the true value.
    */

    return 0;
}