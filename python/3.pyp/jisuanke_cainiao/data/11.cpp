#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++){
            printf(j == n ? "%d*%d=%d\n" : "%d*%d=%d\t", i, j, i * j);
        }
    }
    return 0;
}