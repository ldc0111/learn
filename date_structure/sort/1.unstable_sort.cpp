/*************************************************************************
	> File Name: 1.unstable_sort.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月27日 星期六 22时52分47秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



#define swap(a,b){\
    __typeof(a) temp;\
    temp = a; a = b; b = temp;\
}
void select_sort(int *,int );
void quick_sort(int *,int,int);



int main(){

    return 0;
}

void select_sort(int *num,int n){
    for(int i = 0; i < n - 1; i++){
        int ind = i;
        for(int j = i +1; j < n; j++){
            if(num[j] < num[ind]) ind = j;
        }
        swap(num[i], num[ind]);
    }
    return ;
}
void quick_sort(int *num,int l,int r){
    if(r - l < 1) return ;
    int x = l,y = r, z = num[l];
    while(x < y){
        while(x < y && num[y] >= z) --y;
        if(x < y) num[x] = num[y--];
        while(x < y && num[x] <= z) ++x;
        if(x < y) num[y] = num[x++];
    }
    num[x] = z;
    quick_sort(num,l,x - 1);
    quick_sort(num,x + 1,r);
    return ;
}
