/*************************************************************************
	> File Name: Test5.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月08日 星期二 19时26分09秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

class Mem {
    public:
    Mem() {
            cout << "Mem" << endl;
    }
    ~Mem() {
            cout << "~Mem" << endl;
    }
};
class Disk {
    public:
    Disk() {
        cout << "Disk" << endl;
    }
    ~Disk() {
        cout << "~Disk" << endl;
    }

};
class CPU {
    public:
    CPU() {
        cout << "CPU" << endl;
    }
    ~CPU() {
        cout << "~CPU" << endl;
    }
};
class computer{
    private:
        Mem m;
        Disk d;
        CPU c;
    public:
    computer() {
        cout << "computer" << endl;
    }
    ~computer() {
        cout << "~computer" << endl;
    }
    void PowerOn(){
        cout << "power on" << endl;
    }
};
//类与类的关系
int main() {
    computer c;
    return 0;
}
