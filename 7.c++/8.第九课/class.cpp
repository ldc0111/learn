/*************************************************************************
	> File Name: class.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 09时35分15秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;


class A{
    private:
    int a;
    public:
    A(int v) {
        a = v;
    }
    /*
    A(const A &b){
        a = b.a;
    }*/
};


template<typename T>
class test{
    private:
        T a;
        int len;
    public:
        test(T v) : a(v) {
        }
        void swap(T &b) {
            T temp = a;
            a = b;
            b = temp;
        }
        T get() {
            return a;
        }
        T add(T b){
            T ret = a + b;
            return ret;
        }
        T sub(T b) {
            return a - b;
        }
};

string operator-(const string &s1, const string &s2) {
    return s1;
}
//类模板　１当再类外事项成语昂函数的时候，
//template<typename T>
//返回值 calssname<T>:: add(参数){函数体}
//2类魔棒声明和实现在供一个头问价中
int main() {
    test<int> t(2);
    string s1 = "wrf";
    test<string> t2(s1);
    cout << t2.get() << endl;
    cout << t2.add("ssss") << endl;
    cout << t2.sub("s") << endl;
    A aa(23);
    test<A> t3(aa);
    
    return 0;
}
