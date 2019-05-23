/*************************************************************************
	> File Name: 5.bisearch.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月06日 星期二 19时27分14秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>


#define P(func){\
    printf("%s = %d\n",#func,func);\
}

///1 2 3 4 5 6
int binary_search(int *num,int n){
    int head = 0, tail = n - 1,mid;
    while(head <= tail) {
        mid = (head + tail) >> 1;
        if(num[mid] == n) return mid;
        if(num[mid] > n) tail = mid - 1;
        else head = mid + 1;
    }
    return -1;
}

/////111111100000000
int binary_search2(int *num, int n){
    int head = -1,tail = n - 1 , mid;
    while(head < tail){
        mid = (head + tail + 1) >> 1;
        if(num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}
///0000111111
int binary_search3(int *num,int n){
    int head = 0,tail = n,mid;
    while(head < tail){
        mid = (head + mid) >> 1;
        if(num[mid] == 1) tail = mid;
        else head = mid + 1;

    }
    return head == n ? -1:head;
}


int main(){
    int num[] = {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
    int num2[] = {1, 3, 5, 7, 9, 11,13, 17, 19, 23, 29};
    P(binary_search2(num,12));


    return 0;
}
