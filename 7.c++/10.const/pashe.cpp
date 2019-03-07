/*************************************************************************
> File Name: pashe.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2019年03月06日 星期三 15时13分11秒
************************************************************************/
#include<iostream>
using namespace std;
/*
 class B0//基类 BO 声明
{
    public://外部接口
    virtual void display() = 0;//虚成员函数
    //{
    //    cout<<"B0::display0"<<endl;}
};
class B1:public B0//公有派生
{
    public:
    void display() { cout<<"B1::display0"<<endl; }
};
class D1: public B1//公有派生
{
    public:
    void display(){ cout<<"D1::display0"<<endl; }
};
void fun(B0 &ptr)//普通函数
{
    ptr.display();
}
int main()//主函数
{
    //B0 b0;//声明基类对象和指针
    B1 b1;//声明派生类对象
    D1 d1;//声明派生类对象
    //fun(b0);//调用基类 B0 函数成员
    fun(b1);//调用派生类 B1 函数成员 
    fun(d1);//调用派生类 D1 函数成员
    return 0;
}*/


class Test{
    public:

    static int a;
    void f(){
        this->a += 1;
    }
};


int Test::a=0;
int main() {
    Test c, d;
    c.f();
    d.f();
    cout << Test::a << endl;
    return 0;
}

