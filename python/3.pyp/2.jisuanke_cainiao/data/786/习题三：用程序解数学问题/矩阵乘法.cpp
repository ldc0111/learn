#include <stdio.h>

int main() {
    int matrix_a[10][10];
    int matrix_b[10][10];
    int m;
    int n;
    int matrix_c[10][10] = {0};
    scanf("%d%d",&m,&n);
    for (int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &matrix_a[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &matrix_b[i][j]);
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    
    for (int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            printf(j == (m - 1) ? "%d\n": "%d ", matrix_c[i][j]);
        }
    }
    return 0;
}