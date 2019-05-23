#include <stdio.h>

int search(int *data, int length, int value) {
    for(int i = 0; i < length; i++){
        if(data[i] == value){
            return i;
        }else if(data[i] > value){
            return i;
        }
    }
    return length - 1;
}

int main() {
    int n,k;
    scanf("%d", &n);
    int arr[105],brr[105];
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        int temp,time;
        scanf("%d", &temp);
        time = search(arr,n,temp);
        if(arr[time] == temp){
            printf("%d %d\n",time + 1,time);
        } else {
            printf("%d failed\n",time + 1);
        }
        time = 0;
    }
    return 0;
}