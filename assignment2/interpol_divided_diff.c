#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    int n = (argc>1) ? atoi(argv[1]) : 5;
    double x[n], y[n], divided_diff[n][n];
    int term = 0;
    for(int i=0; i<n; i++){
        scanf("%lf %lf", &x[i], &y[i]);
    }
    int itr = n;
    for(int i=0;i<n;i++){
        divided_diff[i][0] = y[i];
    }
    for(int i=1;i<n;i++){
        if(divided_diff[0][i-1]!=0){
            term=i-1;
        }
        for(int j=0;j<itr-1;j++){
            divided_diff[j][i] = (divided_diff[j+1][i-1]-divided_diff[j][i-1])/(x[j+i]-x[j]);
        }
        itr--;
    }
    if(divided_diff[0][n-1]!=0){
        term=n-2;
    }
    printf("Given data is a polynomial of degree %d\n", term);
}