/*************************************************************************
	> File Name: max.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月23日 星期日 11时59分24秒
 ************************************************************************/

#include<iostream>
using namespace std;


#define P(func) {\
    printf("%s = %d\n", #func, func); \
}

//#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define MAX(a,b) ({\
        __typeof(a) aa = (a);\
        __typeof(b) bb = (b);\
        aa > bb ? aa : bb;\
})


int main(){
    //P(MAX(2,3));
    //P(5 + MAX(2,3));
    //P(MAX(2,MAX(3,4)));
    //P(MAX(2,3 > 4 ? 3 : 4));
    int a = 7;
    P(MAX(a++,6));
    printf("a = %d\n", a);
    ( {int a = 3;});
    printf("a = %d\n",a);
    return 0;
}
