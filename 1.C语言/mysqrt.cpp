/*************************************************************************
	> File Name: mysqrt.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月13日 星期四 20时03分55秒
 ************************************************************************/

#include<iostream>
#include <time.h>
#include <math.h>
using namespace std;

#define TEST_TIME(func)({\
    int begin=clock();\
    double ret=func;\
    int end=clock();\
    printf("%lfms\m",(end-begin) * 1.0/ CLOCK_PER_SEC * 1000);\
})

double _sqrt(double x){
    double head = -100,tail = 100, mid;
    #define EPS 1e-7
    while(tail - head > EPS){
        mid=(head + tail)/2.0;
        if(mid * mid < x) head = mid;
        else tail= mid;
    }
    #undef EPS 
    return tail;
}
double f_func(double x,double n){
    return x * x - n;
}
double ff_func(double x){
    return 2 * x;
}

double newton(int n, double (*f)(double,double), double (*ff)(double)){
    double x = 1.0;
    #define EPS 1e-7

    while(fabs(f(x,n)) > EPS){
        x -= f(x,n)/ff(x);
    }
    #undef EPS
    return x;
}

int main(){
    int x;
    scanf("%d", &x);
    printf("%lf\n", _sqrt(x));
    printf("%lf\n", newton(x,f_func,ff_func));

    return 0;
}
