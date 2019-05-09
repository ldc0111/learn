#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int n,k;
    scanf("%d", &n);
    int *a = (int *)calloc(sizeof(int),(n + 2));
    k = n;
    while(n--){
        int temp;
        scanf("%d",&temp);
        if(temp > 0){
            a[temp] = 1;
        }
    }
    for(int i = 1; i <= k + 1; i++){
        if(a[i] == 0){
            printf("%d\n", i);
            break;
        }
    }
    
    return 0;
}