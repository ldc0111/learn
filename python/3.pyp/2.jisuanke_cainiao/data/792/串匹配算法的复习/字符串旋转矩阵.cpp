#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 110000
void quick_sort(char *str, int l, int r) {
    if (l >= r) return ;
    int x = l, y = r, z = str[l];
    while (x < y) {
        while (x < y && str[y] >= z) y--;
        if (x < y) str[x++] = str[y];
        while (x < y && str[x] <= z) x++;
        if (x < y) str[y--] = str[x];
    }
    str[x] = z;
    quick_sort(str,l, x -  1);
    quick_sort(str,x + 1, r);
}
char * bianma(char *str2, char *str1) {
    int len = strlen(str2),p = 0;
    int *temp = (int *)calloc(sizeof(int),len);
    char *arr = (char *)calloc(sizeof(char), len + 1);
    char ch = 0;
    for (int i = 0; str2[i]; i++) {
        if(str2[i] != ch) p = 0;
        while (str1[p] != str2[i]) p++;
        temp[i] = p++;
        ch = str2[i];
    }
    /*
    for (int i = 0; i < strlen(str2); i++) {
        printf("%d \n",temp[i]);
    }*/
    p = 0;
    for (int i = 0; i < strlen(str2); i++) {
        arr[i] = str2[p];
        p = temp[p];
    }
    return arr + 1;
}
int KMP(char *pattern, char *text) {
    int len1 = strlen(pattern), len2 = strlen(text);
    int *next = (int *)malloc(sizeof(int) * len1);
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < len1; i++) {
        while (j > -1 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) j++;
        else j = -1;
        next[i] = j;
    }
    j = -1;
    for (int i = 0; i < len2; i++) {
        while (j > -1 && pattern[j + 1] != text[i]) j = next[j];
        if (pattern[j + 1] == text[i]) j++;
        else j = -1;
        if (pattern[j + 1] == 0) return 1;
    }
    return -1;
}


int main(){
    char str1[maxn + 5];
    char str2[maxn + 5];
    char *arr = NULL;
    int n = 0;
    scanf("%s", str1);
    strcpy(str2, str1);
    quick_sort(str2, 0, strlen(str2) - 1);
    arr = bianma(str2,str1);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s",str2);
        if(KMP(str2, arr) >= 0) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}