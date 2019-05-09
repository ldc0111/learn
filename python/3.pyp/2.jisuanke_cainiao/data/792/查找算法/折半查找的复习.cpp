#include <stdio.h>

int search(int *data, int length, int value) {
    int left = 0,right = length - 1;
    int time = 0;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(data[mid] == value) {
            printf("%d success\n",++time);
            return mid;
        } else if(data[mid] < value){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
        time++;
    }
    printf("%d failed\n", time);
    return -1;
}

int main() {
    int n,m;
    int arr[105],brr[105];
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &brr[i]);
    }
    for (int i = 0; i < m; i++) {
        search(arr,n,brr[i]);
    }
    
    
    return 0;
}