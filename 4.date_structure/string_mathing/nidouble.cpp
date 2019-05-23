/*************************************************************************
	> File Name: nidouble.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月06日 星期日 16时03分08秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct DATNode{
    int base, check;
}DATNode;


void pro(DATNode *trie,int ind, int len, char *st){
    if(trie[ind].check < 0) {
        printf("%s\n", st);
    }
    for (int i  = 0; i < 26; i++) {
        int check = abs(trie[trie[ind].base + i].check);
        if(ind == 1 && i == 0 && trie[ind].base == 1) continue;
        if(check  - ind == 0) {
            st[len] = i + 'a';
            st[len + 1] = 0;
            pro(trie, trie[ind].base + i, len + 1, st);
        }
    }
    return ;
}



int main() {
    DATNode *trie = (DATNode *)calloc(sizeof(DATNode), 200);
    int n = 0;
    char st[50];
    memset(st, 0, sizeof(st));
    int cnt = 0;
    while(scanf("%d%d%d", &n, &trie[n].base, &trie[n].check) != EOF) n++;
    
    //for (int i = 0; i <= 162; i++) {
    //    printf("%d %d %d\n", i, trie[i].base, trie[i].check);
    //}
    
    pro(trie,1, 0, st);
    
    return 0;
}

