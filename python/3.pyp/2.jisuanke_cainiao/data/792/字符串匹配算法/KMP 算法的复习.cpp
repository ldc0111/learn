#include <stdio.h>
#include <string.h>

#define MAX_LEN 100010

void get_next(char * pattern, int *next) {
    next[0] = -1;
    for (int i = 1, match = -1; pattern[i]; i++) {
        while (match >= 0 && pattern[match + 1] != pattern[i]) {
            match = next[match];
        }
        if (pattern[match + 1] == pattern[i]) {
            match += 1;
        }
        next[i] = match;
    }
}

int find(char *text, char *pattern, int *next) {
    for(int i = 0,match = -1; i < strlen(text); i++) {
        while(match >= 0 && pattern[match + 1] != text[i]) {
            match = next[match];
        }
        if (pattern[match + 1] == text[i]){
            match += 1;
        }
        if (match == strlen(pattern) - 1) {
            return i - match;
        }
    }
    return -1;
}

int main() {
    char text[MAX_LEN];
    char pattern[MAX_LEN];
    scanf("%s", text);
    scanf("%s",pattern);
    int next[MAX_LEN];
    get_next(pattern,next);
    //for (int i = 0; i < strlen(pattern); i++) {
    //    printf("%d ", next[i]);
    //}
    int num = find(text,pattern,next);
    if (num >= 0) {
        printf("Yes\n%d\n",num);
    } else {
        printf("No\n");
    }
    return 0;
}