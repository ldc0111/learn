/*************************************************************************
	> File Name: lesson_init.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月06日 星期日 18时56分41秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;
//1类中的属性可以用const修饰
//普通初始化方法不好使
//初始化列表
//用法class 

class Value{
    private:
    int i;
    public:
    Value(int v): i(v) {//程序初始化执行的时候，先执行初始化列表，再执行函数体，当函数体执行的时候对象已经存在了
        cout << "i = " << i << endl;

    }
};
//注意事项1,初始化列表的顺序与专属成员属性声明顺序相同一个类类型
//初始化顺序与列表中位置无关,只与声明顺序有关
//初始化列表优先于函数体执行
/*
class Test{
    private:
    const int i;
    int a;
    Value v1;
    public:
    Test(int v1, int v2);

    Test(int v):i(v) {
        //i = v;
        cout << "i = " << i << endl;
    }
    int getI() {
        return i;
    }
};

Test::Test(int v1, int v2) : i(v1),a(v2) {
    cout << "i = " << i << endl;
    cout << "a = " << a << endl;
}*/
class Test{
    private:
    Value v1;
    Value v3;
    Value v2;
    public:
    Test();
    int getI(){
    }
};
Test::Test() :v1(1),v2(2),v3(3){
   cout << "Test" << endl; 
}


int main() {
    Test t;
    cout << "t.i =" << t.getI() << endl;
    return 0;
}
