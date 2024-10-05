#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<lapacke.h>
#include<math.h>

void fit_check(int degree, double A[][degree+1], double XY[][2], int n){
    for(int i=0;i<n;i++){
        double y=0;
        for(int j=0;j<=degree;j++){
            y+=A[j][0]*pow(XY[i][0], j);
        }
        printf("f(%lf) = %lf\n", XY[i][0], y);
        
        if(fabs(y-XY[i][1])>0.0001){
            printf("The fit is incorrect\n");
            return;
        }
    }
    printf("The fit is perfect\n");
}

int main(int argc, char *argv[]) {
    int n = argc > 1 ? atoi(argv[1]) : 3;
    int degree = argc > 2 ? atoi(argv[2]) : 2;
    double XY[n][2], X[n][degree+1], Y[n][1], X_T[degree+1][n];

    char input[n*2], *token;
    for (int i=0; i<n; i++){
        int j=0;
        scanf(" %[^\n]", input);
        token = strtok(input, " ");

        while(token != NULL){
            XY[i][j] = atoi(token);
            token = strtok(NULL, " ");
            j++;
        }
    }

    for (int i=0; i<n; i++){
        X[i][0] = 1;
        X_T[0][i] = 1;
        for (int j=1; j<=degree; j++){
            X[i][j] = X[i][j-1] * XY[i][0];
            X_T[j][i] = X[i][j];
        }
        Y[i][0] = XY[i][1];
    }

    double X_T_X[degree+1][degree+1];
    for(int i=0;i<=degree;i++){
        for(int j=0;j<=degree;j++){
            X_T_X[i][j] = 0;
            for(int k=0;k<n;k++){
                X_T_X[i][j] += X_T[i][k] * X[k][j];
            }
        }
    }

    int ipiv[degree+1];
    int info;
    info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, degree+1, degree+1, X_T_X[0], degree+1, ipiv);
    if(info != 0){
        printf("dgetrf failed with error code %d\n", info);
        return 1;
    }

    info = LAPACKE_dgetri(LAPACK_ROW_MAJOR, degree+1, X_T_X[0], degree+1, ipiv);

    if(info != 0){
        printf("dgetri failed with error code %d\n", info);
        return 1;
    }

    double X_T_X_X_INV_X_T[degree+1][n];
    for(int i=0;i<=degree;i++){
        for(int j=0;j<n;j++){
            X_T_X_X_INV_X_T[i][j] = 0;
            for(int k=0;k<=degree;k++){
                X_T_X_X_INV_X_T[i][j] += X_T_X[i][k] * X_T[k][j];
            }
        }
    }

    double A[degree+1][degree+1];
    for(int i=0;i<=degree;i++){
        for(int j=0;j<=degree;j++){
            A[i][j] = 0;
            for(int k=0;k<n;k++){
                A[i][j] += X_T_X_X_INV_X_T[i][k] * Y[k][0];
            }
        }
    }

    printf("The polynomial of degree %d is:\n", degree);
    printf("f(x) = ");
    for(int i=0;i<=degree;i++){
        printf("%lf", A[i][0]);
        if(i>0){
            printf("(x^%d)", i);
        }
        if(i<degree){
            printf(" + ");
        }
    }
    printf("\n");

    fit_check(degree, A, XY, n);

    return 0;
}