/*************************************************************************
	> File Name: ACDFS.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月20日 星期日 09时44分21秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BASE 26
#define BASE_le 'a'

typedef struct Node{
    int flag;
    struct Node *next[BASE], *fail, *father;
}Node;

Node *getnownode() {
    return (Node *)calloc(sizeof(Node), 1);
}

void clear(Node *root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
}

void insert(Node *root, const char *str){
    Node *p = root;
    for (int i = 0;  str[i]; i++) {
        int ind = str[i] - BASE_le;
        if (p->next[ind] == NULL) {
            p->next[ind] = getnownode();
        }
        p->next[ind]->father = p;
        p = p->next[ind];
    }
    p->flag = 1;
    return ;
}

void build_ac(Node *node) {
    if (node == NULL) return ;
    if (node->fail == NULL) build_ac(node->father);
    for (int i = 0; i < BASE; i++) {
        if (node->next[i] == NULL) continue;
        if (node->next[i]->fail) continue;//有失败指针就不建立失败指针
        Node *p = node->fail, *pre_p = node;
        while (p && p->next[i] == NULL) {
            if (p->fail == NULL) build_ac(p->father);
            //他的失败指针的失败指针没有确定，就去确定他失败指针的父亲节点的
            //第四层会成环，返回到根节点会重新建立全部的节点
            pre_p = p;
            p = p->fail;
        }
        if (p == NULL) p = pre_p;//当ｐ等于空的时候,pre_等于根节点
        else p = p->next[i];
        node->next[i]->fail = p;
        build_ac(node->next[i]);
    }
    return ;
}


int main() {
    Node *root =  getnownode();

    return 0;
}


