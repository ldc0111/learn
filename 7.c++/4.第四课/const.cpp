/*************************************************************************
	> File Name: const.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月07日 星期一 09时22分10秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

//const 可以修饰一个对象
//const classname 变量名
//1.只读对象 里面的属性是只读的，
//在编译器里面只读对象成员呢属性不能被改变
//const对象只能用const方法
class Test{
    private:
    int i;
    int j;
    const int m;
    public:
    Test(int v):m(10) {
        this->i = v;
        this->j = 5;
    }
    void print() const{
        cout << "hello" << endl;
        return ;
    }
    int getI() const{
        cout << "const" << endl;
        print();
        return this->i;
    }
    int getI(){
        cout << "no const" << endl;
        return this->i;
    }
    int getJ(){
        return this->j;
    }
    int getM() const {
        return m;
    }
    
    void setM(int v){
        int *p = const_cast<int *>(&m);
        *p = v;
        return ;
    }
};

//在函数里面用const编译器认为他就是一个常量，必须给初值
//类外type classname::funcname() const()
//类内：type function const()
//const 方法一些特性
//1const对象只能调用const方法
//2cosnt成员函数，内部只能调用const方法
//3const方法中变量值不可以改的
int main() {
    /*
    const Test t(1);
    cout << t.getI() << endl;
    //cout << t.getJ() << endl;
    */
    Test t(1);
    ;
    cout << t.getM() << endl;
    t.setM(100);
    cout << t.getM() << endl;
    return 0;
}
