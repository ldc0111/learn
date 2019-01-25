/*************************************************************************
	> File Name: double_arraytree_ac_dfs.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月23日 星期三 12时07分30秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BASE 'a'
#define SIZE 26

typedef struct Node{
    int flag;
    struct Node *next[SIZE];
}Node;

Node *getNewNode() {
    return (Node *)calloc(sizeof(Node), 1);
}

int insert(Node *node, const char *str) {
    Node *p = node;
    int cnt = 0,ind = 0;
    while (str[0]) {
        ind = str[0] - BASE;
        if (p->next[ind] == NULL) {
            p->next[ind] = getNewNode();
            cnt++;
        }
        p = p->next[ind];
        str++;
    }
    p->flag= 1;
    return cnt;
}
int search(Node *node, const char *str) {
    Node *p = node;
    int ind = 0;
    while (p && str[0]) {
        ind = str[0] - BASE;
        p=p->next[ind];
        str++;
    }
    return (p && p->flag);
}


void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}
int main() {
    Node *root = getNewNode();
    int n = 0;
    char str[50];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(root,str);
    }
    while (scanf("%s", str)) {
        printf("search %s = %d\n", str,search(root, str));
    }
    clear(root);
    return 0;
}
