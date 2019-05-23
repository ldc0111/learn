#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            printf(j == n ? "%d\n":"%d ", i);
        }
    }

    return 0;
}