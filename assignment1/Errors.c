#include<stdio.h>
#include <stdlib.h>

int main(){

    double num = 0.1 , decimal_num;
    char binary_num[104];
    
    scanf("%s", binary_num);
    scanf("%lf", &decimal_num);

    printf("The binary equivalent of %0.1lf is: %s\n", num, binary_num);
    printf("The decimal equivalent of %s is: %lf\n", binary_num, decimal_num);

    printf("True value of the number in context is: %0.1lf\n", 0.1);
    printf("Approximate value of the number in context is: %lf\n", decimal_num);
    printf("Absolute error: %lf\n", (decimal_num- 0.1)<0 ? (-1.0)*(decimal_num- 0.1): (decimal_num- 0.1));
    printf("Relative error: %lf\n", ((decimal_num- 0.1)<0 ? (-1.0)*(decimal_num- 0.1): (decimal_num- 0.1))/0.1);

    return 0;
}