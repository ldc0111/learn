/*************************************************************************
	> File Name: pp.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月04日 星期四 15时37分15秒
 ************************************************************************/

#include<iostream>
#include <inttypes.h>
using namespace std;


int add(int a,int b){
    return a+b;
}
//1
//typedef int (*func)();


//2
typedef int (*func)(int,int);


int main(){
    //1
    //func func_a = (func)add;
    //printf("%d\n", func_a(5,5));
    //2
    //func func_b = add;
    //printf("%d",func_b(3,5));
    int (*func)(int,int) = add;
    printf("%d\n", func(5,5));
    
    return 0;
}
