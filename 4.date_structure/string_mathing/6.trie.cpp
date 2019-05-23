/*************************************************************************
	> File Name: 6.trie.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月30日 星期日 20时38分46秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_CNT 26
#define BASE 'a'

typedef struct Node{
    int flag;
    struct Node *next[BASE_CNT];
}Node;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    for (int i = 0; i < BASE_CNT; i++) {
        p->next[i] == NULL;
    }
    p->flag = 0;
    return p;
}

void insert(Node *node, const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) p->next[str[i] - BASE] = getNewNode();
        p = p->next[str[i] - BASE];
    }
    p->flag = 1;
    return ;
}
int search(Node *node, const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) {
            return 0;
        }
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
    return ;
}


int main() {
    Node *root = getNewNode();
    char str[100];
    int op;
    while (scanf("%d%s", &op, str) != EOF) {
        switch(op) {
            case 1: {
                printf("insert %s to trie\n", str);
                insert(root, str);
                break;
            }
            case 2: {
                printf("search %s to, trie = %d\n", str, search(root, str));

            }
        }
    }
    return 0;
}
