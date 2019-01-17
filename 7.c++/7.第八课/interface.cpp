/*************************************************************************
	> File Name: interface.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 14时40分35秒
 ************************************************************************/

#include<iostream>
using namespace std;

class INterface {
    public:
        virtual bool open() = 0;
        virtual void class() = 0;
        virtual bool send(char *buf, int len) = 0;
        virtual int recvive() = 0;
        
}

int main() {
    return 0;
}
