#include<stdio.h>
#include<math.h>

void binaryToBase10(){
    char binary[104];
    int i=0;
    double intPart=0;

    printf("Enter a binary number: \n");
    scanf("%s", binary);
    
    while(binary[i]!='\0' && binary[i]!='.'){
        i+=1;
    }

    for (int j=0; j<i; j++){
        intPart += (((int)binary[j]-48)==1 ? pow(2, i-j-1): 0);
    }

    double deciPart=0;
    for (int j=i+1; binary[j]!='\0'; j++){
        deciPart += ((int)binary[j]-48==1 ? 1/pow(2, j-i-1): 0);
    }

    printf("The decimal equivalent is: \n%lf\n", intPart+deciPart);
}

int main()
{
    
    binaryToBase10();

    return 0;
}