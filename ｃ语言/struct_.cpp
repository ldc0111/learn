/*************************************************************************
	> File Name: struct_.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月04日 星期四 10时26分19秒
 ************************************************************************/

#include<iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct test{
    char a;
    char b;
    char d;
    int c;
};
struct test1{
    short a;
    char b;
    int c;
    double e;
};
struct Number{
    int type;
    union{
        int num1;
        float num2;
    }N;
};

void print(Number * n){
    switch (n->type) {
        case 0: printf("%d\n", n->N.num1);break;
        case 1: printf("%f\n", n->N.num2);break;
}
}

void set(Number * n,int value){
    n->type = 0;
    n->N.num1 = value;
}
void set(Number * n,float value){
    n->type = 1;
    n->N.num2 = value;
}


int main(){
    srand(time(0));
    //struct test a;
    //struct test1 b;
    //printf("%p %p %p %p", &a.a, &a.b, &a.d, &a.c);
    //printf("%p %p %p", &b.a, &b.b, &b.c);
    #define max_n 20
    struct Number arr[max_n];
    for (int i = 0; i < max_n; i++){
        int op =rand() % 2;
        switch (op) {
            case 0:{
                int value = rand() % 100;
                set(arr + i, value);
            } break;   
            case 1:{
                float value = (1.0*(rand()%10000) / 10000) * 100;
                set(arr + i, value);
            }break;
        }
        print(arr + i);
    }

    arr[0].N.num2 = 1.0;
    printf("arr[0].N.num2 = %d\n", arr[0].N.num2);
    printf("arr[0].N.num1 = %d\n", arr[0].N.num1);
    printf("arr[0].N.num1 = %x\n", arr[0].N.num1);
    return 0;
}





