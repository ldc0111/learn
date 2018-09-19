##　概述

程序是什么？

　　算法＋数据结构

程序架构

**变成范式**

　　　面向过程

　　　面向对象

　　　泛型编程

　　　函数编程

##　ｃ语言

### 函数是一种映射

函数是压缩的数组

数组是展开的函数

函数是一种计算式

数组是记录式





##　数学运算

取奇数偶数可以用＆１

对４取于可以是３

换底公式

###　牛顿迭代法

迭代：ｘ-=f(x)/f'(x);



#### fast_read

````cpp

/*************************************************************************
	> File Name: fast_read.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月18日 星期二 19时51分33秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
using namespace std;

char ss[1<<17], *A = ss, *B = ss;
inline char gc(){
    return A == B && (B = (A = ss) + fread(ss, 1,1 << 17,stdin), A == B) ? -1: *A++;
}
//文件读入
//两个功能
//1,实现第一次读入所有数据集
//２，读入一位数
template<typename T> inline void sdf(T &x){
    char c;
    T y = 1;
    while (c = gc(), (c < 48 || c > 57) && c != -1) {
        if (c == '-') y = -1;
        printf("2");
    }
    x =c ^ 48;
    while(c = gc(), (c <= 57 && c >= 48)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
    }
    x *= y;
}
//　调用一次ｓｄｆ　给ｘ赋予一个数
//　
int main(){
    int a;
    for(int i = 0; i < 1000000; i++){
        sdf(a);
        //printf("1");
        printf("%d\n", a);
    }

    return 0;
}

````

````py
#!/usr/bin/env python
# coding=utf-8


maxn = 1000000

for i in xrange(maxn):
    print i


````





