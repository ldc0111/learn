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





####　函数

####　递归是一个技巧，不是算法



1. 语义信息　n的阶乘
2. 边界处理条件
3. 处理过程
4. 递归过程
5. 结果返回



####　函数一章

变参函数



````
int max_int(int a, ...);
va_list获取往后的参数裂变
va_start定位后面第一个参数位置
va_arg获取下一个可变参数中的参数列表
va_end结束整个获取可变参数列表

````



#### 复杂结构与指针

结构体

对齐方式

会找到结构体中占用内存最大的那个作为对齐方式，选择最大类型的倍数位内存的字节数

每个类型选用的开始地址必须是本类型的倍数（方便cpu取字节，cpu一次取一个整型，这样不会跨字节取数据，节约时间）

```c
struct node1{
    char a;
    char b;
    int c;
};
struct node2{
    char a;
    int c;
    char b;
};
```

````c
typedef struct node{
    char name[17];
    int age;
    char gender;
    float height;
}node;
````

````c
struct node{
    short a;
    char a;
    int c;
    double e;
}
0x00 0x02 0x04 0x08 
````





共用体

union





#### 指针

*解析运算符

scanf（“%d”，&n）；

为什么取地址，要给n赋值，必须取地址



传出参数，传入参数

-> 间接引用

a[1].x

(p+1)->x

​    (*(p+1)).x

p[1].x

​    (a + 1)->x

​    *(a + 1).x

(a + 1)->x



#### 宏的妙用

https://blog.csdn.net/yang_yulei/article/details/31496091