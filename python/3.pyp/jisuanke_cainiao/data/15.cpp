#include <stdio.h>

int main() {
    int a[51],n;
    a[0] = 0;
    a[1] = 0;
    a[2] = 1;
    a[3] = 1;
    scanf("%d", &n);
    for(int i = 4; i <=n; i++){
        a[i]  = a[i - 2] + a[i - 3];
    }
    printf("%d", a[n]);
    return 0;
}