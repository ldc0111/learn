#include <stdio.h>

int main() {
    int matrix[3][3];
    int i;
    int j;
    int *p = &matrix[0][0];
    for (int i = 0; i < 9; i++) {
        scanf("%d",p+i);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(j == 2 ? "%d\n":"%d ", matrix[2 - j][i]);       
        }
    }
    return 0;
}