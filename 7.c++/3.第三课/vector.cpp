/*************************************************************************
	> File Name: vector.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月01日 星期二 20时16分35秒
 ************************************************************************/

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class vector{
    private:
    int length;
    int num;
    int *data;
    public:
    vector(){
        length = 4;
        num = 0;
        data = new int[length];
    }
    vector(int length){
        this->length = length;
        num = 0;
        data = new int[length];
    }
    void expand(){
        length <<= 1;
        cout << "expand :" << length << endl;
        int *data1 = data;
        data = (int *)malloc(sizeof(int) * length);
        //data = (int *)realloc(data, length);
        for (int i = 0; i < num; i++) {
            data[i] = data1[i];
        }
    }
    int insert(int value) {
        if(num >= length) expand();
        data[num++] = value;
        cout << "insert" << endl;
    }
    void print(){
        for (int i = 0; i < num; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }
};


int main() {
    vector arr;
    for (int i = 0; i < 20; i++) {
        arr.insert(i);
        arr.print();
    }
    return 0;
}
