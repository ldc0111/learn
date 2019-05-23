/*************************************************************************
	> File Name: 046.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月14日 星期一 20时18分03秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <string.h>
using namespace std;
#define maxn 500000

char s[maxn + 5];

int expand(char *s, int l, int r) {
    int head = l, tail = r;
    while (s[head] == s[tail]) head--, tail++;
    if(head != l) {
        char c = s[tail];
        s[tail] = 0;
        printf("%s\n", s + head + 1);
        s[tail] = c;
    }
    return 0;
}



int main() {
    string str;
    int n;
    cin >> str;
    for (int i = 0; i < str.size(); i++) s[i + 1] = str[i];
    n = str.size();
    for (int i = 1; i <= n; i++) {
        printf("%c\n", s[i]);
        expand(s, i - 1, i + 1);
        expand(s, i, i + 1);
    }

    return 0;
}
