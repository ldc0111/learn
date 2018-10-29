/*************************************************************************
	> File Name: int.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月26日 星期五 23时59分32秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//返回要查找的字符的下标，最后匹配返回特殊值-1，出现错误，返回特殊值-2
bool match(char * s, int *ind,char fato){
    printf("ind : %d,fato :%c\n",*ind, fato);
    if(*(s + *ind) == NULL && fato =='a') return true;
    if(*(s + *ind) == NULL && fato != 'a') return false;
    switch(*(s + (*ind)++)){
        case '(': return match(s, ind, ')') ? match(s, ind, fato): false;
        case '[': return match(s, ind, ']') ? match(s, ind, fato): false;
        case '{': return match(s, ind, '}') ? match(s, ind, fato): false;
        case ')': return fato == ')' ? true:false;
        case ']': return fato == ']' ? true:false;
        case '}': return fato == '}' ? true:false;
    }
 printf(" -22 ");
    return false;
}



bool isValid(char* s) {
    int ind = 0;
    return match(s,&ind, 'a');
}

int main(){
    char s[44]={"{[][][]}"};
    printf("|%d|\n",isValid(s));
    return 0;
}
