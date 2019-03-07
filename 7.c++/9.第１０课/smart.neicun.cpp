/*************************************************************************
	> File Name: neicun.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月21日 星期一 18时33分23秒
 ************************************************************************/

#include<iostream>
using namespace std;


class Test{
    private:
    int i;
    public:
    Test(int v = 0) {
        i = v;
    }
    int geti() {
        return i;
    }
};

//自动回收的功能
//
class SmartPoint{
    private:
    Test *mp;
    public:
    SmartPoint(Test *p = NULL) :mp(p) {
    }
    Test *operator->() {
        return mp;
    }
    Test& operator*() {
        return *mp;//*mp = 8;可以赋值返回引用
    }
    SmartPoint(const SmartPoint &obj){
        mp = obj.mp;
        const_cast<SmartPoint &>(obj).mp = NULL;
    }
    SmartPoint& operator=(const SmartPoint &obj) {
        if (this == &obj) return *this;//防止自赋值
        delete mp;//吧当前对象的值给他
        mp = obj.mp;
        //去掉他的属性
        const_cast<SmartPoint &>(obj).mp = NULL;
        return *this;
    }
    ~SmartPoint() {
        delete mp;
    }
};
//智能之后怎特性，１能自动回收堆空间
//２一片内存空间只能有一个指针指向
//（避免多次释放）
//３杜绝指针运算
//
//二：　->  和　*重载的注意事项
//１，只能重载成成员函数
//２，重载函数不能有参数
//３，一个类中只能定义１个
//只能用于堆空间的申请和删除
//只能指针理论上是用对象取模拟原声指针
//
//
//
//



int main() {
    for (int i = 0; i < 5; i++) {
        SmartPoint p = new Test(i);//调用的构造函数，不是ｃｏｐｙ构造函数
        cout << p->geti() << endl;
    }
    SmartPoint p1(new Test(1));
    SmartPoint p2(new Test(2));
    p1 = p2;
    //if (p1 == p2);
    //p1++;
    return 0;
}
