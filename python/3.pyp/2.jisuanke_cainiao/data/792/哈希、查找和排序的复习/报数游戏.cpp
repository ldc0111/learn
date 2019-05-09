#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search(int *arr,int n, int value){
    int head = 0,tail = n - 1;
    while(head < tail){
        int mid = (head + tail + 1) >> 1;
        //if(arr[mid] == value) return mid;
        if(arr[mid] > value) tail = mid - 1;
        else head = mid;
    }
    return head;
}


int main(){
    int n,m;
    int *arr = NULL;
    scanf("%d%d", &n ,&m);
    arr = (int *)calloc(sizeof(int), n + 1);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    for(int i = 0; i < m; i++) {
        int temp = 0;
        scanf("%d", &temp);
        printf("%d", arr[search(arr, n, temp)]);
        i != m - 1 && printf(" ");
    }
    printf("\n");
    return 0;
}