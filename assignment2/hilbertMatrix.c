#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    int n = (argc < 2) ? 5 : atoi(argv[1]);

    double hilbertMatrix[n][n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            hilbertMatrix[i][j] = 1.0 / (i + j + 1);
        }
    }

    printf("The Hilbert matrix of order 5 is:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%f ", hilbertMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}