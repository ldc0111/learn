#include <stdio.h>

int main() {
    int n = 10;
    int m;
    int numbers[10];
    int i, k;

    // 读入给定的数字
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    for(i = 0; i < n; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(numbers[j] < numbers[j + 1]){
                   k = numbers[j];
                   numbers[j] = numbers[j + 1];
                   numbers[j + 1] = k;              
            }
        }
    }

    for(i = 0; i < n; i++){
        printf(i == n - 1? "%d\n":"%d ", numbers[i]);
    }
    return 0;
}