/*************************************************************************
	> File Name: trie.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年08月28日 星期三 23时43分01秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define BASE_CNT 26
#define BASE 'a'

typedef struct Node{
    int flag;
    struct Node *next[26];
}Node;


Node *getNewNode() {
    return (Node *)calloc(sizeof(Node),1);
}


void insert(Node *node,const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) {
            p->next[str[i] - BASE] = getNewNode();
        }
        p = p->next[str[i] - BASE];
    }
    p->flag = 1;
    return ;
}

int search(Node *node, const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) return -1;
        p = p->next[str[i] - BASE];
    }
    return p->flag;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE_CNT; i++) {
        clear(node->next[i]);
    }
    free(node);
}


int main() {
    Node *root = getNewNode();
    char str[100];
    int op;
    while (scanf("%d%s",&op,str) != EOF) {
        switch(op) {
            case 1:{
                printf ("insert %s to trie\n",str);
                insert(root,str);
            }break;
            case 2:{
                printf("search %s from trie = %d\n",str,search(root,str));
            }break;
        }
    }
    return 0;
}
