#include <stdio.h>
long long paintWallCounts(int wallsize) {
    long long arr[3];
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 6;
    for (int i = 3; i <= wallsize; i++) {
        arr[i % 3] = arr[(i - 1) % 3] + 2 * arr[(i - 2) % 3];
    }
    return arr[wallsize % 3];
}
int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", paintWallCounts(n));
    return 0;
}