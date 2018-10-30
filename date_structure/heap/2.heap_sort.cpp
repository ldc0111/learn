/*************************************************************************
	> File Name: 2.heap_sort.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月30日 星期二 20时28分04秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


#define swap(a,b) {\
    __typeof(a)  __temp = a; \
    a = b; b = __temp;\
}

void heap_sort(int *arr, int n){
    int *p = arr - 1;
    for(int i = 2; i <= n; i++){
        int ind = i;
        while(ind > 1){
            if(p[ind] <= p[ind >> 1]) break;
            swap(p[ind], p[ind >> 1]);
            ind >>= 1;
        }
    }
    for(int i = n; i > 1; i--){
        swap(p[i], p[1]);
        int ind = 1;
        while((ind << 1) <= i - 1){
            int temp = ind;
            if(p[temp] < p[ind << 1]) temp = ind << 1;
            if((ind << 1 | 1) <= i - 1 && p[temp] < p[ind << 1|1]) temp = ind << 1 | 1;
            if(temp == ind) break;
            swap(p[temp],p[ind]);
            ind = temp;
        }
    }
    return ;
}

void output(int *num, int n){
    printf("ARR = [");
    for(int i = 0; i < n; i++){
        printf(" %d", num[i]);
        i == n -1 && printf(" ]\n");

    }
    return ;
}




int main(){
    srand(time(0));
    #define MAX_N 20
    int arr[MAX_N];
    for(int i = 0; i < MAX_N; i++) arr[i] = rand() % 100;
    output(arr, 20);
    heap_sort(arr,20);
    output(arr,20);

    return  0;
}
