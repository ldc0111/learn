#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 100010;
const int SIZE = 26;
const char BASE = 'a';

typedef struct TrieNode {
    int flag;
    struct TrieNode **next;
} TrieNode, *Trie;
int cnt = 0;


TrieNode* new_node() {
    TrieNode *p = (TrieNode *)calloc(sizeof(TrieNode), 1);
    p->next = (TrieNode **)calloc(sizeof(TrieNode*), SIZE);
    return p;
}

void clear(Trie root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

void insert(Trie root, const char *pattern) {
    TrieNode *p = root;
    for (int i = 0; pattern[i]; i++) {
        if (p->next[pattern[i] - BASE] == NULL) {
            p->next[pattern[i] - BASE] = new_node();
            cnt++;
        }
        p = p->next[pattern[i] - BASE];
    }
    p->flag = 1;
    return ;
}


int main() {
    char str[N];
    Trie root = new_node();
    scanf("%s", str);
    
    for (int i = 0; i <= strlen(str); i++) {//长度
        insert(root, str + i);
    }
    printf("%d\n", cnt);
    return 0;
}