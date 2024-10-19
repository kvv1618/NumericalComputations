#include<stdio.h>
#include<stdlib.h>
#include<lapacke.h>
#include<math.h>

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
}

void solve_X(int n_rows, int n_cols, double equation_A[n_rows][n_cols+1],double ans_array[n_cols]){
    for(int i=n_rows-1; i>=0; i--){
        double sum=0;
        for(int j=n_cols-1; j>i; j--){
            sum+=ans_array[j]*equation_A[i][j];
        }
        ans_array[i] = (equation_A[i][n_cols]-sum)/equation_A[i][i];
    }
    for(int i=n_cols-1; i>=0; i--){
        if(i==0){
            printf("%lf\n", ans_array[i]);
        }
        else{
            printf("%lf*x^%d + ", ans_array[i], i);
        }
    }
    
}

void partial_pivot(int n_rows, int n_cols, double matrix_GSE[n_rows][n_cols+1]){
    for(int i=0; i<n_rows; i++){
        int max_row = i, p_r=0, c_r=0;
        for(int j=i+1; j<n_rows; j++){
            if (matrix_GSE[j][i]<0){
                p_r = -1*matrix_GSE[j][i];
            }
            if (matrix_GSE[max_row][i]<0){
                c_r = -1*matrix_GSE[max_row][i];
            }
            if(p_r>c_r){
                max_row = j;
            }
        }
        if(max_row!=i){
            for(int j=0; j<n_cols; j++){
                double temp = matrix_GSE[i][j];
                matrix_GSE[i][j] = matrix_GSE[max_row][j];
                matrix_GSE[max_row][j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]){
    FILE *f = fopen("rocket.txt", "r");
    if(f==NULL){
        printf("Error in opening file\n");
    }
    char header[256];
    fgets(header, sizeof(header), f);

    char ch;
    int r=0, i=0;
    while((ch = fgetc(f)) != EOF){
        if(ch=='\n'){
            r+=1;
        }
    }
    fseek(f, 0, SEEK_SET);

    double velocity_y[r], acc_x[r], temp;

    fgets(header, sizeof(header), f);
    
    while(fscanf(f, "%lf,%lf,%lf,%lf,%lf,%lf,%lf",&temp,&temp,&velocity_y[i],&acc_x[i],&temp,&temp,&temp)!=EOF){
        i+=1;
    }
    fclose(f);
    printf("Polynomial fit between velocity_y and acc_x\n");

    int num_points = 5;
    double matrix_GSE[num_points][num_points+1], matix_GE[num_points][num_points+1];
    int row_c = 0;
    for(int i=0; i<r; i++){
        if(i%(r/num_points)==0){
            for(int j=0; j<num_points; j++){
                matrix_GSE[row_c][j] = pow(i, j);
                matix_GE[row_c][j] = pow(i, j);
            }
            matrix_GSE[row_c][num_points] = velocity_y[i];
            matix_GE[row_c][num_points] = velocity_y[i];
            row_c+=1;
        }
    }
    row_c-=1;

    LU_T_matrix(row_c, row_c, matix_GE);
    printf("Polynomial of degree %d by Gauss Elimination method\n", row_c-1);
    double ans_array_ge[row_c];
    solve_X(row_c, row_c, matix_GE, ans_array_ge);

    //Gauss Sidal Method
    partial_pivot(row_c, row_c, matrix_GSE);
    LU_T_matrix(row_c, row_c, matrix_GSE);
    printf("Polynomial of degree %d by Gauss Sidal method\n", row_c-1);
    double ans_array_gse[row_c];
    solve_X(row_c, row_c, matrix_GSE, ans_array_gse);
    
    printf("Error check at 30th data point\n");
    printf("True value: %lf\n", velocity_y[30]);
    printf("Relative absolute error\n");
    double sum_ge=0, sum_gse=0;
    for(int j=0; j<row_c; j++){
        sum_ge+=ans_array_ge[j]*pow(acc_x[30], j);
        sum_gse+=ans_array_gse[j]*pow(acc_x[30], j);
    }
    printf("in gauss Elimination: %lf\n", fabs(sum_ge-velocity_y[30])/velocity_y[30]);
    printf("in gauss Sidal: %lf\n", fabs(sum_gse-velocity_y[30])/velocity_y[30]);

    printf("\nRoot mean square error\n");
    double sum_ge_rms=0, sum_gse_rms=0;
    for(int i=0; i<r; i++){
        if(i%(r/30)){
            double sum_ge=0, sum_gse=0;
            for(int j=0; j<row_c; j++){
                sum_ge+=ans_array_ge[j]*pow(acc_x[i], j);
                sum_gse+=ans_array_gse[j]*pow(acc_x[i], j);
            }
            sum_ge_rms+=pow(sum_ge-velocity_y[i], 2);
            sum_gse_rms+=pow(sum_gse-velocity_y[i], 2);
        }
    }
    printf("for gauss Elimination: %lf\n", sqrt(sum_ge_rms/r));
    printf("for gauss Sidal: %lf\n", sqrt(sum_gse_rms/r));

    return 0;
}
