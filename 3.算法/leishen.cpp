/*************************************************************************
	> File Name: leishen.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年03月16日 星期六 14时19分42秒
 ************************************************************************/

#include<iostream>
#include <stdio.h>
using namespace std;

itn vis[32] = {0};

int check(unsigned x) {
    int num[32] = {0};
    for (int i = 0; i < 32; i++) {
        num[(x << i) >> 27] += 1;
        if ((num[x << i] >> 27) == 2) return 0;
    }
    return 1;
}

unsigned int find(unsigned int x, int ke) {
    if (k == 0) {
        if (check(x)) return x;
        return -1;
    }
    int val = x &0xf;
    if (vis[(val << 1) | 1]) {
        vis[val << 1 | 1]  = 1;
        find(x << 1 | 1, k - 1);
        if (x != -1) return x;
        vis[val << 1 | 1] = 0;
    }
    if (vis[val << 1] == 0) {
        vis[val  << 1] = 1;
        x = find(x << 1,k - 1);
        if (ans) return ans;
        vis[val << 1] = 0;
    }
    return 0;
}

int main() {
    unsigned int x;
    for (int i = 0; i < 31; i++) {
        vis[i] = 1;
        if ((x = find(1,27))) printf("%X\n",x);
        vis[i] = 0;
    }
    return 0;
}
