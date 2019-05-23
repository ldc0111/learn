#include <stdio.h>

void swap(int *a,int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}


int main() {
    int matrix[100][100];
    int m;
    int n;
    int t;
    scanf("%d %d",&n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    scanf("%d", &t);
    if (!t) {
         for (int i = 1; i <= n/2; i++) {
            for (int j = 1; j <= m; j++) {
                swap(&matrix[i][j], &matrix[n - i + 1][j]);
            }
        }       
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m/2; j++) {
                swap(&matrix[i][j], &matrix[i][m + 1 - j]);
            }
        }        
    }
     for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf(j == m? "%d\n" : "%d ", matrix[i][j]);
        }
    }


    return 0;
}