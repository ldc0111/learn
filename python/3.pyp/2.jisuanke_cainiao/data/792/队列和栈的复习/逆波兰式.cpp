#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 1000000

int calc(char *str, int l, int r){
    int pos = -1, temp_prior,prior = INF - 1;
    for(int i = l; i <= r; i++){
        int cur_prior = INF;
        switch(str[i]) {
            case '+': cur_prior = 1; break; 
            case '-': cur_prior = 1; break;
            case '*': cur_prior = 2; break;
            case '/': cur_prior = 2; break;
        }
        if(cur_prior <= prior){
            prior = cur_prior;
            pos = i;
        }
    }
    if(pos == -1){
        int num = 0;
        for(int i = l; i <= r; i++){
            if(str[i] < '0' || str[i] > '9') continue;
            num = num * 10 + str[i] - '0';
        }
        return num;
    }else{
        int a = calc(str, l, pos - 1);
        int b = calc(str, pos + 1, r);
        switch(str[pos]){
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
        }
    }
    return 0;
}

int main(){
    char s[30];
    int num = 0;
    scanf("%[^\n]s", s);
    
    num = calc(s,0,strlen(s) - 1);
    printf("%d\n", num);
    
    return 0;
}