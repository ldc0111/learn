/*************************************************************************
	> File Name: 2.string_algrithm.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月03日 星期一 09时59分48秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST(func) {\
    printf("%s = %d\n",#func,func);\
}

int sunday(const char *text,const char *patten) {
    int len = strlen(patten),len2 = strlen(text);
    int ind[127] = {0};
    for (int i = 0; i < 127; i++) ind[i] = len + 1;
    //初始化为len+1的值如果要是字符串内没出现这个字符当失配的时候就可以直接跳过这个字符开始继续匹配
    for (int i = 0; patten[i]; i++) ind[patten[i]] = len - i;//标记位最后一个出现的字符到结尾的距离
    for (int i = 0; i <= len2 - len;) {
        int j = 0;
        for (; j < len; j++) {
            if (patten[j] != text[i + j]) break;
        }
        if (j == len) return 1;//匹配成功
        i += ind[text[i + len]];
        //不成功，看失配位置的字符在模式串中最后出现的位置，将i加上标记数组的值，就是将
        //文本串失配的字符与对应的模式串最后出现的那个字符对齐
    }
    return 0;
}

/*
 * 正确性分析，当字符串失配的时候，能够匹配模式串的文本串一定在失配之后，如果模式串中存在失配字符，
 * 当我们记录的是与失配字符相等的最后一个字符出现的位置时，向后移动的范围是最小的，一定不会错过正
 * 确答案
*/
int shift_and(const char *text, const char *patten) {
    int d[127] = {0},n = 0;
    for (n = 0; patten[n]; n++) {
        d[patten[n]] |= (1 << n);
    }
    int p = 0;
    for (int i = 0; text[i]; i++) {
        p = (p << 1 | 1) & d[text[i]];
        if (p & (1 << (n - 1))) return 1;
    }
    return 0;
}




int main(){
    TEST(sunday("hello world","hello"));
    TEST(shift_and("hello world","hello"));
    TEST(sunday("hello world","wr"));
    TEST(shift_and("hello world","wr"));

    return 0;
}
