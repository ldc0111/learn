#include <stdio.h>

int find_max(int *data, int length) {
    int left = 0,right = length -  1;
    int time = 0;
    while(right - left >= 2){
        int m1 = left + (right - left)/3;
        int m2 = right - (right - left + 2)/3;
        if(data[m1] <= data[m2]) {
            right = m2;
        } else{
            left = m1  + 1;
        }
        time++;
    }
    if(data[left] <= data[right]){
        printf("%d %d",time, left);
        return left;
    } else {
        printf("%d %d",time, right);
        return right;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[105];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    find_max(arr,n);
    return 0;
}