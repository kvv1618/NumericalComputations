#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <lapacke.h>

void LU_T_matrix(int n_rows, int n_cols, double equation_A[n_rows][n_cols+1]){
    double lower_T_matrix[n_rows][n_cols];
    for(int i=0; i<(n_rows); i++){
        for(int j=0; j<(n_cols); j++){
            if (j>i){
                double ratio = equation_A[j][i]/equation_A[i][i];
                for(int k=0; k<n_cols+1; k++){
                    equation_A[j][k] = equation_A[j][k] - ratio*equation_A[i][k]; 
                }
                lower_T_matrix[j][i] = ratio;
            }
            else if(i==j){
                lower_T_matrix[i][j] = 1;
            }
            else{
                lower_T_matrix[j][i] = 0;
            }
        }
    }
    double det = 1;
    printf("Upper Triangular Matrix\n");
    for(int i=0; i<n_rows; i++){
        for(int j=0; j<n_cols; j++){
            if(i==j){
                det*=equation_A[i][j];
            }
            printf("%lf ", equation_A[i][j]);
        }
        printf("\n");
    }
    printf("Lower Triangular Matrix\n");
    for(int i=0; i<n_rows; i++){
        for(int j=0; j<n_cols; j++){
            printf("%lf", lower_T_matrix[i][j]);
        }
        printf("\n");
    }
    printf("Determinant of the matrix: %lf\n", det);
}

void solve_X(int n_rows, int n_cols, double equation_A[n_rows][n_cols+1]){
    printf("Values in X\n");
    double *val_array = (double *)malloc(n_cols * sizeof(int));;
    for(int i=n_rows-1; i>=0; i--){
        double sum=0;
        for(int j=n_cols-1; j>i; j--){
            sum+=val_array[j]*equation_A[i][j];
        }
        val_array[i] = (equation_A[i][n_cols]-sum)/equation_A[i][i];
    }
    for(int i=0; i<n_cols; i++){
        printf("%lf\n", val_array[i]);
    }
}

int main(int argc, char *argv[]){
    int n_rows = argc > 1 ? atoi(argv[1]) : 3, n_cols = argc > 2 ? atoi(argv[2]) : 3;
    double B[n_rows];
    for(int i=0; i<n_rows; i++){
        scanf("%lf", &B[i]);
    }
    printf("Values in B\n");
    for(int i=0; i<n_rows; i++){
        printf("%lf\n", B[i]);
    }
    double A[n_rows * n_cols],equation_A[n_rows][n_cols+1];

    char input[n_cols*2], *token;    
    for (int i=0; i<n_rows; i++){
        int j = 0;
        scanf(" %[^\n]", input);
        token = strtok(input, " ");

        // Loop through the tokens and print each one
        while (token != NULL) {
            equation_A[i][j] = atof(token);
            A[j*n_rows+i] = atof(token);
            j+=1;
            token = strtok(NULL, " ");  // Get the next token
        }
    }

    for(int i=0; i<n_rows; i++){
        equation_A[i][n_cols] = B[i];
    }
    printf("Values in equation_A\n");
    for(int i=0; i<n_rows; i++){
        for(int j=0; j<n_cols; j++){
            printf("%lf ", equation_A[i][j]);
        }
        printf("\n");
    }
    
    LU_T_matrix(n_rows, n_cols, equation_A);
    solve_X(n_rows, n_cols, equation_A);

    int nhrs = 1, ipiv[n_rows], info;

    dgesv_(&n_rows, &nhrs, A, &n_rows, ipiv, B, &n_cols, &info);

    if(info == 0){
        printf("Solution using dgesv from LAPACK\n");
        for(int i=0; i<n_rows; i++){
            printf("%lf\n", B[i]);
        }
    }
    else{
        printf("Solution not found\n");
    }
    
    double rcond = 0.0, work[4*n_rows], anorm=15;
    int iwork[n_rows];
    char norm = '1';

    dgecon_(&norm, &n_rows, A, &n_rows, &anorm, &rcond, work, iwork, &info);

    if(info == 0){
        printf("1 Norm Condition number of the matrix: %lf\n", 1/rcond);
    }
    else{
        printf("Condition number not found\n");
    }

    return 0;
}