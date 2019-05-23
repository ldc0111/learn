/*************************************************************************
	> File Name: 1.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月06日 星期六 10时18分01秒
 ************************************************************************/

#include<iostream>
using namespace std;

typedef void (*func)(int a,int b);

struct tes{ 
    func* funcp;
    struct tes *next;
    void add(int a,int b);
}te;
void tes::add(int a,int b){

    printf("haha");
}


int main(){
    te.add(3,4);
    return 0;
}



