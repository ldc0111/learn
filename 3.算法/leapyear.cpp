/*************************************************************************
	> File Name: leapyear.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月30日 星期二 16时36分53秒
 ************************************************************************/

#include<iostream>
using namespace std;

#define swap(a,b){\
    __typeof(a) temp = a;\
    a = b; b = temp;\
}
#define MAX(a,b){\
    __typeof(a) aa = (a);\
    __typeof(b) bb = (b);\
    aa > bb ? aa : bb;\
}



int leapyear(int year){
    return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}
int gcd(int a,int b){
    return b == 0 ? a : gcd(b,a%b);
}
int lcm(int a,int b){
    return a * b /gcd(a,b);
}

/*
int main(){
    int year;
    while(scanf("%d", &year) != EOF){
        printf("%d\n",leapyear(year));
    }
}*/

int main(){
    int a,b;
    while(scanf("%d%d",&a,&b) != EOF){
        //printf("%d",gcd(a,b));
        swap(a,b);
        printf("%d %d",a,b);
    }
}
