/*************************************************************************
	> File Name: template_class.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 10时41分22秒
 ************************************************************************/

#include<iostream>
using namespace std;
template<typename T1, typename T2>
class Test{
    public:
    void add(T1 a, T2 b) {

    }
};
//类模板
//特殊类型


//部分特化
template<typename T>
class Test<T,T> {
    public:
    void add(T a,T b){
        cout << "void add(T a, T b)" << endl;
    }
    void print() {
        cout << endl;
    }
};

//完全特化
template<>
class Test<int , int>{
    private:
    public:
    void add(int a, int b) {
        cout << "void add(int a, int b)" << endl;
        cout << "ERRO!" << endl;
    }
};

template<typename T>
class Test<T* , T*>{
    private:
    public:
    void add(T *a, T *b) {
        cout << "void add(T *a, T* b)" << endl;
        cout << "ERRO!" << endl;
    }
};
template<typename T>
class Test<T, int>{
    private:
    public:
    void add(T a, int b) {
        cout << "void add(T a, int b)" << endl;
        cout << "ERRO!" << endl;
    }
};
//类模板 1,可以有多个类型参数
//      2，特化类模板分开实现
//      3，特化的类模板，使用方式都是一样的，使用方法都是一样的，必须显示指定参数的类型
//      有多个特化的模板，根据不同的参数类型取选择不同的特化
//
//      函数模板也支持特化，只支持完全特化
//      完全特化，完全显示指定出参数类型
//      不完全指定参数类型，用特定规则取约束类型参数

template <typename T>
bool equal(T a, T b){
    cout << "template <typename T>" << endl;
    return a == b;
}

template <> 
bool equal<double> (double a, double b) {
    cout << "template <>" << endl;
    const double x = 0.0000001;
    double ret = a - b;
    return (ret > -x && ret < x);
}

/*
int main() {
    Test<int,double> t;
    t.add(3, 3.9);
    cout << equal(1,2) << endl;
    cout << equal(2.2, 1.3) << endl;
    return 0;
}*/
/*
 * 泛型编程:数据类型
 *          与数据操作分开
 *c++     1。模板函数
 *        2。模板类
 *        template 告诉编译器我要进行模板编程了
 *        typename T 模板类型
 *        跟函数类型关的操作就是重载
 *        模板模板这块
 *        特化，部分特化,完全特化
*/




//模板参数可以是数值类型的参数
template<typename T,int N>
void fun(){
    T sum = 0;
    for (int i  = 0; i <= N; i++) {
        sum += i;
    }
    cout << sum << endl;
    return ;
};
//1，这个数值类型的参数不能用变量，不能用浮点类型，类类型
//

template<typename T, int N>
class people{
    private:
        T a[N];
    public:
    people() {
        for (int i = 0; i < N; i++) {
            a[i] = i + 1;
        }
    }
    void print(){
        for (int i = 0; i < N; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
};

/*

int main() {
    Test<int, float> t1;
    t1.add(2,4.3);
    Test<int, int> t2;
    t2.add(1,2);
    Test<int*,int* > t3;
    int a = 1, b =2;
    t3.add(&a, &b);
    //Test
    return 0;
}*/

template<int N>
class people<string, N>{
    private:
        string a[N];
    public:
    people() {
        for (int i = 0; i < N; i++) {
            a[i] = "ldc";
        }
    }
    void print(){
        for (int i = 0; i < N; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
};



int main() {
    fun<int, 10>();
    people<int, 10> t;
    people<string, 10> t2;

    return 0;
}








