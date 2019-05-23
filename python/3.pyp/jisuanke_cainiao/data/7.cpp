#include <stdio.h>
int main() {
    int n;
    scanf("%d",&n);
    for(int i = 2; i<= n; i+=(2 +(i%2 - 1))){
        int j;
        for(j = 2; j*j <= i;j++){
            if(i % j == 0){
                break;
            }
        }
        if(j*j > i){
            printf("%d\n",i);
        }
    }
    return 0;
}