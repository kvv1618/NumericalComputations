#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include <time.h>

int main() {
    int N = 10000;  // Matrix size for large floating-point operations
    double *A = (double *) malloc(N * N * sizeof(double));
    double *B = (double *) malloc(N * N * sizeof(double));
    double *C = (double *) malloc(N * N * sizeof(double));

    // Initialize matrices with random values
    for (int i = 0; i < N * N; i++) {
        A[i] = (double) rand() / RAND_MAX;
        B[i] = (double) rand() / RAND_MAX;
        C[i] = 0.0;
    }

    // Start timer
    clock_t start = clock();

    // Perform matrix multiplication: C = A * B
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, A, N, B, N, 0.0, C, N);

    // End timer
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // Calculate FLOPS (2 * N^3 operations for matrix multiplication)
    double flops = (2.0 * N * N * N) / time_spent;

    printf("Performed %.0f floating-point operations in %.2f seconds\n", 2.0 * N * N * N, time_spent);
    printf("Estimated FLOPS: %.2e FLOPS\n", flops);

    free(A);
    free(B);
    free(C);

    return 0;
}
