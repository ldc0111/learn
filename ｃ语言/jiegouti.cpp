/*************************************************************************
	> File Name: jiegouti.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月04日 星期四 09时38分35秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;
typedef struct Node{
    char name[17];
    int age;
    char gender;
    float height;
}node;


int main(){
    printf("%d",sizeof(node));
    return 0;
}
