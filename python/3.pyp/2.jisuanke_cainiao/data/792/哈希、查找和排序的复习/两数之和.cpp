#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define swap(a,b) {\
    __typeof(a) __temp = a;a = b; b = __temp;\
}


int main(){
    int a[1050] = {0},b[1050] = {0},c[1050] = {0},n,m;
    scanf("%d", &n);
    for(int i = 1; i <=n; i++){
        int temp = 0;
        scanf("%d", &temp);
        a[temp] = i;
        b[i] = temp;
    }
    scanf("%d",&m);
    for(int i = 1; i < n; i++) {
        for(int j = i + 1; j <= n; j++)
            if(b[i] + b[j] <= 1000) {
                 c[b[i] + b[j]] = i;
            }
    }
    printf("%d %d\n",c[m],a[m - b[c[m]]]);
    
    return 0;
}