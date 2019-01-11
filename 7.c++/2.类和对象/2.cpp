/*************************************************************************
	> File Name: 2.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月25日 星期二 20时23分30秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace my_lib {
    class People {
        private:
            int age;
            string name;
        public:
        //构造函数
        People(string s) {
            name = s;
        }
        //成员函数
        int  getAge() {
            return age;
        }
        //成员函数
        string getName() {
            return name;
        }
    };
}


//using my_lib::People;
int main() {
    my_lib::People p("wefwf");
    my_lib::People *p1 = new my_lib::People("wewe");
    cout << p.getName() << endl;
    delete p1;
    return 0;
}
