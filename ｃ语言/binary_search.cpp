/*************************************************************************
	> File Name: binary_search.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月23日 星期日 10时41分54秒
 ************************************************************************/

#include<iostream>
using namespace std;

int binary_search(int (*arr)(int), int x, int n){
    int head = 0,tail = n - 1;
    while(head <= tail){
        int mid = (head + tail) >> 1;
        if(arr(mid) == x) return mid;
        else if (arr(mid) < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}



int main(){
    int arr[100];
    char *p1 = (char * )(arr + 1);
    char *p2 = (char * )(arr + 2);
    long long * p3 = (long long *)(arr + 1);
    p1[0] = 'a';
    p1[1] = 'b';
    p1[2] = 'c';
    p1[3] = 'd';
    for(int i = 0; i < 3; i++) p2[i] = p1[i];
    printf("p1 = %s, p1 = %lx\n", p1 ,*(long long*)p1);
    //printf("p3 = %ld",*p3);

    return 0;
}
/*
int main(){
    char arr[100];
    int *p1 = (int *)(arr + 1);
    int *p2 = (int *)(arr + 2);
    *p1 = 1;
    *p2 = 2;
    printf("*p1 = %d\n*p2 = %d\n", *p1, *p2);
}*/

/*
int main(){
    int ret;
    unsigned char * p = (unsigned char *)&ret;
    int a,b,c,d;
    scanf("%d%d%d%d",&a, &b, &d, &d);
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    //p[0] = d;
    //p[1] = c;
    //p[2] = b;
    //p[3] = a;
    //注意高对高，低对低
    printf("ret: %u\n", ret);
    return 0;
}*/
