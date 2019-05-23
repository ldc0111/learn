/*************************************************************************
	> File Name: main.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 09时14分12秒
 ************************************************************************/

#include<iostream>
#include <string>
using namespace std;

class people{
    private:
    string name;
    int age;
    public:
    people(string s1, int v1) :name(s1),age(v1){

    }
    void print() {
        cout << name << " " << age << endl;
    }
};

class Teacher : virtual public people{
    public:
    Teacher(string s1, int v1) :people(s1, v1) {

    }
};
class Student : virtual public people{
    public :
    Student(string s1, int v1) : people(s1, v1){

    }
};

class Doctor : public Teacher, public Student{
    public:
    Doctor(string s1, int v1) : Teacher(s1 + "1", v1 + 1),Student(s1 + "2", v1 + 2),people(s1 + "1",v1 + 3) {

    }
};
//多继承有数据冗余的时候可以使用虚继承来解决数据冗余
int main() {
    Doctor d("qwe", 28);
    d.Teacher::print();
    d.Student::print();
    d.print();
    return 0;
}
