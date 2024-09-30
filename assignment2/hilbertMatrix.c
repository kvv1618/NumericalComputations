#include<stdio.h>
#include<stdlib.h>
#include <lapacke.h>

int main(int argc, char *argv[]) {
    int n = (argc < 2) ? 5 : atoi(argv[1]);

    double hilbertMatrix[n][n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            hilbertMatrix[i][j] = 1.0 / (i + j + 1);
        }
    }

    printf("The Hilbert matrix of order %d is:\n", n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%f ", hilbertMatrix[i][j]);
        }
        printf("\n");
    }
    
    double hilbertMatrixColumnMajor[9*9];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            hilbertMatrixColumnMajor[j*n + i] = 1.0 / (i + j + 1);
        }
    }

    double singularValues[9], U[9*9], VT[9*9], work[9*9], wkopt;
    int info, lwork = -1, dimentions=9, ipiv[9];

    dgetrf_(&dimentions, &dimentions, hilbertMatrixColumnMajor, &dimentions, ipiv, &info);
    
    if (info == 0) {
        double rcond = 0.0;
        double anorm = dlange_("1", &dimentions, &dimentions, hilbertMatrixColumnMajor, &dimentions, work);
        int iwork[9];
        char norm = '1';
        dgecon_(&norm, &dimentions, hilbertMatrixColumnMajor, &dimentions, &anorm, &rcond, work, iwork, &info);
        if (info == 0) {
            printf("1 Norm Condition number of Hilbert matrix of order %d is: %lf\n", n, 1/rcond);
        }
        else {
            printf("Error in computing condition number\n");
        }
    }
    else {
        printf("Error in computing SVD\n");
    }

    return 0;
}