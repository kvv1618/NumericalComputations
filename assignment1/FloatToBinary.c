#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void wholeToBinary(int n, int precision){
    int binary[precision], i=0;
    while(n>0){
        binary[i] = n%2;
        i+=1;
        n = n/2;
    }
    for(int j=i-1; j>=0; j--){
        printf("%d", binary[j]);
    }
}

void DeciToBinary(double n, int precision){
    if (n>0){
        printf(".");
    }
    int p = precision;
    while(n>0 && p--){
        printf("%d", (int)(n*2));
        n = n*2 - (int)(n*2);
    }
    printf("\n");
}

void floatToBinary(int precision){
    double a=0,w=0,deci=0;
    /*
    Double Vs Float:
    A variable of type float only has 7 digits of precision whereas a variable of type double has 15 digits of precision.
    double precision numbers are represented by 64 bits, while float precision numbers are represented by 32 bits.
    */
    printf("Enter a decimal number with no more than 6 decimal digits: \n");
    scanf("%lf", &a);

    deci = modf(a, &w); // modf returns the fractional part of a in d upto six decimals and the integer part in w
    int intpart = (int)w;
    
    wholeToBinary(intpart, precision);
    DeciToBinary(deci, precision);
}

int main(int argc, char *argv[])
{
    int precision = argc > 1 ? atoi(argv[1]) : 52; 
    printf("Precision: %d\n", precision);
    floatToBinary(precision);
    return 0;

}