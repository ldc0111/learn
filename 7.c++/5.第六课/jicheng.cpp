/*************************************************************************
	> File Name: jicheng.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月08日 星期二 19时45分26秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;


/*
 *　继承：类与类的一种关系－》单向关系
 *父亲－儿子－儿子
 *父类为基类，子类为派生类
 *１，子类继承了父类的所有属性和方法
 *２，子类是一种特殊的父类
 *３，子类对象也可以当父类对象用
 *４，子类不仅有父类的属性和方法，而且还可以有自己的属性和方法，还可以重写父类的方法
 */
 class Father {
     //private:
     protected:
        int i;
     public:
     Father() {
         i = 100;
     }
     int get() {
         return i;
     }
    void say() {
         cout << "I am Father." << endl;
     }
 };


class Son:public Father {
    private:
        int age;
    public:
    int getAge(){
        cout << age << endl;
    }
    void say(){
        cout << "i am son" << endl;
    }
};


void how_to_say(Father *f){
    f->say();
}

int main() {
    Father f;
    Son s;
    cout << s.get() << endl;
    how_to_say(&f);//不加ｖｉｒｔｕａｌ都是ｆａｔｈｅｒ
    how_to_say(&s);
    return 0;
}
