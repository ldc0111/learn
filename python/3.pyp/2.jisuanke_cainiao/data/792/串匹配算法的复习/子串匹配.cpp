#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxn 1005

int get_num(const char *str) {
    int n = 0;
    for (int i = 0; str[i] >= '0' && str[i] <= '9'; i++) {
        n = n * 10 + str[i] - '0';
    }
    return n;
}

void build(char *text,const char *str) {
    int i = 0,j = 0;
    while (str[i]) {
        if (str[i] >= 'a'  && str[i] <= 'z'){
            text[j++] = str[i++];
        } else if (str[i] == '[') {
            int x = i + 1,k = i + 1,num;
            while (str[k] != ']') k++;
            num = get_num(str + k + 1);
            while (num--){
                for (int t = x; t < k; t++){
                    text[j++] = str[t];
                }
            }
            i = k + 1;
        } else if (str[i] >= '0' && str[i] <= '9') {
            i++;
        }
    }
}

int Sunday(const char *text,const char *pattern){
    int len1 = strlen(text),len2 = strlen(pattern),cnt = 0;
    int ind[280] = {0};
    for (int i = 0; i < 280; i++) ind[i] = len2 + 1;
    for (int i = 0; pattern[i]; i++) ind[pattern[i]] = len2 - i;
    for (int i = 0; i <= len1 - len2;) {
        int j = 0;
        for (; j < len2; j++) {
            if (pattern[j] != text[i + j]) break;
        }
        if(j == len2) cnt++;
        i += ind[text[i + len2]];
    }
    return cnt;
}
int main() {
    char str[maxn];
    char b[maxn];
    char text[maxn * maxn];
    scanf("%s", str);
    scanf("%s", b);
    build(text,str);
    //printf("%s\n",text);
    printf("%d\n",Sunday(text,b));
    return 0;
}