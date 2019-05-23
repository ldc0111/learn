#include <stdio.h>
#include <string.h>

int n = 1000000;
int mark[1000001];

int main() {
    int c, nn, mm;
    memset(mark, 0, sizeof(mark));
    mark[0] = 1;
    mark[1] = 1;
    scanf("%d %d", &nn, &mm);
    for (c = 2; c * c <= n; c++) {
         if(mark[c] != 1){
             for(int j = c; j <= n/c;j++){
                 mark[j*c] = 1;
             }
         }
    }
    
    for(int i = mm; i <= nn; i++){
        if(mark[i] != 1){
            printf("%d\n", i);
        }
    }
    return 0;
}