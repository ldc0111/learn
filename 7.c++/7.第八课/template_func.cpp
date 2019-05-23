/*************************************************************************
	> File Name: template_func.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 15时59分48秒
 ************************************************************************/

#include<iostream>
#include <string>
using namespace std;
#define swap(a,b) {\
    __typeof(a) temp = a;\
    a = b;\
    b = temp;\
}

template<typename T>
void myswap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}


class Test{
    public:
    Test(const Test &t) {

    }
    public:
    Test() {

    }
};

template <typename T>
void my_sort(T *a, int len) {
    for (int i = 0; i < len; i++){
        for (int j = i; j < len ;j++) {
            if (a[i] > a[j]) {
                myswap(a[i],a[j]);
            }
        }
    }
}
/*
int main() {
    string s1 = "srf", s2 = "cxh";
    int a = 10, b = 20;
    swap(a,b);
    printf("%d %d\n",a,b);
    swap(a,b);
    printf("%d %d\n",a,b);
    swap(s1,s2);
    cout << s1 << " " << s2 << endl;
    //Test t1, t2;
    myswap(t1,t2);
    return 0;
}*/

template<typename T>
void print(T *a, int len) {
    for (int i = 0; i < len ;i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
int main() {
    int a[5] = {2,3,1,6,3};
    double b[5] = {3,6,9,4,1};
    string s[5] = {"c", "java", "c++", "c#", "python"};
    print(a,5);
    my_sort(a,5);
    print(a,5);


    return 0;
}
