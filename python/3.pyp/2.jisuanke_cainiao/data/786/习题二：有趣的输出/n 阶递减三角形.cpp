#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = n - i + 1; j >= 1; j--) {
            printf(j == 1 ?"%d\n":"%d ", j);
        }
    }

    return 0;
}