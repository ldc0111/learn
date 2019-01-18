/*************************************************************************
	> File Name: array.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 19时08分46秒
 ************************************************************************/

#include<iostream>
using namespace std;
class array{
    private:
    int m_len;
    int *data;
    public:
    array(int len = 0) : m_len(len) {
        data = new int[len];
    }
    array& operator=(const array &obj) {
        if (this == &obj)  return *this;
        int *p = new int[obj.m_len];
        if (p) {
            for (int i = 0; i < obj.m_len; i++) {
                p[i] = obj.data[i];
            }
            m_len = obj.m_len;
            delete[] data;
            data = p;
        }
        return *this;
    }
    void set(int index, int value) {
        if (index >= 0 && index < m_len) {
            data[index] = value;
        }
    }
    int get(int index) {
        if (index >= 0 && index < m_len) {
            return data[index];
        }
    }
    int& operator[] (int index) {
        if ((index < m_len) && (index >= 0)) {
            return data[index];
        } else {
            //自己想办法
            throw -1;
        }
    }
};


int main() {
    array a1(5);
    for (int i = 0; i < 5; i++) {
        a1.set(i, i + 1);
    }
    for (int i = 0; i < 5; i++) {
        cout << a1[i] << " ";
    }
    /*
    cout << endl;
    array a2(10);
    for (int i = 0; i < 10; i++) {
        a2.set(i, i + 1);
    }
    a1 = a2;
    for (int i = 0; i < 10; i++) {
        cout << a1.get(i) << " ";
    }
    cout << endl;
    */
    return 0;
}
