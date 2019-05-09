#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define swap(a,b){\
  __typeof(a) __temp = a; a = b; b = __temp;\
}

void sort(int a[],int l,int r){
    if(r <= l) return ;
    int x = l,y = r,z = a[l];
    while(x < y){
        while(x < y && a[y] >= z) y--;
        if(x < y) a[x++] = a[y];
        while(x < y && a[x] <= z) x++;
        if(x < y) a[y--] = a[x];
    }
    a[x] = z;
    sort(a,l,x - 1);
    sort(a,x + 1,r);
    return ;
}



int search(int *arr,int n, int value){
    int head = 0,tail = n - 1;
    while(head < tail){
        int mid = (head + tail + 1) >> 1;
        if(arr[mid] == value) return mid;
        else if(arr[mid] > value) tail = mid - 1;
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
    sort(arr,0,n - 1);
    //for(int i = 0; i < n; i++){
    //    printf("%d ",arr[i]);
    //}
    
    for(int i = 0; i < m; i++) {
        int temp = 0;
        scanf("%d", &temp);
        printf("%d", arr[search(arr, n, temp)]);
        i != m - 1 && printf(" ");
    }
    printf("\n");
    return 0;
}