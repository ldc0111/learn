#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn1    1000005
int sunday(char *text1,char *text2, char *pattern) {
    int len1 = strlen(text1);
    int len2 = strlen(text2);
    int len3 = strlen(pattern);
    int ind[300];
    for (int i = 0;i < 300; i++) ind[i] = len3 + 1;
    for (int i = 0; pattern[i]; i++) ind[pattern[i]] = len3 - i;
    for (int i = 0; i <= len1 - len3 && i <= len2 - len3;) {
        int j = 0;
        for (; j < len3; j++) {
            if (pattern[j] != text1[i + j] || pattern[j] != text2[i + j]) {
                break;
            }
        }
        //printf("i %d j %d\n", i, j);
        if (j == len3) return i + 1;
        i += ind[text1[i + len3]];
    }
    return 0;
}
int KMP(char *text1, char *text2, char *pattern) {
    int len1 = strlen(text1);
    int len2 = strlen(text2);
    int len3 = strlen(pattern);
    int *next = (int)malloc(sizeof(int) * len3);
    int j = -1;
    next[0] = -1;
    for (int i = 1; pattern[i]; i++) {
        while (j >= 0 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) j += 1;
        next[i] = j;
    }
    //for (int i = 0; i < len3; i++) {
    //    printf("%d ",next[i]);
    //}
    j = -1;
    for (int i = 0; text1[i] && text2[i]; i++) {
        while (j >= 0 && pattern[j + 1]!= text1[i] && pattern[j + 1] != text2[i]) {
            j = next[j];
        }
        //printf("%c %c %c\n", pattern[j + 1],text1[i], text2[i]);
        if (pattern[j + 1] == text1[i] && pattern[j + 1] == text2[i]) {
            j += 1;
        }
        //printf("%c %c %c\n", pattern[j + 1],text1[i], text2[i]);
        if (j + 1 == len3) return i - len3 + 2;
    }
    return 0;
}

int main() {
    char text1[maxn1];
    char text2[maxn1];
    char pattern[maxn1];
    scanf("%[^\n]s", text1);
    getchar();
    scanf("%[^\n]s", text2);
    getchar();
    scanf("%[^\n]s", pattern);
    //printf("%d\n",sunday(text1,text2,pattern));
    printf("%d\n",KMP(text1,text2,pattern));
    return 0;
}